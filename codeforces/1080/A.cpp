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
  int n, k;
  cin >> n >> k;
  cout << ll(ceil(n * 2.0 / k) + ceil(n * 5.0 / k) + ceil(n * 8.0 / k)) << endl;
  return 0;
}
