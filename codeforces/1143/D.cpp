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

  ll n, k, a, b;
  cin >> n >> k >> a >> b;
  ll mi = 0x3f3f3f3f3f3f3f3fll;
  ll mx = -1;
  ll nk = n * k, l1 = k + a - b, l2 = k - a - b;
  for (int step = 0; step < n; ++step) {
    ll c1 = nk / __gcd(nk, l1);
    ll c2 = nk / __gcd(nk, l2);
    mx = max(mx, max(c1, c2));
    mi = min(mi, min(c1, c2));
    l1 += k;
    l2 += k;
  }
  cout << mi << " " << mx << '\n';
  return 0;
}
