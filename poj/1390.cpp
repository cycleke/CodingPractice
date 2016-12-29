#include <cstdio>
#include <cstring>

//Input
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false; while ((inc = getc()) < '0' || inc> '9') insign |= inc == '-';
	ina = inc - '0'; while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0';
	return insign ? -ina : ina;
}


const int N = 205;
int dp[N][N][N], color[N], len[N], pre[N], pos[N], Sum[N];
inline void SelfMax(int &a, const int &b) { if (a < b) a = b; }
inline int p2(const int &a) { return a * a; }
int main() {
	int n, pr, i, j, k, T = geti(), tot, a, Sizdp = sizeof dp, length, Case = 0;
	while (T--) {
		n = 0; pr = -1;
		for (k = tot = geti(); k; --k) {
			a = geti();
			if (a ^ pr) color[++n] = pr = a, len[n] = 1;
			else ++len[n];
		}

		memset(dp, 0, Sizdp); memset(pos, 0, sizeof pos); memset(Sum, 0, sizeof Sum);
		for (i = 1; i <= n; ++i) pre[i] = pos[color[i]], pos[color[i]] = i;
		for (i = n; i; --i) if (!Sum[i]) {
			j = i; k = 0;
			while (j) {
				Sum[j] = k; k += len[j];
				j = pre[j];
			}
		}
		for (length = 1; length <= n; ++length) 
		  for (i = 1;; ++i) {
			  if ((j = i + length - 1) > n) break;
			  for (k = 0; k <= tot; ++k) {
				  dp[i][j][k] = dp[i][j-1][0] + p2(len[j] + k);
				  for (a = pre[j]; a >= i; a = pre[a])
					SelfMax(dp[i][j][k], dp[i][a][k+len[j]] + dp[a+1][j-1][0]);
			  }
		  }
		printf("Case %d: %d\n", ++Case, dp[1][n][0]);
	}
	return 0;
}
