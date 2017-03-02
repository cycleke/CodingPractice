#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxS = 400005, MaxN = 200005;

inline int r32() {
	static int r = 0xeedeedef;
	return r = (69069 * r + 1) & (~0u >> 1);
}

struct Circle {
	int x, y, r;
	void read() {
		scanf("%d%d%d", &x, &y, &r);
	}
	bool operator < (const Circle &a) const {
		return x - r < a.x - a.r;
	}
} c[MaxN];
pair<int, int> event[MaxS];

int now;

inline double calc(const int &x, const int &k) {
	static double t;
	t = (long long)(c[x].x - now) * (c[x].x - now);
	t = sqrt((long long)c[x].r * c[x].r - t);
	if (k < 0) return c[x].y - t;
	else return c[x].y + t;
}

struct node {
	node *ls, *rs;
	int sum, val, key, idx;
	void maintain();
	double calc() const;
} node_mset[MaxS], *nil, *root, *cnode = node_mset;

inline node *newnode(const int &x, const int &idx) {
	cnode->idx = idx;
	cnode->key = r32();
	cnode->ls = cnode->rs = nil;
	cnode->sum = cnode->val = x;
	return cnode++;
}

void node :: maintain() {
	sum = val + ls->sum + rs->sum;
}

double node :: calc() const {
	return ::calc(idx, val);
}

void lrt(node * &u) {
	node *t = u->rs;
	u->rs = t->ls;
	t->ls = u;
	t->sum = u->sum;
	u->maintain();
	u = t;
}
void rrt(node * &u) {
	node *t = u->ls;
	u->ls = t->rs;
	t->rs = u;
	t->sum = u->sum;
	u->maintain();
	u = t;
}

void Insert(node * &u, const int &p, const int &k) {
	if (u == nil) {
		u = newnode(k, p);
		return;
	}
	u->sum += k;
	if (u->calc() < calc(p, k) || (u->val < k && u->calc() == calc(p, k))) {
		Insert(u->ls, p ,k);
		if (u->ls->key > u->key) rrt(u);
	} else {
		Insert(u->rs, p, k);
		if (u->rs->key > u->key) lrt(u);
	}
}

void Delete(node * &u, const int &p, const int &k) {
	if (u->idx == p && u->val == k) {
		if (u->ls == nil) u = u->rs;
		else if (u->rs == nil) u = u->ls;
		else if (u->ls->key < u->rs->key) {
			rrt(u);
			Delete(u, p, k);
		} else {
			lrt(u);
			Delete(u, p, k);
		}
	} else {
		u->sum -= k;
		if (u->calc() < calc(p, k) || (u->val < k && u->calc() == calc(p, k)))
		  Delete(u->ls, p, k);
		else
		  Delete(u->rs, p, k);
	}
}

inline int g(const int &v) {
	int ans = 0;
	node *u = root;
	while (u != nil) {
		if (u->calc() > v) {
			ans += u->ls->sum + u->val;
			u = u->rs;
		} else
		  u = u->ls;
	}
	return ans;
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, tot = 0;
	long long ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		c[i].read();
		event[tot++] = make_pair(c[i].x - c[i].r, i);
		event[tot++] = make_pair(c[i].x + c[i].r, -i);
	}
	sort(event, event + tot);
	nil = cnode++;
	*nil = (node) {nil, nil, 0, 0, 0, 0};
	root = nil;
	for (int i = 0; i < tot; ++i) {
		now = event[i].first;
		if (event[i].second > 0) {
			if (g(c[event[i].second].y) & 1)
			  ans -= (long long)c[event[i].second].r * c[event[i].second].r;
			else
			  ans += (long long)c[event[i].second].r * c[event[i].second].r;
			Insert(root, event[i].second, 1);
			Insert(root, event[i].second, -1);
		}  else {
			Delete(root, -event[i].second, 1);
			Delete(root, -event[i].second, -1);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
