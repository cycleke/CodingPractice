#include <cstdio>
const int sc[5][5]={
  {0, 0, 1, 1, 0},
  {1, 0, 0, 1, 0},
  {0, 1, 0, 0, 1},
  {0, 0, 1, 0, 1},
  {1, 1, 0, 0, 0}
};
int a[200], b[200];
int main() {
  int n, na, nb, ca=0, cb=0, sa=0, sb=0;
  scanf("%d%d%d", &n, &na, &nb);
  for (int i = 0; i < na; ++i) {
    scanf("%d",a + i);
  }
  for (int i = 0; i < nb; ++i) {
    scanf("%d",b + i);
  }
  for (int i = 0; i < n; ++i) {
    sa += sc[a[ca]][b[cb]];
    sb += sc[b[cb]][a[ca]];
    if(++ca >= na)ca=0;
    if(++cb >= nb)cb=0;
  }
  printf("%d %d\n", sa, sb);
  return 0;
}
