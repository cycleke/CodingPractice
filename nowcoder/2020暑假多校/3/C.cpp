#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;

void prework() {}

void solve() {
  static const int N = 20;
  static double x[N], y[N], d[N];
  static double EPS = 1e-3, FIRST = 1, SECOND = 6;

  for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];

  double cross = x[N - 1] * y[0] - x[0] * y[N - 1];
  for (int i = 0; i < N - 1; ++i) cross += x[i] * y[i + 1] - x[i + 1] * y[i];

  if (cross < 0) {
    reverse(x, x + N);
    reverse(y, y + N);
  }

  static auto dist = [](int p, int q) {
    double dx = x[p] - x[q];
    double dy = y[p] - y[q];
    return sqrt(dx * dx + dy * dy);
  };

  d[0] = dist(0, N - 1);
  for (int i = 1; i < N; ++i) d[i] = dist(i, i - 1);
  if (fabs(d[N - 1] - FIRST) < EPS && fabs(d[0] - SECOND) < EPS) {
    cout << "right\n";
    return;
  }
  for (int i = 1; i < N; ++i)
    if (fabs(d[i - 1] - FIRST) < EPS && fabs(d[i] - SECOND) < EPS) {
      cout << "right\n";
      return;
    }
  cout << "left\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
