#include <cstdio>

int main() {
  int a[] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292};
  int n;
  scanf("%d", &n);
  if (n < 12) printf("%d", a[n]);
  else printf("%lld", n * 49ll - 247ll);
  return 0;
}
