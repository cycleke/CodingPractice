#include <stdio.h>
inline void gi(int *a) {
	register char c;
	do c = getchar_unlocked(); while (c < 48);
	*a = c - 48;
	while (47 < (c = getchar_unlocked())) *a = (*a << 3) + (*a << 1) + c - 48;
}
int main() {
	static int n, x, dp[1025][1025], mod = 1e9 + 7;
	gi(&n);
	dp[0][0] = 1;
	while (n--) {
		gi(&x);
		x ^= 1023;
		for (register int i = 1023, ti, tj, unt; ~i; --i)
			if (unt = (ti = x | i) ^ i) {
				for (register int j = i; ; (--j) &= i) {
					tj = j - (j & x);
					dp[ti][tj] += dp[i][j];
					dp[ti][tj|unt] -= dp[i][j];
					if (dp[ti][tj] >= mod) dp[ti][tj] -= mod;
					if (dp[ti][tj|unt] < 0) dp[ti][tj|unt] += mod;
					if (!j) break;
				}
			}
	}
	printf("%d\n", dp[1023][0]);
	return 0;
}
