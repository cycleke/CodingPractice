#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, sg[129140163], p[MAXN];

bool check(int *s) {
  for (int i = 2; i < n; ++i)
    if (s[i] == 1 && s[i - 1] == 2 && s[i - 2] == 1) return true;
  return false;
}

void expand(int *s, int status) {
  for (int i = 0; i < n; ++i) {
    s[i] = status % 3;
    status /= 3;
  }
}

int dfs(int status) {
  if (~sg[status]) return sg[status];

  int s[n];
  expand(s, status);
  if (check(s)) return sg[status] = 2;
  vector<int> v;

  for (int i = 0; i < n; ++i) {
    if (s[i]) continue;
    v.push_back(dfs(status + p[i]));
    v.push_back(dfs(status + p[i] * 2));
  }

  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());

  if (v.empty()) return sg[status] = 0;
  if (v.size() == 1) {
    if (v[0] == 0) return sg[status] = 0;
    return sg[status] = 3 - v[0];
  }
  if (v.size() == 2) {
    if (v[0] == 2 || v[1] == 2) return sg[status] = 1;
    return sg[status] = 0;
  }
  return sg[status] = 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  memset(sg, -1, sizeof(sg));
  p[0] = 1;
  for (int i = 1; i < MAXN; ++i) p[i] = 3 * p[i - 1];
  cout << dfs(0) << '\n';

  return 0;
}
