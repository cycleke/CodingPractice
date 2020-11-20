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
  vi C1(n + 1, INF), C2(n + 1, INF);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    int t = INF;
    for (int j = x - 1; j; j -= j & -j) {
      t = min(t, C1[j]);
    }
    ans = max(ans, i - t);
    t = INF;
    for (int j = n - x; j; j -= j & -j) {
      t = min(t, C2[j]);
    }
    ans = max(ans, i - t);

    for (int j = x; j <= n; j += j & -j) {
      C1[j] = min(C1[j], i);
    }
    for (int j = n + 1 - x; j <= n; j += j & -j) {
      C2[j] = min(C2[j], i);
    }
  }
  cout << ans << "\n";
  return 0;
}
