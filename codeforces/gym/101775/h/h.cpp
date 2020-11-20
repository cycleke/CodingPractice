// by OwenCreeper
#include "bits/stdc++.h"
#define N 1000000
using namespace std;
int Case = 0, p[N + 5], c[N + 5], cnt, dp[N + 5][2], a[N + 5], x, y, n;
bool ckdis() {
	int lc = 0;
	for (int i = 1; i <= cnt; i++) 
		if (p[i] == 2 || p[i] == 0) {
			lc += c[i];
			if (lc >= x) return 1;
		} else lc = 0;
	lc = 0;
	for (int i = 1; i <= cnt; i++) 
		if (p[i] == 2 || p[i] == 1) {
			lc += c[i];
			if (lc >= y) return 1;
		} else lc = 0;
	// puts("YES");
	return 0;
}
bool cklike() {
	for (int i = 1; i <= n; i++) 
		if (a[i] == 0) {
			dp[i][0] = dp[i - 1][0] + 1,
			dp[i][1] = 0;
			if (dp[i][0] >= x) return 0;
		} else if (a[i] == 1) {
			dp[i][0] = 0;
			dp[i][1] = dp[i - 1][1] + 1;
			if (dp[i][1] >= y) return 0;
		} else {
			if (dp[i - 1][0] + 1 >= x) {
				dp[i][0] = 0, dp[i][1] = 1;
				if (dp[i][1] >= y) return 0;
				continue;
			}
			if (dp[i - 1][1] + 1 >= y) {
				dp[i][1] = 0, dp[i][0] = 1;
				if (dp[i][0] >= x) return 0;
				continue;
			}
			dp[i][0] = dp[i][1] = 0;
		}
	return 1;
}
char s[N + 5];
int T;
void work() {
	scanf("%s", s);
	scanf("%d%d", &x, &y);
	Case++;
	printf("Case #%d: ", Case);
	n = strlen(s);
	cnt = 0;
	for (int i = 0; i < n; i++)
		if (s[i] == '?')
			a[i + 1] = 2;
		else
			if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
				a[i + 1] = 0;
			else
				a[i + 1] = 1;
	for (int i = 1; i <= n; i++)
		if (i == 1 || a[i] != a[i - 1])
			p[++cnt] = a[i], c[cnt] = 1;
		else
			c[cnt]++;
	// for (int i = 1; i <= cnt; i++)
	// 	printf("%d %d\n", p[i], c[i]);
	for (int i = 1; i <= cnt; i++)
		if (p[i] == 0 && c[i] >= x) {
			puts("DISLIKE");
			return ;
		} else 
		if (p[i] == 1 && c[i] >= y) {
			puts("DISLIKE");
			return ;
		}
	bool f1 = ckdis(), f2 = cklike();
	if (f1 && f2) puts("SURPRISE"); else
	if (f1) puts("DISLIKE"); else
	puts("LIKE");
}
int main(int argc, char const *argv[]) {
	scanf("%d", &T);
	while (T--) work();
	return 0;
}
