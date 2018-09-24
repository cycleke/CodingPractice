#include <cstdio>
#include <algorithm>
using namespace std;

pair<int, int> farmer[5000];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &farmer[i].first, &farmer[i].second);
  }
  sort(farmer, farmer + m);
  int cost = 0;
  for (int i = 0; i < m; i++) {
    //printf("%d %d %d\n", farmer[i].first, farmer[i].second, n);
    if (farmer[i].second >= n) {
      cost += n * farmer[i].first;
      break;
    } else {
      cost += farmer[i].first * farmer[i].second;
      n -= farmer[i].second;
    }
  }
  printf("%d\n", cost);
  return 0;
}
