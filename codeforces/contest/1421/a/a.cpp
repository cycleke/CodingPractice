#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int a, b, x = 0;
  cin >> a >> b;
  for (int i = 0; i < 31; ++i) {
    int a_ = a >> i & 1, b_ = b >> i & 1;
    if (a_ == b_) x ^= a_ << i;
  }
  cout << (a ^ x) + (b ^ x) << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
