#include <cstdio>
#include <algorithm>
using namespace std;

pair<int, int> candidate[5000];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    int id, score;
    scanf("%d%d", &id, &score);
    candidate[i] = make_pair(id, score);
  }
  auto cmp = [&](const pair<int, int> &a, const pair<int, int> &b) {
               if (a.second != b.second) return a.second > b.second;
               else return a.first < b.first;
             };
  sort(candidate, candidate + n, cmp);
  int score_line = candidate[int(m * 1.5) - 1].second;
  int pass_count = 0;
  for (int i = 0; i < n; i++) {
    if (candidate[i].second < score_line) break;
    pass_count++;
  }
  printf("%d %d\n", score_line, pass_count);
  for (int i = 0; i < n; i++) {
    if (candidate[i].second < score_line) break;
    printf("%d %d\n", candidate[i].first, candidate[i].second);
  }
  return 0;
}
