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

  int n, m, k;
  cin >> n >> m >> k;
  int res = n, pre, cur, a[n - 1];
  cin >> pre;
  for (int i = 0; i < n - 1; i++) {
    cin >> cur;
    a[i] = cur - pre - 1;
    pre = cur;
  }
  sort(a, a + n - 1);
  for (int i = 0; i < n - k; i++) {
    res += a[i];
  }
  cout << res << endl;
  return 0;
}
