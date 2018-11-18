#include <bits/stdc++.h>
using namespace std;

int mark[1000001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<int> ans, a(n);
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
    mark[a[i]]++;
  }
  for (int i = 0; i < n; i++) {
    if ((sum - a[i]) & 1)
      continue;
    if (sum - a[i] > 2000000)
      continue;
    if (((sum - a[i]) / 2 != a[i] && mark[(sum - a[i]) / 2]) ||
        (((sum - a[i]) / 2 == a[i]) && mark[a[i]] > 1))
      ans.push_back(i + 1);
  }
  cout << ans.size() << endl;
  for (int &x : ans) {
    cout << x << " ";
  }
  return 0;
}
