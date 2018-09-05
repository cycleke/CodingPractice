#include <cmath>
#include <cstdio>
#include <map>
using namespace std;

map<int, int> count[10];
int a[200000];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
    int x = a[i];
    for (int j = 0; j < 10; j++) {
      x = x * 10ll % k;
      count[j][x]++;
    }
  }

  long long sum = 0;
  long long p10[12] = {1};

  for (int i = 1; i < 12; i++) {
    p10[i] = p10[i - 1] * 10 % k;
  }
  for (int i = 0; i < n; i++) {
    int t = a[i] % k;
    int len = log10(a[i]);
    sum += count[len][(k - t) % k];
    if ((a[i] * p10[len + 1] % k + a[i]) % k == 0) sum--;
  }
  printf("%lld\n", sum);
  return 0;
}
