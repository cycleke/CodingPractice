#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e5 + 5;

struct data {
	bool A[105];
	data() { memset(A, 0, sizeof A); }
	data operator | (const data &x) const {
		data c;
		for (int i = 0; i < 105; ++i)
			c.A[i] = A[i] || x.A[i];
		return c;
	}
	void change(const int &a) {
		memset(A, 0, sizeof A);
		A[a] = 1;
	}
	int Cnt() const {
		int s = 0;
		for (int i = 0; i < 105; ++i) s += A[i];
		return s;
	}
}C[Maxn << 2];
bool ly[Maxn << 2];

void Up(const int &u) {
	C[u] = C[u<<1] | C[u<<1|1];
}

void Down(const int &u) {
	if (ly[u]) {
		C[u<<1] = C[u<<1|1] = C[u];
		ly[u<<1] = ly[u<<1|1] = 1;
		ly[u] = 0;
	}
}

void Build(int u, int l, int r) {
	if (l ^ r) {
		int mid = (l + r) >> 1;
		Build(u<<1, l, mid);
		Build(u<<1|1, mid + 1, r);
		Up(u);
	} else {
		int a; scanf("%d", &a);
		C[u].change(a);
	}
}

void Update(int u, int l, int r, int x, int y, const int &val) {
	if (l == x && r == y) {
		C[u].change(val); ly[u] = 1;
		return;
	}
	Down(u);
	int mid = (l + r) >> 1;
	if (y <= mid) Update(u<<1, l, mid, x, y, val);
	else if (x > mid) Update(u<<1|1, mid + 1, r, x, y, val);
	else {
		Update(u<<1, l, mid, x, mid, val); Update(u<<1|1, mid + 1, r, mid + 1, y, val);
	}
	Up(u);
}

data Query(int u, int l, int r, int x, int y) {
	if (l == x && r == y) {
		return C[u];
	}
	Down(u);
	int mid = (l + r) >> 1;
	if (y <= mid) return Query(u<<1, l, mid, x, y);
	else if (x > mid) return Query(u<<1|1, mid + 1, r, x, y);
	else return Query(u<<1, l, mid, x, mid) | Query(u<<1|1, mid + 1, r, mid + 1, y);
}

int main() {
	int N, M, Q, l, r, x; char op[5];
	scanf("%d%d", &N, &M);
	Build(1, 1, N);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%s%d%d", op, &l, &r);
		if (*op == 'M') {
			scanf("%d", &x);
			Update(1, 1, N, l, r, x);
		} else {
			printf("%d\n", Query(1, 1, N, l, r).Cnt());
		}
	}
	return 0;
}
