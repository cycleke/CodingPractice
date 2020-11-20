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
  int a[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  unordered_map<int, int> count;
  int common = a[0], index = 0;
  for (int i = 0; i < n; ++i) {
    ++count[a[i]];
    if (count[a[i]] > count[common]) {
      index = i;
      common = a[i];
    }
  }
  cout << n - count[common] << "\n";

  for (int i = index - 1; ~i; --i) {
    if (a[i] == common) {
      continue;
    }
    cout << (a[i] < common ? 1 : 2) << " " << i + 1 << " " << i + 2 << "\n";
  }
  for (int i = index + 1; i < n; ++i) {
    if (a[i] == common) {
      continue;
    }
    cout << (a[i] < common ? 1 : 2) << " " << i + 1 << " " << i << "\n";
  }
  return 0;
}
