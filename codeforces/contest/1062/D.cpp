#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  long long ans = 0;
  for (int i = 2; i <= n / 2; i++) {
    for (int j = 2; i * j <= n; j++) {
      ans += i + j;
    }
  }
  cout << ans * 2 << endl;
  return 0;
}
