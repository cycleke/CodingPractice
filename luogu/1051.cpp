#include <cstdio>
#include <cstring>

int main() {
  //freopen("1051.in", "r", stdin);
  int n;
  scanf("%d", &n);
  char who_win_most[21] = {0};
  int sum_scholar = 0;
  int max_scholar = -1;
  for (int i = 0; i < n; i++) {
    char name[21];
    int final_score, class_score;
    char is_leader[2], is_east[2];
    int paper;
    scanf("%s%d%d%s%s%d", name, &final_score, &class_score, is_leader, is_east, &paper);
    int scholar = 0;
    if (final_score > 80 && paper > 0) scholar += 8000;
    if (final_score > 85 && class_score > 80) scholar += 4000;
    if (final_score > 90 ) scholar += 2000;
    if (final_score > 85 && *is_east == 'Y') scholar += 1000;
    if (class_score > 80 && *is_leader == 'Y') scholar += 850;
    if (scholar > max_scholar) {
      max_scholar = scholar;
      strcpy(who_win_most, name);
    }
    sum_scholar += scholar;
  }
  printf("%s\n%d\n%d", who_win_most, max_scholar, sum_scholar);
  return 0;
}
