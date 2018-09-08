#include <cmath>
#include <cstdio>

int main() {
  double s, x;
  scanf("%lf%lf", &s, &x);
  double t_enter, t_exit;
  t_enter = log(1 - 0.02 * (s - x) / 7) / log(0.98);
  t_exit = log(1 - 0.02 * (s + x) / 7) / log(0.98);
  //fprintf(stderr, "%lf %lf\n", t_enter, t_exit);
  if (t_exit - t_enter > 1.0 + 1e-9) puts("y");
  else puts("n");
  return 0;
}
