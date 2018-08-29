#include <cstdio>
#include <cstring>

int ModAdd(int a, int b, int p) {
  return (a + b) % p;
}

int ModMul(int a, int b, int p) {
  return a * b % p;
}

void PrintArray(int p, int f(int, int, int)) {
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      if (j) putchar(' ');
      printf("%d", f(i, j, p));
    }
    puts("");
  }
}

int main() {
  int o_o, p;
  scanf("%d", &o_o);
  while (o_o--) {
    scanf("%d", &p);
    PrintArray(p, ModAdd);
    PrintArray(p, ModMul);
  }
  return 0;
}
