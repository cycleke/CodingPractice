#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  map<int, int> count;
  vector<int> cnt, ans;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    count[x]++;
  }
  for (auto &x : count) {
    cnt.push_back(x.second);
  }
  auto Count = [&](int m) {
    int sum = 0;
    for (int &x : cnt) {
      sum += x / m;
    }
    return sum;
  };
  int l = 1, r = n;
  while (l <= r) {
    int m = (l + r) / 2;
    if (Count(m) >= k) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  for (auto &x : count) {
    int t = x.second / r;
    while (t--) {
      ans.push_back(x.first);
    }
  }
  for (int i = 0; i < k; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}
