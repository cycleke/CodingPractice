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

  int a[6], b[6];
  for (int i = 0; i < 6; ++i) cin >> a[i];
  for (int i = 0; i < 6; ++i) cin >> b[i];

  int cnt = 0;
  for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 6; ++j) cnt += a[i] > b[j];

  int tot = 36, g = __gcd(cnt, tot);
  cout << cnt / g << "/" << tot / g << "\n";

  return 0;
}
