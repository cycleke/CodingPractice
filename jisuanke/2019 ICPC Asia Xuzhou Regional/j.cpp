#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 3;

bitset<MAXN> used[MAXN];
int n, ans[MAXN][MAXN], mx[MAXN];

void gao1() {
  fill(mx + 1, mx + n + 1, 1);
  for (int i = 1; i <= n; ++i) used[i].set(i);
  for (int len = n - 1; len; --len) {
    ans[len][0] = n;
    int sz = 1, pre = n;
    while (sz <= len) {
      int &cur = mx[pre];
      while (used[pre][cur]) ++cur;
      ans[len][sz++] = cur;
      used[cur][pre] = used[pre][cur] = 1;
      pre = cur;
    }
  }
}

int cur_len;

void push(int x) {
  ans[cur_len][mx[cur_len]++] = x;
  if (cur_len + 1 == mx[cur_len]) {
    --cur_len;
    if (~cur_len & 1) ans[cur_len][mx[cur_len]++] = x;
  }
}

void gao2() {
  cur_len = n - 1;
  for (int i = 2; i <= n; i += 2) {
    push(i);
    for (int x = 1, y = i + 1;; ++x, ++y) {
      push(x);
      if (y > n) break;
      push(y);
    }
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n;

  (n & 1) ? (gao1(), 0) : (gao2(), 0);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= i; ++j) cout << ans[i][j] << " \n"[j == i];
  }

  return 0;
}
