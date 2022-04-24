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

// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, a;
  cin >> n >> a;
  if (a < n - 2) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  cout << "POSSIBLE\n";
  switch (n) {
  case 3:
    cout << "0 0\n1 0\n0 " << a << "\n";
    break;
  case 4:
    cout << "0 0\n1 0\n1 1\n0 " << a - 1 << "\n";
    break;
  case 5:
    cout << "0 0\n1 0\n2 2\n1 1\n0 " << a - 2 << "\n";
    break;
  default:
    cout << "0 " << a - n + 4 << "\n";
    for (int i = 1; i < (n + 1) / 2; ++i) {
      cout << i << " ";
      if (i & 1) {
        cout << "1\n";
      } else if (i < (n - 1) / 2 || (n & 3) == 3) {
        cout << "2\n";
      } else {
        cout << "1\n";
      }
    }
    for (int i = n / 2 - 1; i >= 0; --i) {
      cout << i << " ";
      if (i & 1) {
        cout << "0\n";
      } else {
        cout << "1\n";
      }
    }
    break;
  }
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
