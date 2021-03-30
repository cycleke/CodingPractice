
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

constexpr int MAXK = 16;
constexpr int MAXN = 1 << MAXK | 3;

char s[MAXN];
bitset<MAXK> sum;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int k, n, s0, brk;
  while (cin >> k >> s) {
    sum.reset();
    s0 = 0, n = 1 << k;
    for (int i = 1; i < n; ++i) {
      s0 ^= s[i] - '0';
      if (__builtin_popcount(i) <= 1) continue;
      for (int j = 0; j < k; ++j)
        (i >> j & 1) && (sum[j] = sum[j] ^ (s[i] - '0'));
    }
    brk = 0;
    for (int i = 0; i < k; ++i) (sum[i] != s[1 << i] - '0') && (brk |= 1 << i);
    if (!brk) {
      cout << (s0 != s[0] - '0' ? "d(0) is changed\n" : "good\n");
    } else {
      cout << (s0 != s[0] - '0' ? "d(" + to_string(brk) + ") is changed\n"
                                : "broken\n");
    }
  }

  return 0;
}
