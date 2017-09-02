#include <cstdio>
#include <algorithm>

const int maxn = 4e5, maxm = 2e7, MOD = 998244353;
typedef int arrn[maxn], arrm[maxm];

int tot = 1;
arrn v, ls, rs;
arrm str, w, s[6], pre;

inline int nextInt() {
  register int a;
  register char c, f = 0;
  do c = getchar(); while (c < '-');
  if (c == '-') f = 1, c = getchar();
  a = c ^ 48;
  while (47 < (c = getchar()))
    a = (a << 3) + (a << 1) + (c ^ 48);
  return f ? -a : a;
}

inline int rect(int c, int k) {
  return s[c][k] != 0 ? s[c][k] : (s[c][k] = ++tot,
                                   pre[tot] = s[c][pre[k]],
                                   tot);
}

int main() {
  int n = nextInt(), m = nextInt();
  for (int i = 1; i <= n; ++i) {
    v[i] = nextInt() - 1;
    if (s[v[i]][1] == 0) {
      s[v[i]][1] = ++tot;
      pre[tot] = 1;
    }
    ++w[s[v[i]][1]];
  }
  while (m--) {
    int operation = nextInt();
    if (operation == 1) {
      int a = nextInt(), b = nextInt(), t = 0, p;
      rs[a] = b, ls[b] = a;
      for (int i = a; t < 50 && i != 0; i = ls[i])
        str[++t] = v[i];
      std::reverse(str + 1, str + t + 1);
      p = t;
      for (int i = b; p - t < 50 && i != 0; i = rs[i])
        str[++p] = v[i];
      for (int i = 2; i <= 50 && i <= p; ++i) {
        int x = 1, j = std::max(1, t - i + 2);
        for (int k = i; --k; ++j) x = s[str[j]][x];
        for (; j <= p && j - t < i; ++j) {
          x = rect(str[j], x);
          ++w[x];
          x = pre[x];
        }
      }
    } else if (operation == 2) {
      int a = nextInt(), b = rs[a];
      for (int i = 1, k = a; i < 50 && k != 0; k = ls[k], ++i) {
        int x = 1;
        for (int p = k, j = 1; j <= 50 && p != 0; p = rs[p], ++j) {
          x = s[v[p]][x];
          if (j > i) --w[x];
        }
      }
      rs[a] = ls[b] = 0;
    } else {
      int k = 0;
      char c;
      while ((c = getchar()) < 48);
      while (c > 47)
        str[++k] = (c ^ 48) - 1, c = getchar();
      int ans = 1;
      int t = nextInt();
      for (int i = 1, x = 1; i <= k; ++i) {
        if (s[str[i]][x] == 0) {
          ans = 0;
          break;
        }
        x = s[str[i]][x];
        if (i >= t) {
          ans = 1ll * ans * w[x] % MOD;
          x = pre[x];
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
