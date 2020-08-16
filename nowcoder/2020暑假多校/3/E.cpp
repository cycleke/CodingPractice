#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 3;

vector<pair<vi, vi>> ok[7];

void prework() {
  for (int n = 4; n <= 6; n += 2) {
    vi p(n);
    iota(p.begin(), p.end(), 0);
    vector<vi> q;
    do {
      bool flag = false;
      for (int i = 0; i < n; ++i) {
        if (p[i] == i || p[p[i]] != i) {
          flag = true;
          break;
        }
      }
      if (flag) continue;
      q.push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    for (vi a : q) {
      for (vi b : q) {
        if (a < b) {
          bool flag = true;
          for (int i = 0; i < n; ++i)
            if (a[i] == b[i]) {
              flag = false;
              break;
            }
          if (flag) ok[n].emplace_back(a, b);
        }
      }
    }
  }
}

void solve() {
  int n;
  cin >> n;
  static int a[MAXN];
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a, a + n);

  static ll dp[MAXN];
  static auto cost = [&](int l, int r) {
    static int z[7];
    for (int i = l; i < r; ++i) z[i - l] = a[i];
    ll res = LLONG_MAX;
    for (auto &a : ok[r - l]) {
      ll sum = 0;
      for (int s = 0; s < r - l; ++s) {
        sum += a.first[s] < s ? abs(z[a.first[s]] - z[s]) : 0;
        sum += a.second[s] < s ? abs(z[a.second[s]] - z[s]) : 0;
      }
      res = min(res, sum);
    }
    return res;
  };
  static auto cmin = [&](ll &a, ll b) { a > b ? a = b : 0; };

  dp[0] = 0;
  memset(dp + 1, 0x3f, n * sizeof(ll));
  for (int i = 0; i < n; ++i) {
    if (i + 4 <= n) cmin(dp[i + 4], dp[i] + cost(i, i + 4));
    if (i + 6 <= n) cmin(dp[i + 6], dp[i] + cost(i, i + 6));
  }
  cout << dp[n] << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
