#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  int above = n / 3;
  for (int i = 0; i < above; i++) {
    cout << 2 * i + 1 << " 3" << endl;
  }
  int below = n - above;
  for (int i = 0; i < below; i++) {
    cout << i << " 0" << endl;
  }
  return 0;
}
