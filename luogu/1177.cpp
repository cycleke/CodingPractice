#include <cstdio>
#include <cstdlib>

int a[100000];

void swap(int *a, int *b) {
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void sort(int *begin, int *end) {
  if (begin + 1 >= end) return;
  int *i = begin, *j = end - 1;
  int random_id = rand() % (end - begin);
  int random_num = begin[random_id];
  swap(i, begin + random_id);
  while (i < j) {
    while (i < j && *j > random_num) j--;
    if (i < j) *i++ = *j;
    while (i < j && *i < random_num) i++;
    if (i < j) *j-- = *i;
  }
  *i = random_num;
  sort(begin, i);
  sort(i + 1, end);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  return 0;
}
