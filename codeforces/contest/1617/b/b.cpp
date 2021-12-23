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

constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n;
  cin >> n;
  if (n % 2 == 0) {
    cout << "2 " << n - 3 << " 1\n";
  } else {
    int x = (n - 1) / 2;
    if (x % 2 == 0) {
      cout << x - 1 << " " << x + 1 << " 1\n";
    } else {
      cout << x - 2 << " " << x + 2 << " 1\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) { solve(); }
  return 0;
}
