#include <cstdio>
#include <algorithm>

typedef int array[200003];
array a, s, w, win, lose;

bool cmp(const int &a, const int &b) {
  return (s[a] == s[b]) ? a < b : s[a] > s[b];
}

int main() {
  int n, r, q;
  scanf("%d%d%d", &n, &r, &q);
  n *= 2;
  for (int i = 1; i <= n; i++) a[i] = i;
  for (int i = 1; i <= n; i++) scanf("%d", s + i);
  for (int i = 1; i <= n; i++) scanf("%d", w + i);
  std::sort(a + 1, a + n + 1, cmp);
  for (int step = 0; step < r; step++) {
    win[0] = lose[0] = 0;
    for (int i = 1; i <= n; i += 2) {
      if (w[a[i]] > w[a[i + 1]]) {
        s[a[i]]++;
        win[++win[0]] = a[i];
        lose[++lose[0]] = a[i + 1];
      } else {
        s[a[i + 1]]++;
        win[++win[0]] = a[i + 1];
        lose[++lose[0]] = a[i];
      }
    }
    int i = 1, j = 1;
    a[0] = 0;
    while (i <= win[0] && j <= lose[0]) {
      if (cmp(win[i], lose[j]))
        a[++a[0]] = win[i++];
      else
        a[++a[0]] = lose[j++];
    }
    while (i <= win[0]) a[++a[0]] = win[i++];
    while (j <= lose[0]) a[++a[0]] = lose[j++];
  }
  printf("%d\n", a[q]);
  return 0;
}
