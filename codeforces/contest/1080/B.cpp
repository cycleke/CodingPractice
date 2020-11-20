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

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int l0 = (l & 1) ? l + 1 : l;
    int l1 = (l & 1) ? l : l + 1;
    int r0 = (r & 1) ? r - 1 : r;
    int r1 = (r & 1) ? r : r - 1;
    auto Sum = [](ll s, ll t, ll n) { return (s + t) * n / 2; };
    cout << Sum(l0, r0, (r0 - l0) / 2 + 1) - Sum(l1, r1, (r1 - l1) / 2 + 1)
         << endl;
  }

  return 0;
}
