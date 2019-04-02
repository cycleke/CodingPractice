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

  int n, sum = 0;

  cin >> n;
  vi odds, evens;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    sum += x;
    if (x & 1) {
      odds.push_back(x);
    } else {
      evens.push_back(x);
    }
  }

  sort(odds.begin(), odds.end(), greater<int>());
  sort(evens.begin(), evens.end(), greater<int>());
  auto foo = [&](const vi &a, const vi &b) {
    int sum = 0;
    int ia = 0, ib = 0;
    int la = a.size(), lb = b.size();
    while (true) {
      if (ia < la) {
        sum += a[ia];
        ++ia;
      } else {
        break;
      }
      if (ib < lb) {
        sum += b[ib];
        ++ib;
      } else {
        break;
      }
    }
    return sum;
  };
  cout << sum - max(foo(odds, evens), foo(evens, odds)) << "\n";
  return 0;
}
