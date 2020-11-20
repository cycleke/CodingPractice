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
  ll ans = 0, cnt = 0;
  vi a(n);
  for (int i = n - 1; ~i; --i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cnt += a[i] / 2;
    if (a[i] % 2 == 1 && cnt > 0) {
      ans += 1;
      cnt -= 1;
    }
  }
  ans += 2 * cnt / 3;
  cout << ans << "\n";
  return 0;
}
