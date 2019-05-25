#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#define ll long long
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
using namespace std;
const int maxn = 2e5 + 10;
const double eps = 1e-9;
ll read() {
  ll x = 0, f = 1;
  char ch = getchar();
  while (!(ch >= '0' && ch <= '9')) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  };
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  };
  return x * f;
}
int n;
char s[maxn];
ll dp[10];
int main() {
  while (scanf("%d%s", &n, s + 1) != EOF) {
    memset(dp, 0, sizeof(dp));
    dp[0] = maxn;
    fo(i, 1, n) {
      int tmp;
      switch (s[i]) {
      case 'x':
        tmp = 1;
        break;
      case 't':
        tmp = 2;
        break;
      case 'C':
        tmp = 3;
        break;
      case 'p':
        tmp = 4;
        break;
      case 'c':
        tmp = 5;
        break;
      default:
        tmp = -1;
        break;
      }
      if (~tmp)
        dp[tmp] = min(dp[tmp - 1], dp[tmp] + 1);
    }
    cout << dp[5] << "\n";
  }
  return 0;
}
