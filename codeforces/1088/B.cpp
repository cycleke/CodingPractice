#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, k;
  cin >> n >> k;
  int a[n];

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a, a + n);
  int pre = 0, it = 0;
  for (int i = 0; i < k; i++) {
    if (it >= n) {
      cout << "0" << endl;
    } else {
      cout << a[it] - pre << endl;
      pre = a[it];
      it++;
      while (it < n && a[it] == pre)
        it++;
    }
  }

  return 0;
}