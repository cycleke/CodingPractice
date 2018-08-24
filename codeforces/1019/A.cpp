#include <vector>
#include <cstdio>
#include <algorithm>

#define MAXN 3000

int n, m;
std::vector<std::pair<int, int> > voter;

inline long long Calc(int needed) {
  static int count[MAXN];
  static int vis_colock, vis[MAXN];

  long long cost = 0ll;
  for (int i = 0; i < m; i++) count[i] = 0;
  for (auto x : voter) count[x.second]++;
  vis_colock++;
  for (int i = 0; i < n; i++) {
    std::pair<int, int> &x = voter[i];
    if (x.second && count[x.second] >= needed) {
      count[x.second]--;
      count[0]++;
      vis[i] = vis_colock;
      cost += x.first;
    }
  }
  for (int i = 0; i < n; i++) {
    std::pair<int, int> &x = voter[i];
    if (count[0] < needed && vis[i] != vis_colock && x.second) {
      cost += x.first;
      count[0]++;
    }
  }
  return cost;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    int p, c;
    scanf("%d%d", &p, &c);
    voter.emplace_back(c, p - 1);
  }
  std::sort(voter.begin(), voter.end());
  long long cost = 1ll << 60;
  for (int i = 1; i <= n; i++)
    cost = std::min(cost, Calc(i));
  printf("%lld\n", cost);
  return 0;
}
