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

  int n;
  cin >> n;
  int c[n], t[n];

  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> t[i];
  }
  if (c[0] != t[0] || c[n - 1] != t[n - 1]) {
    cout << "No" << endl;
    return 0;
  }
  for (int i = n - 1; i > 0; i--) {
    c[i] -= c[i - 1];
    t[i] -= t[i - 1];
  }
  sort(c, c + n);
  sort(t, t + n);
  for (int i = 0; i < n; i++) {
    if (c[i] != t[i]) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
  return 0;
}
