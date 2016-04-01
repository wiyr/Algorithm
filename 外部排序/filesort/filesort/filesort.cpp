// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "Psapi.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <direct.h>
using namespace std;

const int MAX_LENGTH_PER_LINE = 1e7;
const char *tempFile = "tempFile";
const char *PATH = ".\\temp\\";
const char *sufixName = ".txt";
const int NAME_SIZE = 33;
int MAX_MEMORY_USED;

vector<string> vec;
int totTemp;
//ifstream in;
//ofstream out;
FILE* in;
FILE* out;
HANDLE handle;
PROCESS_MEMORY_COUNTERS pmc;

void checkMemoryUsed() {
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	MAX_MEMORY_USED = max(MAX_MEMORY_USED, int(pmc.WorkingSetSize));
}

void inputString(string &str) {
	char *buffer = new char[MAX_LENGTH_PER_LINE];
	for(int i = 0; i < str.length(); i ++) {
		buffer[i] = str[i];
	}
	buffer[str.length()] = 0;
	fprintf(out, "%s", buffer);
	checkMemoryUsed();
	str = "";
	delete []buffer;
}

void input(string &str, const string &s) {
	if (str.length() + s.length() >= MAX_LENGTH_PER_LINE) {
		inputString(str);
	}
	str.append(s);
	str.push_back('\n');
}


void ReadAndSplit(int argc, char *argv[]) {
	_mkdir("temp");
	totTemp = 0;
	char *buffer = new char[MAX_LENGTH_PER_LINE + 1];
	char *tempFileName = new char[NAME_SIZE];
	for (int i = 1; i < argc - 1; i++) {
		in = fopen(argv[i], "r");
		int nowSize = 0;
		string str;
		while (~fscanf(in, "%s", buffer)) {
			int t = strlen(buffer);
			if (nowSize + t >= MAX_LENGTH_PER_LINE) {
				totTemp++;
				nowSize = 0;
				sort(vec.begin(), vec.end());
				sprintf_s(tempFileName, NAME_SIZE, "%s%s%d", PATH, tempFile, totTemp - 1);
				out = fopen(tempFileName, "w");
				for (int j = 0; j < vec.size(); j ++) {
					string &s = vec[j];
					input(str, s);
				}
				inputString(str);
				fclose(out);
				vec.clear();
			}
			vec.push_back(string(buffer));
			nowSize += t;
		}
		if (!vec.empty()) {
			totTemp++;
			sort(vec.begin(), vec.end());
			sprintf_s(tempFileName, NAME_SIZE, "%s%s%d", PATH, tempFile, totTemp - 1);
			out = fopen(tempFileName, "w");
			for (int j = 0; j < vec.size(); j ++) {
				string &s = vec[j];
				input(str, s);
			}
			inputString(str);
			fclose(out);
			vec.clear();
		}
		checkMemoryUsed();
		fclose(in);
	//	in.close();
	}
	printf("read finished\n");
	checkMemoryUsed();
	delete []buffer;
	delete []tempFileName;
}



struct DivideAndConquer {
	char **tFileName;
	int n;

	DivideAndConquer() :tFileName(NULL), n(0) {
	}

	DivideAndConquer(const int& totTemp) {
		n = totTemp;
		tFileName = new char *[n << 1];
		for (int i = 0; i < n * 2; i ++) {
			tFileName[i] = new char[NAME_SIZE];
			sprintf_s(tFileName[i], NAME_SIZE, "%sDivide%s%d", PATH, tempFile, i);
		}
	}

	int getID(const int l, const int r) {
		return l + r | l != r;
	}

	void merge(int l, int r) {
		int o = getID(l, r), mid = l + r >> 1;
		int lson = getID(l, mid), rson = getID(mid + 1, r);

		/*ifstream in_l, in_r;
		ofstream out_o;
		in_l.open(tFileName[lson]);
		in_r.open(tFileName[rson]);
		out_o.open(tFileName[o]); */

		FILE *in_l, *in_r;
		in_l = fopen(tFileName[lson], "r");
		in_r = fopen(tFileName[rson], "r");
		out = fopen(tFileName[o], "w"); 
		char *buf1 = new char [MAX_LENGTH_PER_LINE];
		char *buf2 = new char [MAX_LENGTH_PER_LINE];
		//string buf1, buf2;

		fscanf(in_l, "%s", buf1);
		fscanf(in_r, "%s", buf2);

		//in_l >> buf1;
		//in_r >> buf2;

		int cnt = 0;
		string str;

		while (true) {
			if (lexicographical_compare(buf1, buf1 + strlen(buf1), buf2, buf2 + strlen(buf2))) {
				input(str, string(buf1));
				if (~fscanf(in_l, "%s", buf1)) {
				}
				else {
					do {
						input(str, string(buf2));
					} while (~fscanf(in_r, "%s", buf2));//in_r >> buf2);
					inputString(str);
					//out_o << str;
					break;
				}
			}
			else {
				input(str, string(buf2));
				if (~fscanf(in_r, "%s", buf2)) {
				}
				else {
					do {
						input(str, string(buf1));
					} while (~fscanf(in_l, "%s", buf1));
					inputString(str);
					break;
				}
			}
		}
	/*	in_l.close();
		in_r.close();
		out_o.close();*/

		fclose(in_l);
		fclose(in_r);
		fclose(out);

		delete []buf1;
		delete []buf2;

		remove(tFileName[lson]);
		remove(tFileName[rson]);
	}

	void divide(const int &l, const int &r) {
		int o = getID(l, r);
		if (l == r) {
			//printf("vis %d\n", l);
			sprintf_s(tFileName[o], NAME_SIZE, "%s%s%d", PATH, tempFile, l);
			//printf("ret %d\n", l);
			return;
		}
		int mid = l + r >> 1;
		divide(l, mid);
		divide(mid + 1, r);
		merge(l, r);
	}

	void solve(const char *outFileName) {
		divide(0, n - 1);
		char *buffer = new char [NAME_SIZE];
		sprintf_s(buffer, NAME_SIZE, "%s%s%s", PATH, outFileName, sufixName);
		rename(tFileName[getID(0, n - 1)], buffer);
		delete []buffer;
	}

	~DivideAndConquer() {
		for (int i = 0; i < n * 2; i++) {
			delete[] tFileName[i];
		}
		delete []tFileName;
	}
};

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("you need input more than 3 parameters:\n[filesort] [INPUT_FILE_1] [OUTPUT_FILE_NAME]\n");
		exit(0);
	}
	double start = clock();
	handle = GetCurrentProcess();
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	int pre = pmc.WorkingSetSize;
	MAX_MEMORY_USED = 0;

	totTemp = 0;
	ReadAndSplit(argc, argv);
	DivideAndConquer *res = new DivideAndConquer(totTemp);
	res->solve(argv[argc - 1]);
	checkMemoryUsed();
	delete res;

	double end = clock();
	printf("used time: %.2fs\n", (end - start) / CLOCKS_PER_SEC);
	printf("Memory used: %d(B) %d(KB)\n", MAX_MEMORY_USED - pre, (MAX_MEMORY_USED - pre) / 1024);
	return 0;
}



