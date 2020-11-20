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

  int n, m;
  cin >> n >> m;
  vi a(n);
  int mx = -1;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mx = max(mx, a[i]);
  }
  int cur = 1;
  long long ans = 0;
  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++) {
    if (a[i] < cur) {
      ans += max(a[i] - 1, 0);
    } else {
      ans += a[i] - 1;
      cur++;
      // cout << i << " " << a[i] << cur << endl;
    }
  }
  cur--;
  ans -= mx - cur;
  cout << ans << endl;
  return 0;
}
