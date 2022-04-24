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

constexpr int kMaxN = 1e4;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, d, c, m;
  cin >> n >> d >> c >> m;

  static char line[kMaxN + 1];
  cin >> line;

  int dogs = 0;
  for (int i = 0; i < n; ++i) {
    dogs += line[i] == 'D';
  }

  if (dogs > d) {
    cout << "NO\n";
    return;
  }

  for (int i = 0; i < n && dogs; ++i) {
    if (line[i] == 'D') {
      if (d == 0) {
        cout << "NO\n";
        return;
      }

      d -= 1;
      c += m;
      dogs -= 1;
    } else {
      if (c == 0) {
        cout << "NO\n";
        return;
      }

      c -= 1;
    }
  }
  cout << "YES\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 0;
  for (cin >> o_o; o_o; --o_o) {
    cout << "Case #" << ++v_v << ": ";
    solve();
  }
  return 0;
}
