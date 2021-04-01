#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e6 + 5, Mod = 772002+233;
typedef long long LL;

template<class T>
inline T geti(T &a) {
	a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

LL A[Maxn], C[Maxn], C2[Maxn];

void Add(LL *tr, int x, const LL &val) {
	while (x < Maxn) {
		tr[x] += val;
		x += x & -x;
	}
}

LL Sum(LL *tr, int x) {
	LL s = 0;
	while (x) {
		s += tr[x];
		x -= x & -x;
	}
	return s;
}

void Upd(LL *tr, int l, int r, const LL &val) {
	Add(tr, l, val); Add(tr, r + 1, -val);
}

int main() {
	LL N, Q, op, x, y, ans;
	geti(N); geti(Q);
	for (int i = 1; i <= N; ++i) geti(A[i]);
	for (int T = 0; T < Q; ++T) {
		geti(op);
		if (op == 1) {
			geti(x); geti(y);
			Upd(C, x, min(N, x + y), x + y);
			Upd(C2, x, min(N, x + y), 1);
		} else {
			geti(x);
			ans = Sum(C, x) + A[x];
			ans -= x * Sum(C2, x);
			ans %= Mod;
			printf("%d\n", (int)ans);
		}
	}
	return 0;
}
