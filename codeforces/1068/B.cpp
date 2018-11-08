#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  long long b;
  cin >> b;
  int count = 0;
  for (long long i = 1; i * i <= b; i++) {
    if (b % i != 0) continue;
    count += (i * i == b) ? 1 : 2;
  }
  cout << count << endl;

  return 0;
}
