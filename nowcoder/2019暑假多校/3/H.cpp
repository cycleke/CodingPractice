#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define ll long long
#define ld long double
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
const int maxn = 1050;
const ll inf = 1e9;
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
int n, m;
ll xa[maxn], ya[maxn];
struct pt {
  ll x;
  ll y;
  friend bool operator<(pt a, pt b) {
    if (a.x == b.x)
      return a.y < b.y;
    else
      return a.x < b.x;
  }
} pts[maxn];
int main() {
  int T;
  cin >> T;
  while (T--) {
    n = read();
    fo(i, 1, n) {
      xa[i] = read();
      ya[i] = read();
      pts[i].x = xa[i];
      pts[i].y = ya[i];
    }
    sort(pts + 1, pts + 1 + n);
    ll mid = n / 2;
    if (pts[mid].x != pts[mid + 1].x) {
      cout << pts[mid].x << " " << -inf << " " << pts[mid].x + 1 << " " << inf
           << endl;
      continue;
    }
    if (pts[mid + 1].y - pts[mid].y > 1) {
      cout << pts[mid].x - 1 << " " << inf << " " << pts[mid].x << " "
           << pts[mid].y + 1 << endl;
      continue;
    }
    ll dy = 200000ll - pts[mid + 1].y;
    dy = dy + dy + 1;

    cout << pts[mid].x - 1 << " " << 200000 << " " << pts[mid].x + 1 << " "
         << 200000 - dy << endl;
  }
  return 0;
}
