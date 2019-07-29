#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define ll long long
using namespace std;
const int maxn = 100050;
ll read() {
  char ch = getchar();
  ll f = 1, x = 0;
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
ll a[maxn], b[maxn];
struct dat {
  ll v;
  int ps;
  friend bool operator<(dat a, dat b) { return a.v < b.v; }
} nowa, nowb;
dat aa[maxn], bb[maxn];
int posa[maxn], posb[maxn];
set<int> sa, sb;
int main() {
  while (scanf("%d", &n) != EOF) {
    fo(i, 1, n) { a[i] = read(); }
    fo(i, 1, n) { b[i] = read(); }
    sa.clear();
    sb.clear();
    fo(i, 1, n) {
      nowa.ps = nowb.ps = i;
      nowa.v = a[i];
      nowb.v = b[i];
      aa[i] = nowa;
      bb[i] = nowb;
    }
    sort(aa + 1, aa + 1 + n);
    sort(bb + 1, bb + 1 + n);
    posa[aa[1].ps] = posb[bb[1].ps] = 0;
    sa.insert(0);
    sb.insert(0);
    fo(i, 2, n) {
      sa.insert(-aa[i - 1].ps);
      posa[aa[i].ps] = *sa.lower_bound(-aa[i].ps) * (-1);
      sb.insert(-bb[i - 1].ps);
      posb[bb[i].ps] = *sb.lower_bound(-bb[i].ps) * (-1);
    }
    fo(i, 1, n + 1) {
      if (i == n + 1) {
        printf("%d\n", i - 1);
        break;
      }
      if (posa[i] != posb[i]) {
        printf("%d\n", i - 1);
        break;
      }
    }
  }
  return 0;
}