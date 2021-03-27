#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define ONLINE_JUDGE

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

const int MAXN = 1e5 + 3;

int a[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m = 1;
  cin >> n >> a[0];
  for (int i = 1, cnt = 0; i < n; ++i) {
    cin >> a[m];
    if (a[m] == a[m - 1]) {
      if (cnt == 0) ++m, cnt = 1;
    } else {
      ++m, cnt = 0;
    }
  }

  int ans = m, pre = -1, len = 0, mx = 0;
  for (int i = 1; i < m; ++i) {
    if (a[i] != a[i - 1]) {
      if (a[i] == pre) {
        if (len) {
          if (len > mx) mx = len;
          len = 0;
        }
      } else {
        ++len;
      }
      continue;
    }
    if (len > mx) mx = len;
    if (a[i] == pre && mx < 2) --ans;
    pre = a[i], len = mx = 0;
  }
  cout << ans << "\n";

  return 0;
}
