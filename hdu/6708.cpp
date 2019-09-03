#include <bits/stdc++.h>
using namespace std;

bool a[1024][1024];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  a[0][0] = 1;
  for (int l = 1; l < 1024; l <<= 1) {
    for (int i = 0; i < l; ++i) {
      for (int j = 0; j < l; ++j) {
        a[i][j + l] = a[i + l][j + l] = a[i][j];
        a[i + l][j] = !a[i][j];
      }
    }
  }

  int o_o;
  for (cin >> o_o; o_o; --o_o) {
    int k;
    cin >> k;
    k = 1 << k;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < k; ++j) cout << (a[i][j] ? 'C' : 'P');
      cout << '\n';
    }
  }
  return 0;
}
