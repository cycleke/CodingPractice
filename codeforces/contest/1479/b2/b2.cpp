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

int n, a[MAXN], pos[MAXN], nxt[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  memset(pos + 1, 0x63, sizeof(int) * n);
  for (int i = n - 1; ~i; --i) {
    nxt[i] = pos[a[i]];
    pos[a[i]] = i;
  }
  int x = -1, y = -1, ans = 0;
  for (int i = 0; i < n; ++i) {
    debug(x, y, ans, a[i]);
    if ((~x) && a[x] == a[i]) {
      x = i;
    } else if ((~y) && a[y] == a[i]) {
      y = i;
    } else {
      ++ans;
      ((x == -1 || (y != -1 && nxt[x] > nxt[y])) ? x : y) = i;
    }
  }
  cout << ans << "\n";

  return 0;
}
