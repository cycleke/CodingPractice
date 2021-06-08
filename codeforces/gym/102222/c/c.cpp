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

void solve() {
  int n, m;
  static char a[MAXN], b[MAXN], c[MAXN];
  cin >> n >> m >> a >> b >> c;
  int delta = b[0] - a[0];
  for (int i = 0; i < m; ++i) {
    c[i] -= delta;
    if (c[i] > 'Z') c[i] -= 26;
    if (c[i] < 'A') c[i] += 26;
  }
  cout << c << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
