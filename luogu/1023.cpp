#include <cmath>
#include <cstdio>
#include <algorithm>

int sold[100005];

int main() {
  int expected_price;
  scanf("%d", &expected_price);
  int basic_price, basic_sold, max_price;
  scanf("%d%d", &basic_price, &basic_sold);
  max_price = basic_price;
  sold[basic_price] = basic_sold;
  while (true) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a == -1 && b == -1) break;
    sold[a] = b;
    if (a > max_price) max_price = a;
  }
  for (int i = basic_price; i < max_price; ) {
    int next_price;
    for (next_price = i + 1; next_price <= max_price; next_price++) {
      if (sold[next_price] == 0) continue;
      break;
    }
    int delta = (sold[next_price] - sold[i]) / (next_price - i);
    for (int j = i + 1; j < next_price; j++) {
      sold[j] = sold[j - 1] + delta;
    }
    i = next_price;
  }
  int delta;
  scanf("%d", &delta);
  if (expected_price >= max_price) {
    for (int i = max_price + 1; i <= expected_price + 1; i++) {
      sold[i] = sold[i - 1] - delta;
    }
    max_price = expected_price + 1;
  }
  //for (int i = basic_price; i <= max_price; i++) {
  //  fprintf(stderr, "%d ", sold[i]);
  //}
  double maxinum(-1e20), mininum(1e20);
  for (int i = basic_price; i <= max_price; i++) {
    double t = ((double)(i-basic_price)*sold[i]-(double)(expected_price-basic_price)*sold[expected_price])/(double)(sold[expected_price]-sold[i]);
    if (expected_price < i) {
      maxinum = std::max(maxinum, t);
    } else {
      mininum = std::min(mininum, t);
    }
  }
  if (maxinum > mininum) puts("NO SOLUTION");
  else if (maxinum > 0) printf("%.0lf\n", ceil(maxinum));
  else if (mininum < 0) printf("%.0lf\n", floor(mininum));
  else puts("0");
  return 0;
}
