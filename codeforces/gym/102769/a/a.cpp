#include <bits/stdc++.h>
using namespace std;

void solve() {
  int r, b;
  cin >> r >> b;
  int f = r * (r - 1);
  int g = (r + b) * (r + b - 1);
  if (f == 0) {
    cout << "0/1\n";
  } else if (f == g) {
    cout << "1/1\n";
  } else {
    int d = __gcd(f, g);
    f /= d, g /= d;
    cout << f << "/" << g << "\n";
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T;
  cin >> T;
  for (int step = 1; step <= T; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}
