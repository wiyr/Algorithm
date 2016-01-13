const int N = 200000;

struct Node {
	int v, s, r;
	Node *ch[2];

	Node(int v): v(v) {
		r = rand();
		ch[0] = ch[1] = NULL;
	}

	int cmp(int x) const {
		if(x == v)    return -1;
		return x < v ? 0: 1;
	}

	void up() {
		s = 1;
		if(ch[0] != NULL)    s += ch[0]->s;
		if(ch[1] != NULL)    s += ch[1]->s;
	}
};

void rot(Node* &o, int d) {
	Node *k = o->ch[d^1];
	o->ch[d^1] = k->ch[d];
	k->ch[d] = o;
	o->up();
	k->up();
	o = k;
}

void insert(Node* &o, int x) {
	if(o == NULL)    o = new Node(x);
	else {
		int d = (x < o->v ? 0: 1);
		insert(o->ch[d], x);
		if(o->ch[d]->r > o->r) {
			rot(o, d^1);
		}
	}
	o->up();
}

void remove(Node* &o, int x) {
	int d = o->cmp(x);
	if(d == -1) {
		Node *u = o;
		if(o->ch[0] && o->ch[1]) {
			int d2 = (o->ch[0]->r > o->ch[1]->r ? 1: 0);
			rot(o, d2);
			remove(o->ch[d2], x);
		} else {
			if(o->ch[0] == NULL)    o = o->ch[1];
			else    o = o->ch[0];
			delete u;
		}
	} else
		remove(o->ch[d], x);
	if(o != NULL)    o->up();
}

void removeTree(Node* &o) {
	if(o->ch[0])    removeTree(o->ch[0]);
	if(o->ch[1])    removeTree(o->ch[1]);
	delete o;
	o = NULL;
}
