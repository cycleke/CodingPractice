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

  int b, k, a, res = 0;
  cin >> b >> k;
  for (int i = 0; i < k; i++) {
    cin >> a;
    res = (res * b + a) & 1;
  }
  cout << (res ? "odd" : "even") << endl;
  return 0;
}
