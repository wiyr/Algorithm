const int N = 50050;

struct Node {
	Node *ch[2];
	int s; 
	bool flip;

	int cmp(int k) const {
		int d = k - ch[0]->s;
		if(d == 1)	return -1;
		return d <= 0 ? 0: 1;
	}

	inline void modifyFlip() {
		flip = !flip;
		std::swap(ch[0], ch[1]);
	}

	void down() {
		if(flip) {
			ch[0]->modifyFlip();
			ch[1]->modifyFlip();
			flip = !flip;
		}
	}

	void up() {
		s = 1;
		s += ch[0]->s + ch[1]->s;
	}

}pool[N];

Node *root, *null = new Node();
int sz;

void rot(Node* &o, int d) {
	Node *k = o->ch[d^1];
	o->ch[d^1] = k->ch[d];
	k->ch[d] = o;
	o->up();
	k->up();
	o = k;
}

void splay(Node* &o, int k) {
	o->down();
	int d = o->cmp(k);
	if(d == 1)	k -= o->ch[0]->s + 1;
	if(d != -1) {
		Node *p = o->ch[d];
		p->down();
		int d2 = p->cmp(k);
		int k2 = d2==0 ? k: k-p->ch[0]->s - 1;
		if(d2 != -1) {
			splay(p->ch[d2], k2);
			if(d2 == d) {
				rot(o, d^1);
			} else
				rot(o->ch[d], d);
		}
		rot(o, d^1);
	}
}

void split(Node *o, int k, Node* &left, Node* &right) {
	splay(o, k);
	left = o;
	right = o->ch[1];
	o->ch[1] = null;
	left->up();
}

Node* merge(Node *a, Node *b) {
	splay(a, a->s);
	a->ch[1] = b;
	a->up();
	return a;
}

Node* build(int s) {
	if(!s)	return null;
	Node *L = build(s / 2);
	Node *o = &pool[sz];
	sz ++;
	o->ch[0] = L;
	o->ch[1] = build(s - s/2 - 1);
	o->up();
	return o;
}

void init(int s) {
	null->ch[0] = null->ch[1] = NULL;
	null->s = 0;
	sz = 0;
	root = build(s);
}
