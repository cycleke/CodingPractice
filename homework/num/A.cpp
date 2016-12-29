#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
template<class T>
T readint(T& a) {
	a = 0; char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
}
typedef long long LL;
LL dp[21][10][2];
int dig[21];
#define clr(a,b) memset(a,b,sizeof(a))

int f(LL n) {
	int tot = 0;
	while (n) {
		dig[++tot] = n % 10;
		n /= 10;
	}
	return tot;
}

LL dfs(int pos, int per, bool Rigth, bool limited) {
	if (!pos) return Rigth;
	LL &tmp = dp[pos][per][Rigth];
	if (!limited && ~tmp) return tmp;
	int end = limited?dig[pos]:9;
	LL ret = 0;
	for (int i = 0; i <= end; ++i)
		ret += dfs(pos-1,i,Rigth || (per == 4 && i == 9),limited && i == end);
	if (!limited) tmp = ret;
	return ret;
}

int main() {
	LL N; int T, tot;
	readint(T);
	clr(dp,-1);
	while(T--) {
		readint(N);
		tot = f(N);
		cout << dfs(tot, 0, 0, 1) << endl;
	}
	return 0;
}
