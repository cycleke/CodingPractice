#include <bits/stdc++.h>
using namespace std;

int A[100010], pos[10005];

inline int geti(int &a) {
	a = 0; char c = getchar(); bool sign = 0;
	while (c < '0' || c > '9') sign |= (c == '-') , c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	if (sign) a = -a;
	return a;
}

struct node {
	int l, r, id;
	void Read(const int &a) {
		geti(l); geti(r); id = a;
	}
	bool operator < (const node &A) const {
		return r < A.r;
	}
}op[100010];

int C[100010], ans[100010];

void Add(int x, const int &val) {
	while (x < 100010) {
		C[x] += val;
		x += x & -x;
	}
}

int Sum(int x) {
	int s = 0;
	while (x) {
		s += C[x];
		x -= x & -x;
	}
	return s;
}

int main() {
	int n, q;
	geti(n); geti(q);
	for (int i = 1; i <= n; ++i) geti(A[i]);
	memset(pos, 0, sizeof pos);
	for (int i = 0; i < q; ++i) op[i].Read(i);
	sort(op, op + q);
	for (int i = 1,j = 0; i <= n && j < q; ++i) {
		if (pos[A[i]]) {
			Add(pos[A[i]], -1); 
			Add(i, 1);
		} else {
			Add(i, 1); 
		}
		pos[A[i]] = i;
		while (j <= q && op[j].r == i) {
			ans[op[j].id] = Sum(op[j].r) - Sum(op[j].l - 1);
			++j;
		}
	}
	for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
	return 0;
}
