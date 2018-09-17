#include <cstdio>
#include <algorithm>
using namespace std;

int row[1005], col[1005], rk[1005], *array, id_sort[1005];
bool cmp(const int &a, const int &b) {
  return array[a] > array[b];
}

int main() {
  int m, n, k, l, d;
  scanf("%d%d%d%d%d", &m, &n, &k, &l, &d);
  for (int i = 0; i < d; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a == c) ++col[min(b, d)];
    else ++row[min(a, c)];
  }

  for (int i = 1; i <= m; i++) rk[i] = i;
  array = row;
  sort(rk + 1, rk + m + 1, cmp);
  for (int i = 1; i <= k; i++) {
    id_sort[i] = rk[i];
  }
  sort(id_sort + 1, id_sort + k + 1);
  for (int i = 1; i <= k; i++) {
    printf("%d%c", id_sort[i], " \n"[i == k]);
  }

  for (int i = 1; i <= n; i++) rk[i] = i;
  array = col;
  sort(rk + 1, rk + n + 1, cmp);
  for (int i = 1; i <= l; i++) {
    id_sort[i] = rk[i];
  }
  sort(id_sort + 1, id_sort + l + 1);
  for (int i = 1; i <= l; i++) {
    printf("%d%c", id_sort[i], " \n"[i == l]);
  }
  return 0;
}
