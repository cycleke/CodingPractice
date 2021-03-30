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

  int n, x0, y0, cur_x, cur_y, pre_x, pre_y;
  while (cin >> n) {
    ll area = 0;
    cin >> x0 >> y0;
    pre_x = x0, pre_y = y0;
    for (int i = 1; i < n; ++i) {
      cin >> cur_x >> cur_y;
      area += 1ll * cur_x * pre_y - 1ll * cur_y * pre_x;
      pre_x = cur_x, pre_y = cur_y;
    }
    area += 1ll * x0 * pre_y - 1ll * y0 * pre_x;
    if (area < 0) area = -area;
    cout << area / 2 << (area & 1 ? ".50\n" : ".00\n");
  }

  return 0;
}
