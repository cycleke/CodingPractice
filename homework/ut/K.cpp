#include <map>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> pll;
pll A[200010];
LL B[200010], C[200010];
LL BIT[200010];
int n, len;
map<LL, int> Cnt;
map<LL, int>::iterator it;

template<class T>
T geti(T &a) {
	a = 0; char c = getchar(); bool sign = 0;
	while (c < '0' || c > '9') sign = sign | (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	if (sign) a = -a;
	return a;
}

void Add(int x) {
	while (x < 200010) {
		++BIT[x];
		x += x & -x;
	}
}

LL Sum(int x) {
	LL s = 0;
	while (x) {
		s += BIT[x];
		x -= x & -x;
	}
	return s;
}

inline int findi(const LL &val) {
	int l = 0, r = len, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (val == C[mid]) break;
		if (val < C[mid]) r = mid - 1;
		else l = mid + 1;
	}
	return mid;
}

int main() {
	LL u, v, k, b;
	geti(n); geti(u); geti(v);
	for (int i = 0; i < n; ++i) {
		geti(k); geti(b);
		A[i] = make_pair(k * u + b, k * v + b);
		it = Cnt.find(k * u + b);
		if (it == Cnt.end()) Cnt[k * u + b] = 1;
		else ++it->second;
	}
	sort(A, A + n);
	for (int i = 0; i < n; ++i) C[i] = B[i] = A[i].second;
	sort(C, C + n);
	len = unique(C, C + n) - C - 1;
	LL ans = 0;
	if (u ^ v){ 
		for (int i = 0; i < n; ++i) {
			k = findi(B[i]) + 1;
			Add(k);
			ans += i - Sum(k - 1);
		}
	} else {
		for (it = Cnt.begin(); it != Cnt.end(); ++it) 
			ans += (it->second) * (it->second - 1) >> 1;
	}
	printf("%I64d\n", ans);
	return 0;
}
