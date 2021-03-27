#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

const int MAXN = 1e5 + 3;

int a[MAXN], a0[MAXN], a1[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, ans = 0, ss;
  cin >> n;

  for (int i = 0; i < n; ++i) cin >> a[i];

  static auto gao = [](int *a, int n) {
    if (n == 0) return 0;
    int ans = 1, pre = a[0];
    for (int i = 1; i < n; pre = a[i++]) {
      ans += a[i] != pre;
      // debug(i, pre, a[i], ans);
    }
    return ans;
  };

  int n0 = 0, n1 = 0;
  for (int s = 0; s < (1 << n); ++s) {
    n0 = 0, n1 = 0;
    for (int i = 0; i < n; ++i) ((s >> i & 1) ? a1[n1++] : a0[n0++]) = a[i];
    int sum = gao(a0, n0) + gao(a1, n1);
    if (sum > ans) {
      ss = s;
      ans = sum;
    }
  }

  debug(ss);
  n0 = 0, n1 = 0;
  for (int i = 0; i < n; ++i) ((ss >> i & 1) ? a1[n1++] : a0[n0++]) = a[i];
  for (int i = 0; i < n0; ++i) debug(a0[i]);
  for (int i = 0; i < n1; ++i) debug(a1[i]);
  cout << ans << "\n";

  return 0;
}
