#include <iostream>
using namespace std;

int c[51], maxx, minx;

bool check(int rest, int sum, int pre, const int &single) {
  if (rest == 0) return true;
  if (sum == single) {
    return check(rest - 1, 0, maxx, single);
  }
  for (int i = pre; i >= minx; i--) {
    if (c[i] && i + sum <= single) {
      c[i]--;
      if (check(rest, sum + i, i, single))
        return true;
      c[i]++;
      if (sum == 0 || sum + i == single)
        return false;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, sum = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x <= 50) {
      c[x]++;
      sum += x;
      if (x > maxx) {
        maxx = x;
      }
      if (x < minx) {
        minx = x;
      }
    }
  }
  for (int i = 1; i <= sum; i++) {
    if (sum % i) continue;
    if (check(sum / i, 0, maxx, i)) {
      cout << i << endl;
      break;
    }
  }
  return 0;
}
