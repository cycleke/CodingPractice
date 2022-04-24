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

constexpr int kMaxN = 5e3;
constexpr int kMaxK = 1e6;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  static int b[kMaxN], f[kMaxK + 1];

  int n, k;
  cin >> n >> k;

  memset(f, 0x3f, (k + 1) * sizeof(f[0]));
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  f[0] = 0;
  int ans = 0x3f3f3f3f;
  for (int i = 0; i < n; ++i) {
    int sum = 0;
    for (int j = i; j < n; ++j) {
      sum += b[j];
      if (sum <= k) {
        ans = min(ans, j - i + 1 + f[k - sum]);
      } else {
        break;
      }
    }

    sum = 0;
    for (int j = i; j >= 0; --j) {
      sum += b[j];
      if (sum <= k) {
        f[sum] = min(f[sum], i - j + 1);
      } else {
        break;
      }
    }
  }

  if (ans == 0x3f3f3f3f) {
    cout << "-1\n";
  } else {
    cout << ans << "\n";
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
