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

  int n, max_h;
  cin >> n >> max_h;
  int h[n], a[n];
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }
  int l = 1, r = n, ans = 1;
  while (l <= r) {
    int k = (l + r) / 2;
    for (int i = 0; i < k; ++i) {
      a[i] = h[i];
    }
    sort(a, a + k, greater<int>());
    ll sum = 0;
    for (int i = 0; i < k; i += 2) {
      sum += a[i];
    }
    if (sum <= max_h) {
      ans = k;
      l = k + 1;
    } else {
      r = k - 1;
    }
  }
  cout << ans << "\n";
  return 0;
}
