#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  auto Query = [](const int &c, const int &d) {
    cout << "? " << c << " " << d << endl;
    cout.flush();
    int x;
    cin >> x;
    return x;
  };
  int a(0), b(0);
  int z = Query(a, b);
  for (int step = 29; step >= 0; step--) {
    int x = Query(a | (1 << step), b);
    int y = Query(a, b | (1 << step));
    if (x == y) {
      if (z == 1)
        a |= 1 << step;
      else
        b |= 1 << step;
      z = x;
    } else if (y == 1) {
      a |= 1 << step;
      b |= 1 << step;
    }
  }
  cout << "! " << a << " " << b << endl;
  return 0;
}
