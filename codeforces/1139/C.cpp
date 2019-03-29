#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 3;
const int MOD = 1e9 + 7;
int f[MAXN], size[MAXN];

inline int gf(int x) { return (x == f[x]) ? x : f[x] = gf(f[x]); }

inline int ModPow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = 1ll * res * a % MOD;
    }
    a = 1ll * a * a % MOD;
    b >>= 1;
  }
  return res;
}

int main() {

  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    f[i] = i;
    size[i] = 1;
  }
  for (int i = 1; i < n; ++i) {
    int u, v, type;
    scanf("%d%d%d", &u, &v, &type);
		if (type == 1) {
			continue;
		}
    u = gf(u);
    v = gf(v);
    if (u != v) {
      f[u] = v;
      size[v] += size[u];
    }
  }
  int ans = ModPow(n, k);
  for (int i = 1; i <= n; ++i) {
    if (gf(i) != i) {
      continue;
    }
    ans = (ans - ModPow(size[i], k) + MOD) % MOD;
  }
  printf("%d\n", ans);

  return 0;
}
