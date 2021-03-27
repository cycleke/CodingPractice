#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

constexpr int MAXN = 1e3 + 3;

int a[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN], u[MAXN][MAXN], d[MAXN][MAXN];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
      if (a[i][j]) {
        l[i][j] = j > 0 ? l[i][j - 1] + 1 : 1;
        u[i][j] = i > 0 ? u[i - 1][j] + 1 : 1;
      } else {
        l[i][j] = u[i][j] = 0;
      }
    }
  for (int i = n - 1; ~i; --i)
    for (int j = m - 1; ~j; --j) {
      if (a[i][j]) {
        r[i][j] = j + 1 < m ? r[i][j + 1] + 1 : 1;
        d[i][j] = i + 1 < n ? d[i + 1][j] + 1 : 1;
      } else {
        r[i][j] = d[i][j] = 0;
      }
    }

  int cnt = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (!a[i][j]) continue;

      static auto gao = [](int l1, int l2) {
        if (l1 <= 1 || l2 <= 1) return 0;
        return min(l1, l2 / 2) - 1 + min(l1 / 2, l2) - 1;
      };

      cnt += gao(l[i][j], u[i][j]);
      cnt += gao(l[i][j], d[i][j]);
      cnt += gao(r[i][j], u[i][j]);
      cnt += gao(r[i][j], d[i][j]);
    }
  cout << cnt << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 1;
  for (cin >> o_o; v_v <= o_o; ++v_v) {
    cout << "Case #" << v_v << ": ";
    solve();
  }
  return 0;
}
