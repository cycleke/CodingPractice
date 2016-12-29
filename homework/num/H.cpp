#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int f[33][33];
int dig[33];
void init() {
//i->cnt1 j->len
	for (int i = 0; i <= 32; ++i) f[i][0] = 1;
	for (int i = 1; i <= 32; ++i)
		for (int j = 1; j <= i; ++j)
			f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
}

int Cal(int n,const int& k,const int& b) {
	int len, ans, tot;
	len = ans = tot = 0;
	while (n) {
		dig[++len] = n % b;
		n /= b;
	}
	for (int i = len; i; --i) {
		if (dig[i] == 1) {
			ans += f[i - 1][k - tot];
			++tot;
			if (tot >= k) break;
		} else if(dig[i] > 1) {
			ans += f[i][k - tot];
			break;
		}
	}
	if (tot == k) ++ans;
	return ans;
}

int main() {
	int x, y, k, b;
	scanf("%d%d%d%d", &x, &y, &k, &b);
	init();
	printf("%d", Cal(y,k,b) - Cal(x - 1,k,b));
	return 0;
}
