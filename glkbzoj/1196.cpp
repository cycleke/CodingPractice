#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int Maxn = 10010, Maxm = 20010;

inline int getint(int &a) {
	a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

struct Edge {
	int u, v, c1, c2;
	void Read() {
		getint(u), getint(v), getint(c1), getint(c2);
	}
	Edge() {}
	bool operator < (const Edge &A) const {
		return c1 < A.c1;
	}
};

int n, m, k, fa[Maxn];
Edge E[Maxm];

int find(int a) {
	return (a == fa[a]) ? a : fa[a] = find(fa[a]);
}

bool check(const int &x) {
	for (int i = 1; i <= n; ++i) fa[i] = i;
	int cnt1, cnttot, fu, fv;
	cnt1 = cnttot = 0;
	for (int i = 1; i < m; ++i) {
		fu = find(E[i].u), fv = find(E[i].v);
		if (fu ^ fv) {
			if (E[i].c1 <= x) {
				++cnt1, ++cnttot; 
				fa[fu] = fv;
			} else if (E[i].c2 <= x) {
				++cnttot;
				fa[fu] = fv;
			}
		}
	}
	return cnt1 >= k && ! (cnttot ^ (n - 1));
}

int main() {
	freopen("T.in","r",stdin);
	getint(n), getint(k), getint(m);
	for (int i = 1; i < m; ++i) 
		E[i].Read();
	int l = 0, r = 30000, mid, ans;
	sort(E + 1, E + m);
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid; r = mid - 1;
		} else l = mid + 1;
	}
	printf("%d", ans);
	return 0;
}