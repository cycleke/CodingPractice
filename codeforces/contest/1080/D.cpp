#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

// const int INF = 0x3fffffff;
// const int MOD = 1e9 + 7;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int _;
  cin >> _;
  while (_--) {
    ll n, k, s = 0;
    cin >> n >> k;
    if (n < 60) {
      for (int i = 0; i < n && s < 3 * k; i++)
        s += 1ll << (2 * i);
      if (k > s || (n < 3 && k == 3)) {
        cout << "NO" << endl;
      } else {
        cout << "YES " << n - (int)ceil(log(k + 0.5) / log(4)) << endl;
      }
    } else {
      cout << "YES " << n - 1 << endl;
    }
  }
  return 0;
}
