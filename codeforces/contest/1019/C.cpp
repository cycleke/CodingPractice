#include <cstdio>
#include <vector>

#define MAXN 1000000
std::vector<int> g[MAXN];
bool visited[MAXN], chosen[MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x - 1].push_back(y - 1);
  }

  for (int i = 0; i < n; i++) {
    if (visited[i]) continue;
    chosen[i] = true;
    for (int u : g[i]) visited[u] = true;
  }
  for (int i = n - 1; i >= 0; i--) {
    if (!chosen[i]) continue;
    for (int u : g[i]) chosen[u] = false;
  }
  int count = 0;
  for (int i = 0; i < n; i++)
    if (chosen[i]) count++;
  printf("%d\n", count);
  for (int i = 0; i < n; i++)
    if (chosen[i]) printf("%d ", i + 1);
  return 0;
}
