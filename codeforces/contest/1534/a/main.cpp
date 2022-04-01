#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int MAXN = 50 + 3;

char grid[MAXN][MAXN];

void solve() {
  int n, m;
  cin >> n >> m;

  bool w[2] = {0, 0}, r[2] = {0, 0};

  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    for (int j = 0; j < m; ++j) {
      switch (grid[i][j]) {
      case 'R':
        r[(i + j) & 1] = 1;
        break;
      case 'W':
        w[(i + j) & 1] = 1;
        break;
      default:
        break;
      }
    }
  }

  if ((w[0] || r[1]) && (w[1] || r[0])) {
    cout << "NO\n";
    return;
  }

  int d = w[0] || r[1] ? 1 : 0;
  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j + d) & 1) {
        cout << 'W';
      } else {
        cout << 'R';
      }
    }
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
