#include <bits/stdc++.h>
using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MAXN = 2e5 + 3;

int f[MAXN];
map<int, vector<int>> bin;
tuple<int, int, int> ans[MAXN];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for (int i = 1, m, d; i <= n; ++i) {
    f[i] = i;
    cin >> m;
    for (int j = 0; j < m; ++j) {
      cin >> d;
      bin[d].emplace_back(i);
    }
  }

  int cnt = 1;
  for (auto &p : bin) {
    int r = p.first;
    auto &vs = p.second;
    int sz = vs.size();
    if (sz <= 1) continue;
    int u = vs[0];
    for (int i = 1; i < sz; ++i) {
      int v = vs[i];
      if (find(u) == find(v)) continue;
      f[f[v]] = f[u];
      ans[cnt++] = {u, v, r};
      if (cnt == n) break;
    }
    if (cnt == n) break;
  }

  if (cnt < n) {
    cout << "impossible\n";
  } else {
    for (int i = 1, p, q, r; i < n; ++i) {
      tie(p, q, r) = ans[i];
      cout << p << " " << q << " " << r << "\n";
    }
  }

  return 0;
}
