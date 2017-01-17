#include <cstdio>
#include <cstring>
int dp[1003][1029], cnt[12];
int main() {
	int __, i, j, k, end, t, mo, n;
	char str[12], ch;
	scanf("%d", &__);
	while (__--) {
		for (n = 0; (ch = getchar()) < '0';);
		for (str[n++] = ch; '-' < (ch = getchar());)
			str[n++] = ch;
		scanf("%d", &mo);
		str[n] = 0;
		memset(dp, 0, sizeof dp);
		memset(cnt, 0, sizeof cnt);
		dp[0][0] = 1, end = 1 << n;
		for (j = 1; j < end; ++j)
			for (i = 0; i < mo; ++i)
				for (k = 0; k < n; ++k)
					if (j >> k & 1)
						dp[i][j] += dp[(i * 10 + str[k] - '0') % mo][j ^ (1 << k)];
		t = dp[0][end - 1];
		for (i = 0; i < n; ++i)
			t /= ++cnt[str[i] - '0'];
		printf("%d\n", t);
	}
	return 0;
}
