#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxN = 1e5 + 7;

struct node {
	int val, size;
	bool rev;
	node *fa, *ch[2];
	void pd();
	void REV();
	bool which();
	void maintain();
} node_mset[MaxN], *root;

void node :: pd() {
	if (rev) {
		if (ch[0]) ch[0]->REV();
		if (ch[1]) ch[1]->REV();
		rev = false;
	}
}

void node :: REV() {
	rev ^= true;
	swap(ch[0], ch[1]);
}

bool node :: which() {
	return fa->ch[1] == this;
}

void node :: maintain() {
	size = 1;
	if (ch[0]) size += ch[0]->size;
	if (ch[1]) size += ch[1]->size;
}

inline node *kth(int k) {
	node *u = root;
	static int t;
	while (u) {
		u->pd();
		t = (u->ch[0]) ? u->ch[0]->size : 0;
		if (k <= t) u = u->ch[0];
		else if (k > t + 1) u = u->ch[1], k -= t + 1;
		else return u;
	}
	return NULL;
}

inline void rot(node *u) {
	node *f = u->fa;
	f->pd(); u->pd();
	int d = u->which();
	if (f->ch[d] = u->ch[d ^ 1])
		f->ch[d]->fa = f;
	u->ch[d ^ 1] = f;
	u->fa = f->fa;
	if (f->fa) f->fa->ch[f->which()] = u;
	f->fa = u;
	f->maintain();
}

inline void splay(node *u, node *target) {
	for (node *f; u->fa != target; rot(u))
		if ((f = u->fa)->fa != target)
			f->fa->pd(), rot(f->which() == u->which() ? f : u);
	u->maintain();
	if (target == NULL) root = u;
}

node *build(int l, int r) {
	int m = (l + r) >> 1;
	node *u = node_mset + m;
	u->val = m;
	if (l < m) (u->ch[0] = build(l, m - 1))->fa = u;
	if (m < r) (u->ch[1] = build(m + 1, r))->fa = u;
	u->maintain();
	return u;
}
int n, m;
void Print(node *u) {
	u->pd();
	if (u->ch[0]) Print(u->ch[0]);
	if (u->val && u->val <= n) printf("%d ", u->val);
	if (u->ch[1]) Print(u->ch[1]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	root = build(0, n + 1);
	for (int l, r; m; --m) {
		scanf("%d%d", &l, &r);
		splay(kth(l), NULL);
		splay(kth(r + 2), root);
		root->ch[1]->ch[0]->REV();
		//.Print(root); puts("");
	}
	Print(root); puts("");
	return 0;
}
