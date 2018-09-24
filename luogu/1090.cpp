#include <cstdio>
#include <algorithm>

int a[10000], b[10000];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  std::sort(a, a + n);
  int sum = 0;
  int it = 0, head = 0, tail = 0;
  for (int step = 1; step < n; step++) {
    auto gainTop = [&]() {
      if (it < n && head < tail) {
        if (a[it] < b[head])
          return a[it++];
        else
          return b[head++];
      } else if (it < n) {
        return a[it++];
      } else if (head < tail) {
        return b[head++];
      } else
        exit(-2);
    };
    int x = gainTop() + gainTop();
    sum += x;
    b[tail++] = x;
  }
  printf("%d\n", sum);
  return 0;
}
