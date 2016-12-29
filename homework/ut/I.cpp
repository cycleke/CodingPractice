#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e6 + 5;
map<int,int>X, Y;
pair<int, int>A[Maxn];
int Lx[Maxn], Ly[Maxn], fa[Maxn], ans[Maxn];

int find(int a) {
	return a == fa[a] ? a : fa[a] = find(fa[a]);
}

inline void Union(int a, int b) {
	a = find(a); b = find(b);
	if (a ^ b) fa[a] = b;
}

inline void SelfMax(int &a, const int &b) {
	if (a < b) a = b;
}

int main() {
	int n, m, Siz;
	scanf("%d%d", &n, &m); Siz = n * m;
	for (int i = 0; i < Siz; ++i) {
		scanf("%d", &A[i].first);
		A[i].second = i; fa[i] = i;
	}
	sort(A, A + Siz);
	int j = -1;
	for (int i = 0; i < Siz; ++i) {
		if (i ^ (Siz - 1) && A[i].first == A[i + 1].first) continue;
		for (int k = j + 1; k <= i; ++k) 
			Lx[A[k].second / m]  = Ly[A[k].second % m] = A[k].second;
		for (int k = j + 1; k <= i; ++k) 
			Union(Lx[A[k].second / m], A[k].second), Union(Ly[A[k].second % m], A[k].second);
		for (int k = j + 1; k <= i; ++k)
			SelfMax(ans[find(A[k].second)], max(X[A[k].second / m], Y[A[k].second % m]) + 1);
		for (int k = j + 1; k <= i; ++k)
			SelfMax(X[A[k].second / m], ans[find(A[k].second)]), SelfMax(Y[A[k].second % m], ans[find(A[k].second)]);
		j = i;
	}
	for (int i = 0; i < Siz; ++i) {
		printf("%d ", ans[find(i)]);
		if (i % m == m - 1) puts("");
	}
	return 0;
}
