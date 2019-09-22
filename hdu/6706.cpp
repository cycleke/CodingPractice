#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;

const int INV2 = 500000004;
const int INV6 = 166666668;

bool vis[MAXN];
int phi[MAXN], prime[MAXN / 10], prime_cnt, sum[MAXN];

inline void sieve() {
  phi[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    if (!vis[i]) {
      phi[i] = i - 1;
      prime[prime_cnt++] = i;
    }
    for (int j = 0, t; j < prime_cnt; ++j) {
      t = i * prime[j];
      if (t >= MAXN) break;
      vis[t] = true;
      if (i % prime[j]) {
        phi[t] = phi[i] * (prime[j] - 1);
      } else {
        phi[t] = phi[i] * prime[j];
        break;
      }
    }
  }
  sum[0] = 0;
  for (int i = 1; i < MAXN; ++i) 
    sum[i] = (sum[i - 1] + 1LL * i * phi[i]) % MOD;
}

map<int, int> mp_sum;

int gao(int n) {
  if (n < MAXN) return sum[n];
  if (mp_sum.find(n) != mp_sum.end()) return mp_sum[n];
  int res = 1LL * n * (n + 1) % MOD * (2 * n + 1) % MOD * INV6 % MOD;
  for (int i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    res = (res -
           1LL * (i + j) * (j - i + 1) % MOD * INV2 % MOD * gao(n / i) % MOD +
           MOD) %
          MOD;
  }
  return mp_sum[n] = res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  sieve();

  int o_o, n, a, b, ans;
  for (cin >> o_o; o_o; --o_o) {
    cin >> n >> a >> b;
    ans = gao(n) - 1;
    if (ans < 0) ans += MOD;
    cout << 1LL * ans * INV2 % MOD << '\n';
  }

  return 0;
}
