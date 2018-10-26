#include <bits/stdc++.h>
using namespace std;

#define ZERO(a) memset(a, 0, sizeof(a))

const int MAXN = 2001;
typedef int Array[MAXN][MAXN];

bool a[MAXN][MAXN];
Array f, h, l, r, L, R;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      if ((i + j) % 2 == 0)
        a[i][j] ^= 1;
    }

  int max_square = 0;
  int max_rectangle = 0;
  auto getMax =
    [](int &a, const int &b) {
      if (a < b)
        a = b;
    };
  auto getAnswer =
    [&]() {
      ZERO(f);
      ZERO(h);
      ZERO(l);
      ZERO(r);
      ZERO(L);
      ZERO(R);
      for (int i = 1; i <= m; i++) {
        R[0][i] = m + 1;
      }
      for (int i = 1; i <= n; i++) {
        int pre = 0;
        for (int j = 1; j <= m; j++) {
          if (a[i][j]) {
            l[i][j] = pre;
          } else {
            pre = j;
            L[i][j] = 0;
          }
        }
        pre = m + 1;
        for (int j = m; j >= 1; j--) {
          if (a[i][j]) {
            r[i][j] = pre;
          } else {
            pre = j;
            R[i][j] = m + 1;
          }
        }
      }
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          if (!a[i][j]) continue;
          f[i][j] = min({f[i - 1][j - 1], f[i - 1][j], f[i][j - 1]}) + 1;
          h[i][j] = h[i - 1][j] + 1;
          L[i][j] = max(L[i - 1][j], l[i][j]);
          R[i][j] = min(R[i - 1][j], r[i][j]);
          getMax(max_square, f[i][j] * f[i][j]);
          getMax(max_rectangle, h[i][j] * (R[i][j] - L[i][j] - 1));
        }
      }
    };

  getAnswer();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      a[i][j] ^= 1;
  getAnswer();
  cout << max_square << endl << max_rectangle << endl;
  return 0;
}
