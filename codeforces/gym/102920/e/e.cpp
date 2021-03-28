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

  int n, x;
  bool succ = false, ans = true;

  for (cin >> n; n > 1; --n) {
    cin >> x;
    if (succ) {
      if (x == 0 || x == 2) {
        succ = true;
      } else if (x == 1) {
        succ = false;
      } else {
        ans = false;
        break;
      }
    } else {
      if (x == 1) {
        succ = true;
      } else if (x == 0) {
        succ = false;
      } else {
        ans = false;
        break;
      }
    }
  }
  cin >> x;

  ans &= succ ? x == 1 : x == 0;

  cout << (ans ? "YES\n" : "NO\n");

  return 0;
}
