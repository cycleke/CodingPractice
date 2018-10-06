#include <bits/stdc++.h>
using namespace std;

int f[32001];
int cost[61], value[61];
int son[61][2];
bool is_son[61];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int v, p, q;
    cin >> v >> p >> q;
    cost[i] = v;
    value[i] = v * p;
    if (q != 0) {
      is_son[i] = true;
      if (son[q][0] == 0)
        son[q][0] = i;
      else
        son[q][1] = i;
    }
  }

  for (int i = 1; i <= m; i++) {
    if (is_son[i]) continue;
    for (int j = n; j >= cost[i]; j--) {
      f[j] = max(f[j], f[j - cost[i]] + value[i]);
      int s0 = son[i][0];
      int s1 = son[i][1];
      if (s0 != 0) {
        if (j >= cost[i] + cost[s0])
          f[j] = max(f[j], f[j - cost[i] - cost[s0]] + value[i] + value[s0]);
        if (s1 != 0) {
          if (j >= cost[i] + cost[s1]) {
            f[j] = max(f[j], f[j - cost[i] - cost[s1]] + value[i] + value[s1]);
            if (j >= cost[i] + cost[s0] + cost[s1])
              f[j] = max(f[j],
                         f[j - cost[i] - cost[s0] - cost[s1]] + value[i] + value[s0] + value[s1]);
          }
        }
      }
    }
  }
  cout << f[n] << endl;
  return 0;
}
