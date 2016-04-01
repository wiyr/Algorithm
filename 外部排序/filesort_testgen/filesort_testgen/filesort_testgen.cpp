#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "Psapi.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <string>
typedef long long LL;
using namespace std;
#define ALL(x) (x.begin(), x.end())
#define rep(i,n) for(int i = 0;i < n;i ++)

const int MAX_TOT_CHAR = 1.1e9;
const int ADD = 100;
const int MAX_LENGTH_PER_LINE = 1e7 - ADD;
const int NAME_SIZE = 33;
const char *sufixName = ".txt";
HANDLE handle;
int MAX_MEMORY_USED;
PROCESS_MEMORY_COUNTERS pmc;

void input(string &str, const string &s, ofstream &out) {
	if (str.length() + s.length() >= MAX_LENGTH_PER_LINE) {
		out << str;
		str = "";
	}
	str.append(s);
	str.push_back('\n');
}

void checkMemoryUsed() {
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	MAX_MEMORY_USED = max(MAX_MEMORY_USED, int(pmc.WorkingSetSize));
}

int main(int argc, const char *argv[]) {
	srand(time(NULL));
	double start = clock();
	if (argc != 4) {
		printf("you need input exact 4 parameters:\n[filesort_testgen] [FILE_COUNT] [LINES_PER_FILE] [OUTPUT_FILE]\n");
		exit(0);
	}

	handle = GetCurrentProcess();
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	int pre = pmc.WorkingSetSize;
	MAX_MEMORY_USED = 0;

	ofstream  out;
	char *buffer = new char[MAX_LENGTH_PER_LINE + 1];
	int FILE_COUNT, LINES_PER_FILE;
	sscanf_s(argv[1], "%d", &FILE_COUNT);
	sscanf_s(argv[2], "%d", &LINES_PER_FILE);

	const int NUM_PER_LINE = MAX_TOT_CHAR / LINES_PER_FILE + 1;

	for (int i = 0; i < FILE_COUNT; i++) {
		char *fileName = new char[NAME_SIZE];
		sprintf_s(fileName, NAME_SIZE, "%s%d%s", argv[3], i + 1, sufixName);
		out.open(fileName);
		string str;

		for (int r = 0; r < LINES_PER_FILE; r++) {
			int c = rand() % ADD + NUM_PER_LINE;
			c = min(c, MAX_LENGTH_PER_LINE);
			for (int j = 0; j < c; j++) {
				buffer[j] = char(rand() % 26 + 'a');
			}
			buffer[c] = 0;
			input(str, string(buffer), out);
		}
		out << str;
		str = "";
		checkMemoryUsed();
		delete []fileName;
		out.close();
	}
	printf("Generated %s files:\n", argv[3]);
	for (int i = 0; i < FILE_COUNT; i++) {
		printf("%s%d\n", argv[3], i + 1);
	}
	checkMemoryUsed();
	double end = clock();
	delete []buffer;
	printf("used time: %.2fs\n", (end - start) / CLOCKS_PER_SEC);
	printf("Memory used: %d(B) %d(KB)\n", MAX_MEMORY_USED - pre, (MAX_MEMORY_USED - pre) / 1024);
	return 0;
}
