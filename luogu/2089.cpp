#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int> > ans;
int cur_comb[10];

void Dfs(int step, int rest) {
  if (rest < 0) return;
  if (step == 10) {
    if (rest) return;
    vector<int> a(10);
    for (int i = 0; i < 10; i++) a[i] = cur_comb[i];
    ans.push_back(a);
  } else if (rest >= 10 - step) {
    for (int i = 1; i <= 3; i++) {
      cur_comb[step] = i;
      Dfs(step + 1, rest - i);
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  ans.clear();
  Dfs(0, n);
  printf("%d\n", (int)ans.size());
  for (auto l : ans) {
    for (auto x : l) printf("%d ", x);
    puts("");
  }
  return 0;
}
