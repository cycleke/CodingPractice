#include <cstdio>
#include <cstring>

int dp[42][42][42][42];
int x[5],co[42][5], n;

int cal(int basket, int cnt) {
	if (~dp[x[1]][x[2]][x[3]][x[4]])
	  return dp[x[1]][x[2]][x[3]][x[4]];
	int &t = dp[x[1]][x[2]][x[3]][x[4]], tmp, b;
	for (int i = 1; i <= 4; ++i) {
		tmp = 0; ++x[i];
		if (x[i] <= n) {
			b = 1 << co[x[i]][i];
			if (basket & b)
			  tmp = cal(basket & (~b), cnt - 1) + 1;
			else if (cnt < 4)
			  tmp = cal(basket | b, cnt + 1);
		}
		--x[i];
		if (t < tmp) t = tmp;
	}
	return t;
}

int main() {
	while (scanf("%d", &n) ^ EOF) {
		if (!n) break;
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= 4; ++j)
			scanf("%d", co[i] + j);
		memset(x, 0, sizeof x);
		memset(dp, -1, sizeof dp);
		printf("%d\n", cal(0,0));
	}
	return 0;
}
