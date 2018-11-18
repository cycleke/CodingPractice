#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<int> a(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int count = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i - 1] == 1 && a[i] == 0 && a[i + 1] == 1) {
      a[i + 1] = 0;
      count++;
    }
  }
  cout << count << endl;
  return 0;
}
