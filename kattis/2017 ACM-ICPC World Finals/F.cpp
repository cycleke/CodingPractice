#include <cstdio>
#include <cstring>

const int n = 257;
const int N = 333;
const long long inf = 1e18;

int a[N];
long long f[N][N], cost[N][N];

template<class T>
inline T min(const T &a, const T &b) {
  return a < b ? a : b;
}

int main() {
  int d, p;
  while (scanf("%d %d", &d, &p) != EOF) {
    ++p;
    memset(a, 0, sizeof (a));
    for (int i = 0; i < d; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      a[x + 1] = y;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        cost[i][j] = 0;
        for (int k = i + 1; k < j; ++k) {
          int dist = min(i == 0 ? n : k - i, j == n ? n : j - k);
          cost[i][j] += a[k] * 1ll * dist * dist;
        }
      }
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= p; ++j) {
        f[i][j] = inf;
      }
    }
    f[0][0] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        long long t = f[i][j];
        if (t == inf) {
          continue;
        }
        for (int k = i + 1; k <= n; ++k) {
          f[k][j + 1] = min(f[k][j + 1], t + cost[i][k]);
        }
      }
    }
    printf("%lld\n", f[n][p]);
  }
  return 0;
}
