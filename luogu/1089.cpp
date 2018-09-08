#include <cstdio>

int main() {
  int stored = 0;
  bool have_problem = false;
  int plan, have = 0;
  for (int i = 1; i < 13; i++) {
    scanf("%d", &plan);
    have += 300;
    if (have < plan) {
      printf("-%d\n", i);
      have_problem = true;
      break;
    }
    have -= plan;
    stored += (have / 100) * 120;
    have %= 100;
  }
  if (!have_problem) {
    printf("%d\n", have + stored);
  }
  return 0;
}
