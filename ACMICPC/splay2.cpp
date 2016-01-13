const int N = 200010;
struct Node *null;

struct Node {
	Node *ch[2], *fa;
	int s;
	bool flip;

	void init() {
		ch[0] = ch[1] = fa = null;
	}

	void up() {
		if(this == null)	return;
		s = ch[0]->s + ch[1]->s + 1;
	}

	void down() {
		if(this == null)	return;
		if(flip) {
			ch[0]->modifyFlip();
			ch[1]->modifyFlip();
			flip = !flip;
		}
	}

	inline void modifyFlip() {
		flip = !flip;
		std::swap(ch[0], ch[1]);
	}

	bool d() {
		return fa->ch[1] == this;
	}
 
	void setc(Node *o, int c) {
		ch[c] = o;
		o->fa = this;
		up();
	}

	void rot() {
		int c = d(), cc = fa->d();
		Node *z = fa->fa;
		Node *tmp = fa;
		fa->setc(ch[c^1], c);
		setc(tmp, c^1);
		z->setc(this, cc);
	}

	void D() {
		if(this == null)	return;
		fa->D();
		down();
	}

	void splay(Node *aim = null) {
		D();
		while(fa != aim) {
			if(fa->fa != aim) {
				d() == fa->d() ? fa->rot(): rot();
			}
			rot();
		}
	}

}pool[N];

int sz;
Node *root;
Node *_alloc() {
	pool[sz].init();
	return &pool[sz ++];
}

void init() {
	sz = 0;
	null = _alloc();
	root = _alloc();
	root->s = 1;
	Node *p = _alloc();
	p->s = 1;
	root->setc(p, 1);
}

