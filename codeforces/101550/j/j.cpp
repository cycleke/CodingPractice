#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  

  int a, b;
  cin >> a >> b;
  if (a == b) {
    cout << "0\n";
    return 0;
  }
  int ans1, ans2;
  if (a < b) {
    ans1 = b - a;
    ans2 = a + 360 - b;
  } else {
    ans1 = b + 360 - a;
    ans2 = a - b;
  }
  cout << (ans1 <= ans2 ? ans1 : -ans2) << '\n';
  return 0;
}
