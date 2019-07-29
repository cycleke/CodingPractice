#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define ll long long
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
const int maxn = 500050;
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
int cnt[maxn];
int ans1, ans2;
int main() {
  n = read();
  scanf("%s", s + 1);
  int n1 = 0, n0 = 0;
  fo(i, 1, n) {
    if (s[i] == '0')
      n0++;
    if (s[i] == '1')
      n1++;
  }
  n0 = min(n0, n1);
  ans1 = n0 * 2;
  n1 = n0 = 0;
  fo(i, 1, n) {
    if (s[i] == '0')
      n0++;
    if (s[i] == '1')
      n1++;
    if (cnt[100050 + n1 - n0] == 0 && n1 != n0)
      cnt[100050 + n1 - n0] = i;
    else
      ans2 = max(ans2, i - cnt[100050 + n1 - n0]);
  }
  cout << ans2 << " " << ans1;
  return 0;
}
