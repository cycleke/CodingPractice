#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int o_o;
  unsigned int a, b;
  for (cin >> o_o; o_o; --o_o) {
    cin >> a >> b;
    cout << max(1U, a & b) << '\n';
  }

  return 0;
}
