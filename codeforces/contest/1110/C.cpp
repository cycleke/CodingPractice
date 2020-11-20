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

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int o_o;
  cin >> o_o;
  while (o_o--) {
    long long a;
    cin >> a;
    if (a & (a + 1)) {
      int cnt = 0;
      while (a) {
        cnt++;
        a >>= 1;
      }
      cout << (1ll << cnt) - 1 << endl;
    } else {
      long long x = 2;
      while (a % x) {
        if (x * x > a) {
          x = a;
          break;
        }
        x++;
      }
      cout << a / x << endl;
    }
  }

  return 0;
}
