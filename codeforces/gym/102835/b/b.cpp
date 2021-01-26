#include <bits/stdc++.h>
#define R register
#define inf 1e9
int a[5], st[10], s[10], p[10];
bool v[10010];

using namespace std;

int main() {
  for (int i = 1; i <= 4; ++i) scanf("%d", &a[i]);
  sort(a + 1, a + 4 + 1);
  do {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k) {
          if (i == 0 && j == 0 && k == 0) continue;
          s[1] = a[1];
          int t = 1, tt = 0, top = 0;
          if (i == 0)
            s[t] = s[t] * 10 + a[2];
          else
            p[++tt] = i, s[++t] = a[2];
          if (j == 0)
            s[t] = s[t] * 10 + a[3];
          else
            p[++tt] = j, s[++t] = a[3];
          if (k == 0)
            s[t] = s[t] * 10 + a[4];
          else
            p[++tt] = k, s[++t] = a[4];
          st[++top] = s[1];
          //  for (int r=1; r<=t; ++r) printf("%d ",s[r]);
          for (int q = 2; q <= t; ++q) {
            if (p[q - 1] == 3)
              st[top] *= s[q];
            else
              st[++top] = (p[q - 1] == 1 ? s[q] : -s[q]);
          }
          int now = 0;
          for (int q = 1; q <= top; ++q) now += st[q];
          if (now < 0) continue;
          v[now] = 1;
        }
  } while (next_permutation(a + 1, a + 5));
  int ans = 0;
  for (int i = 0; i <= 9999; ++i) ans += v[i];
  printf("%d", ans);
}
