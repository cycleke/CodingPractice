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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, p;
  ll area = 0, cur_area;

  for (cin >> n; n; --n) {
    ll x0, y0, cx, cy, lx, ly;
    cin >> p >> x0 >> y0;
    lx = x0, ly = y0, cur_area = 0;
    for (int i = 1; i < p; ++i) {
      cin >> cx >> cy;
      cur_area += cx * ly - cy * lx;
      lx = cx, ly = cy;
    }
    cur_area += x0 * ly - y0 * lx;
    area += abs(cur_area);
  }
  cout << area / 2 << "\n";

  return 0;
}
