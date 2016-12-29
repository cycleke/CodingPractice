#include <cstdio>
#include <cstring>

const int N = 105, M = 3005;
int dp[N][M], nxt[N][M];
const int a[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

int ina; char inc;
inline int geti() {
	while ((inc = getchar()) < '0' || inc > '9'); ina = inc - '0';
	while ((inc = getchar()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0';
	return ina;
}

int main() {
	int Case = 0, n, m, i, j, k, _i, _j, maxlen;
	while (n = geti()) {
		m = geti(); maxlen = 0;
		memset(dp, -1, sizeof dp);
		memset(nxt, -1, sizeof nxt);
		dp[0][0] = 0;
		for (i = 0; i < n; ++i)
		  for (j = 0; j < m; ++j) 
			if (~dp[i][j]){
				for (k = 9; ~k; --k) 
				  if (i + a[k] <= n) {
					  _i = i + a[k], _j = (j * 10  + k) % m;
					  if (dp[i][j] + 1 > dp[_i][_j]) {
						  dp[_i][_j] = dp[i][j] + 1;
						  if (dp[_i][_j] > maxlen && (!_j)) maxlen = dp[_i][_j];
					  }
				  }
			}
		for (i = n; ~i; --i)
		  for (j = 0; j < m; ++j)
			if (~dp[i][j]) {
				if ((dp[i][j] ^ maxlen) || j) {
					for (k = 9; ~k; --k) 
					  if (i + a[k] <= n){
						  _i = i + a[k], _j = (j * 10 + k) % m;
						  if (dp[_i][_j] == dp[i][j] + 1 && (~nxt[_i][_j])) {
							  nxt[i][j] = k; break;
						  }
					  }
				} else nxt[i][j] = 10;
			}
		printf("Case %d: ", ++Case);
		if (maxlen){
			i = 0, j = 0;
			while (nxt[i][j] ^ 10) {
				printf("%d", nxt[i][j]);
				_i = i + a[nxt[i][j]]; _j = (j * 10 + nxt[i][j]) % m;
				i = _i, j = _j;
			}
			puts("");
		} else puts((n >= a[0]) ? "0" : "-1");
	}
}
