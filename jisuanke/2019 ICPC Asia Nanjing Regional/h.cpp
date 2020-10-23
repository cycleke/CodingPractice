#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int a, b, c;
  cin >> a >> b >> c;
  if (a + b + c == 1) {
    cout << (a ? "YES\n0\n" : "NO\n");
  } else if (b + c >= a) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    cout << (b + c) * 2 + 1 << "\n";
  }

  return 0;
}
