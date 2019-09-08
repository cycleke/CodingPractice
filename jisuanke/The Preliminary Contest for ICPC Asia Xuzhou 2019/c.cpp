#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int w;
  cin >> w;
  cout << ((w != 2 && w % 2 == 0) ? "YES\n" : "NO\n");
  return 0;
}
