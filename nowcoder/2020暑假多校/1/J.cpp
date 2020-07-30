#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  static const int MOD = 998244353;
  static const int MULTI_MAXN = 2e6 + 5;
  static int fac[MULTI_MAXN], inv[MULTI_MAXN], fac_inv[MULTI_MAXN];

  fac[0] = fac[1] = 1;
  inv[1] = 1;
  fac_inv[1] = 1;

  for (int i = 2; i < MULTI_MAXN; ++i) {
    fac[i] = 1LL * i * fac[i - 1] % MOD;
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    fac_inv[i] = 1LL * inv[i] * fac_inv[i - 1] % MOD;
  }

  int n;
  while (cin >> n) {
    cout << 1LL * fac[n] * fac[n] % MOD * fac_inv[2 * n + 1] % MOD << "\n";
  }

  return 0;
}
