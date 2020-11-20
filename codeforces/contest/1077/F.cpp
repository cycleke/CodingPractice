#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k, x;
  cin >> n >> k >> x;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<deque<pair<long long, int>>> s(x + 1);
  s[0].push_back(make_pair(0ll, -1));
  long long ans = -1;
  for (int i = 0; i < n; i++) {
    for (int j = x - 1; j >= 0; j--) {
      while (!s[j].empty() && s[j].front().second < i - k)
        s[j].pop_front();
      if (s[j].empty())
        continue;
      long long val = s[j].front().first + a[i];
      while (!s[j + 1].empty() && s[j + 1].back().first <= val)
        s[j + 1].pop_back();
      s[j + 1].push_back(make_pair(val, i));
      if (j + 1 == x && i + k >= n)
        ans = max(ans, val);
    }
  }
  cout << ans << endl;
  return 0;
}
