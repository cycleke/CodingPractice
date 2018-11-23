#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, s;
  cin >> n >> s;
  cout << (s / n) + (s % n == 0 ? 0 : 1) << endl;

  return 0;
}
