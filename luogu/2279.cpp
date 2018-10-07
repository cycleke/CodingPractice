#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f;

int father[1001];
int depth[1001], min_dis[1001], ranked[1001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  depth[1] = 0;
  ranked[1] = 1;
  father[1] = 0;
  min_dis[0] = min_dis[1] = INF;
  for (int i = 2; i <= n; i++) {
    cin >> father[i];
    ranked[i] = i;
    min_dis[i] = INF;
    depth[i] = depth[father[i]] + 1;
  }
  sort(ranked + 1, ranked + n + 1,
       [depth](const int &a, const int &b) {
         return depth[a] > depth[b];
       });
  int count = 0;
  for (int i = 1; i <= n; i++) {
    int u = ranked[i];
    int f = father[u];
    int gf = father[f];
    min_dis[u] = min({min_dis[u], min_dis[f] + 1, min_dis[gf] + 2});
    if (min_dis[u] > 2) {
      count++;
      min_dis[gf] = 0;
      min_dis[father[gf]] = min(min_dis[father[gf]], 1);
      min_dis[father[father[gf]]] = min(min_dis[father[father[gf]]], 2);
    }
  }
  cout << count << endl;
  return 0;
}
