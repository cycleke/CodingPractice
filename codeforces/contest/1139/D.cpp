#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;
const int MAXM = 1e5 + 3;

int m, mu[MAXM];
bool vis[MAXM];
vi primes;

inline int _pow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = ll(res) * a % MOD;
    }
    a = ll(a) * a % MOD;
    b >>= 1;
  }
  return res;
}

inline void preWork() {
  mu[1] = 1;
  for (int i = 2; i <= m; ++i) {
    if (!vis[i]) {
      mu[i] = -1;
      primes.push_back(i);
    }
    for (int prime : primes) {
      int x = prime * i;
      if (x > m) {
        break;
      }
      vis[x] = true;
      if (i % prime != 0) {
        mu[x] = -mu[i];
      } else {
        mu[x] = 0;
        break;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> m;
  preWork();

  int ans = 1;
  for (int i = 2; i <= m; ++i) {
    ll f = m / i;
    ans = (ans + MOD - (mu[i] * f * _pow(m - f, MOD - 2)) % MOD) % MOD;
  }
  cout << ans << endl;

  return 0;
}
