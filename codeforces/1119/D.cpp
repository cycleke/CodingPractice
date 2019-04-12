#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;
typedef vector<pii> vpii;

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  ll a[n], d[n + 1], s[n + 1];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a, a + n);
  for (int i = 1; i < n; ++i) {
    d[i] = a[i] - a[i - 1];
  }
  sort(d + 1, d + n);
  s[0] = 0;
  d[n] = d[0] = 0;
  for (int i = 1; i <= n; ++i) {
    s[i] = s[i - 1] + d[i];
  }
  int m;
  cin >> m;
  while (m--) {
    ll l, r;
    cin >> l >> r;
    int p = upper_bound(d + 1, d + n, r - l) - d - 1;
    cout << s[p] + ll(n - p) * (r - l + 1) << " ";
  }

  return 0;
}
