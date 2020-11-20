#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, pre = 0, cur = 1, ml = 1;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x - pre == 1) {
      ml = max(ml, ++cur);
    } else {
      cur = 1;
    }
    pre = x;
  }
  if (1001 - pre == 1) {
    ml = max(ml, ++cur);
  }
  cout << max(0, ml - 2) << endl;
  return 0;
}
