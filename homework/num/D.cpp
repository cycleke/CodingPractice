#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
int dig[20];
const int Mod = 2520;
LL dp[20][Mod][50];
int f[Mod];

void init() {
	int tot = 0;
	memset(dp, -1, sizeof(dp));
	memset(f, 0, sizeof(f));
	for (int i = 1; i < Mod; ++i)
		if (!(Mod % i)) {
			f[i] = ++tot;
		}
}

template<class T>
T readint(T &a) {
	a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

int gcd(int a,int b) {
	return b ? gcd(b, a % b) : a;
}

inline int lcm(const int& a,const int& b) {
	return a / gcd(a,b) * b;
}

LL dfs(const int& pos,const int& mod,const int& lc, const bool& limited) {
	if (!pos) 
		return mod % lc == 0;
	LL &tmp = dp[pos][mod][f[lc]];
	if (!limited && ~tmp) return tmp;
	int end = limited ? dig[pos] : 9, nlc;
	LL ret = 0;
	for (int i = 0; i <= end; ++i) {
		nlc = lc;
		if (i) nlc = lcm(i,lc);
		ret += dfs(pos - 1, (mod * 10 + i) % Mod, nlc, limited && i == end);
	}
	if (!limited) tmp = ret;
	return ret;
}

LL Cal(LL n) {
	if (!n) return 1;
	int len = 0;
	while (n) {
		dig[++len] = n % 10;
		n /= 10;
	}
	return dfs(len, 0, 1, 1);
}

int main() {
	int T; LL a, b;
	init();
	readint(T);
	while(T--) {
		readint(a); readint(b);
		cout << Cal(b) - Cal(a - 1) << endl;
	}
	return 0;
}
