#include <bits/stdc++.h>
using namespace std;
int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int l = sqrt(n * 1.0 + 1.0), r = sqrt(n * 2.0 + 1.0);
    bool f = 0;
    for (int i = l; i <= r; ++i) {
      if (n % i == 0) {
        f = 1;
        break;
      }
    }
    printf("%d\n", f);
  }
  return 0;
}
