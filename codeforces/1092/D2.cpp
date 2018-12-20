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

  int n;
  cin >> n;
  int a[n], mx = -1;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mx = max(mx, a[i]);
  }

  for (int i = 0; i < n; i++) {
    if (a[i] == mx)
      continue;

    int j = i;
    stack<int> stk;
    while (j < n && a[j] < mx) {
      if (stk.empty() || stk.top() > a[j]) {
        stk.push(a[j]);
      } else if (stk.top() == a[j]) {
        stk.pop();
      } else {
        cout << "NO" << endl;
        return 0;
      }
      j++;
    }

    if (!stk.empty()) {
      cout << "NO" << endl;
      return 0;
    }
    i = j - 1;
  }

  cout << "YES" << endl;
  return 0;
}
