#include <cstdio>
#include <iostream>
using namespace std;

const int Mod = 1000000007;
int c[6];
int dp[16][16][16][16][16][6];

inline int getint() {
	int a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

void Add(int &a, const long long &b) {
	long long c = a + b;
	while (c >= Mod) c -=Mod;
	a = c;
}

int Cal(const int &a, const int &b, const int &c, const int &d, const int &e,const int &last) {
	if ((a|b|c|d|e) == 0) return 1;
	int &tmp = dp[a][b][c][d][e][last];
	if (tmp) return tmp;
	if (a) Add(tmp, (long long)Cal(a - 1, b, c, d, e, 1) * (a - (last == 2)));
	if (b) Add(tmp, (long long)Cal(a + 1, b - 1, c, d, e, 2) * (b - (last == 3)));
	if (c) Add(tmp, (long long)Cal(a, b + 1, c - 1, d, e, 3) * (c - (last == 4)));
	if (d) Add(tmp, (long long)Cal(a, b, c + 1, d - 1, e, 4) * (d - (last == 5)));
	if (e) Add(tmp, (long long)Cal(a, b, c, d + 1, e - 1, 5) * e);
	return tmp;
}

int main() {
	for (int i = getint(); i; --i) ++c[getint()];
	printf("%d", Cal(c[1],c[2],c[3],c[4],c[5],0));
	return 0;
}
