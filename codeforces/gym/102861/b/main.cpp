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

constexpr int MAXN = 10;

bitset<MAXN> a[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;

  static auto gao = [&]() {
    int d, l, r, c;
    cin >> d >> l >> r >> c;
    --r, --c;
    if (d == 0) {
      for (int i = 0; i < l; ++i, ++c) {
        if (c >= MAXN || a[r][c]) return false;
        a[r][c] = 1;
      }
    } else {
      for (int i = 0; i < l; ++i, ++r) {
        if (r >= MAXN || a[r][c]) return false;
        a[r][c] = 1;
      }
    }
    return true;
  };

  bool ok = true;
  for (cin >> n; ok && n; --n) ok = gao();
  cout << (ok ? "Y\n" : "N\n");
  return 0;
}
