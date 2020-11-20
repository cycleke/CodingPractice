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

const int MAXN = 2e5 + 3;
int p[MAXN], a[MAXN], pre[MAXN];
int f[20][MAXN], pos[MAXN], max_p[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    if (i) {
      pre[p[i]] = p[i - 1];
    }
  }
  pre[p[0]] = p[n - 1];

  for (int i = 1; i <= m; ++i) {
    cin >> a[i];
    f[0][i] = pos[pre[a[i]]];
    pos[a[i]] = i;
  }
  for (int i = 1; i < 20; ++i) {
    for (int j = 1; j <= m; ++j) {
      f[i][j] = f[i - 1][f[i - 1][j]];
    }
  }

  for (int i = 1; i <= m; ++i) {
    int t = i;
    for (int j = 0; j < 20; ++j) {
      if ((n - 1) >> j & 1) {
        t = f[j][t];
      }
    }
    max_p[i] = max(max_p[i - 1], t);
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    if (max_p[r] >= l) {
      cout << "1";
    } else {
      cout << "0";
    }
  }
  cout << "\n";

  return 0;
}
