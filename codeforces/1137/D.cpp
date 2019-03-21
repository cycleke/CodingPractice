#include <cstdio>

int k;
inline void foo() {
  fflush(stdout);
  scanf("%d", &k);
  for (int i = 0; i < k; i++) {
    scanf("%*s");
  }
}

int main() {
  do {
    puts("next 0 1");
    foo();
    puts("next 0");
    foo();
  } while (k == 3);

  do {
    puts("next 0 1 2 3 4 5 6 7 8 9");
    foo();
  } while (k == 2);

  puts("done");
  return 0;
}
