#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

inline int getint() {
	int a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

struct Node {
	int v, ly, m, s;
	bool rot;
	Node *fa, *ch[2];
	Node() : v(0), fa(NULL), ly(0), rot(false), m(0), s(0) { memset(ch, 0, sizeof ch); }
	void pushdown();
	void maintain();
}NN[200005], *root;
int totNN = -1, a[100005];

void Node::pushdown() {
		if (rot) {
			if (ch[0]) ch[0]->rot ^= 1, swap(ch[0]->ch[0], ch[0]->ch[1]);
			if (ch[1]) ch[1]->rot ^= 1, swap(ch[1]->ch[0], ch[1]->ch[1]);
			rot = false;
		}
		if (ly) {
			if (ch[0]) ch[0]->v += ly, ch[0]->m += ly, ch[0]->ly += ly;
			if (ch[1]) ch[1]->v += ly, ch[1]->m += ly, ch[1]->ly += ly;
			ly = 0;
		}
	}
void Node::maintain() {
		s = 1, m = v;
		if (ch[0]) s += ch[0]->s, m = min(m, ch[0]->m);
		if (ch[1]) s += ch[1]->s, m = min(m, ch[1]->m);
}

Node* NewNode(int vv = 0, Node *f = NULL) {
	Node *ne = NN + (++totNN);
	ne->m = ne->v = vv; ne->fa = f;
	ne->ch[0] = ne->ch[1] = NULL;
	ne->s = 1; ne->rot = ne->ly = 0;
	return ne;
}

Node* Build(int l, int r, Node *f) {
	if (l > r) return NULL;
	int mid = (l + r) >> 1;
	Node *c = NewNode(a[mid], f);
	c->ch[0] = Build(l, mid - 1, c);
	c->ch[1] = Build(mid + 1, r, c);
	c->maintain();
	return c;
}

void Up(Node *u) {
	while (u) {
		u->maintain();
		u = u->fa;
	}
}

void Rot(Node *u) {
	if (u->fa == NULL) return;
	Node *f = u->fa, *ff = u->fa->fa;
	f->pushdown(); u->pushdown();
	int d = (u == f->ch[1]);
	Node *o = u->ch[d^1];
	f->ch[d] = o; f->fa = u;
	u->fa = ff; u->ch[d^1] = f;
	if (o) o->fa = f;
	if (ff) ff->ch[f == ff->ch[1]] = u;
	f->maintain(); u->maintain();
}

void splay(Node *u, Node *tag) {
	Node *f; int d, dd;
	while (u->fa != tag) {
		u->pushdown();
		if (u->fa->fa == tag) {
			Rot(u); break;
		}
		f = u->fa;
		d = u == f->ch[1], dd = f == f->fa->ch[1];
		if (d ^ dd) Rot(u);
		else Rot(f);
		Rot(u);
	}
	u->maintain();
	if (tag == NULL) root = u;
}

void RTO(int k, Node *tag) {
	Node *cur = root; int ls;
	while (cur) {
		cur->pushdown(); ls = 1;
		if (cur->ch[0]) ls += cur->ch[0]->s;
		if (ls == k) break;
		if (k < ls) cur = cur->ch[0];
		else {
			cur = cur->ch[1];
			k -= ls;
		}
	}
	if (cur) splay(cur, tag);
}

void Add(int x, int y, int val) {
	if (x > y) swap(x, y);
	RTO(x - 1, NULL); RTO(y + 1, root);
	Node* u = root->ch[1]->ch[0];
	u->v += val, u->ly += val, u->m += val;
	Up(u->fa); splay(u, NULL);
}

void Reverse(int x, int y) {
	if (x > y) swap(x, y);
	RTO(x - 1, NULL); RTO(y + 1, root);
	swap(root->ch[1]->ch[0]->ch[0], root->ch[1]->ch[0]->ch[1]);
	root->ch[1]->ch[0]->rot ^= 1;
}

void Insert(int k, int val) {
	RTO(k, NULL); RTO(k + 1, root);
	root->ch[1]->ch[0] = NewNode(val, root->ch[1]);
	Up(root->ch[1]);
	splay(root->ch[1]->ch[0], NULL);
}

void Delete(int k) {
	RTO(k - 1, NULL); RTO(k + 1, root);
	root->ch[1]->ch[0] = NULL; Up(root->ch[1]);
	splay(root->ch[1], NULL);
}

void Min(int x, int y) {
	if (x > y) swap(x, y);
	RTO(x - 1, NULL); RTO(y + 1, root);
	printf("%d\n", root->ch[1]->ch[0]->m);
	splay(root->ch[1]->ch[0], NULL); 
}

void Revolve(int x, int y, int t) {
	if (x > y) swap(x, y);
	t %= (y - x + 1);
	t = (t + y - x + 1) % (y - x + 1);
	if (!t) return;
	RTO(y - t, NULL); RTO(y + 1, root);
	Node *u = root->ch[1]->ch[0];
	root->ch[1]->ch[0] = NULL; root->ch[1]->maintain(); root->maintain();
	
	RTO(x - 1, NULL); RTO(x, root);
	root->ch[1]->ch[0] = u;
	u->fa = root->ch[1];
	root->ch[1]->maintain(); root->maintain();
}

void Print(Node *u) {
		if (u == NULL) return;
		u->pushdown();
		Print(u->ch[0]);
		printf("%d ", u->v);
		Print(u->ch[1]);
}
//debug

char op[10];
int main() {
	//freopen("T.in","r",stdin);
	//freopen("B.out","w",stdout);
	int n = getint(), x, y, d;
	for (int i = 1; i <= n; ++i) a[i] = getint();
	a[0] = a[n + 1] = ~0U>>1;
	root = Build(0, n + 1, NULL);
	n = getint();
	for (int i = n; i; --i) {
		scanf("%s",op);
		if (*op == 'A') {
			x = getint(); y = getint(); d = getint();
			Add(x + 1, y + 1, d);
		}
		else if (*op == 'I') {
			x = getint(); y = getint();
			Insert(x + 1, y);
		}
		else if (*op == 'D') Delete(getint() + 1);
		else if (*op == 'M') Min(getint() + 1, getint() + 1);
		else if (op[3] == 'E') {
			x = getint(); y = getint();
			Reverse(x + 1, y + 1);
		}
		else {
			x = getint(); y = getint(); d = getint();
			Revolve(x + 1, y + 1, d);
		}
		//Print(root);
		//puts("\n------");
	}
}

