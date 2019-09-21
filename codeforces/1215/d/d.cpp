#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, sum = 0;
  string s;
  cin >> n >> s;

  for (int i = n / 2 - 1; ~i; --i) {
    if (s[i] == '?') {
      sum += 9;
    } else {
      sum += (s[i] - '0') << 1;
    }
  }
  for (int i = n / 2; i < n; ++i) {
    if (s[i] == '?') {
      sum -= 9;
    } else {
      sum -= (s[i] - '0') << 1;
    }
  }
  cout << (sum ? "Monocarp\n" : "Bicarp\n");
  return 0;
}
