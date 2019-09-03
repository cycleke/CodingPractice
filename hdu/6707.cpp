#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

bool mark[MAXN];
int a[MAXN], s[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = m - 1; ~i; --i) cin >> s[i];
  for (int i = 0; i ^ m; ++i)
    if (!mark[s[i]]) cout << a[s[i]] << ' ', mark[s[i]] = true;
  for (int i = 1; i <= n; ++i)
    if (!mark[i]) cout << a[i] << ' ';

  return 0;
}
