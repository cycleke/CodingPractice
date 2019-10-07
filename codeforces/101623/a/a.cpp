#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int h[MAXN];
vector<int> pos[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> uni(n);
  for (int i = 0; i < n; ++i) cin >> h[i], uni[i] = h[i];

  sort(uni.begin(), uni.end());
  uni.erase(unique(uni.begin(), uni.end()), uni.end());

  vector<int> a;
  for (int i = 0; i < n; ++i) {
    int id = lower_bound(uni.begin(), uni.end(), h[i]) - uni.begin();
    if (!a.empty() && id == a.back()) continue;
    pos[id].push_back(a.size());
    a.push_back(id);
  }

  n = a.size();
  pair<int, int> a1(0, n), a2(0, n);
  for (size_t i = 0; i < uni.size(); ++i) {
    pair<int, int> b1(a1.first, n), b2(a2.first, n);
    for (int &p : pos[i]) {
      if (p < n - 1 && a[p] + 1 == a[p + 1]) {
        auto t = make_pair((p == a1.second + 1 ? a2.first : a1.first) + 1,
                           pos[i + 1].size() == 1 ? n : p);
        if (t > b1)
          b2 = b1, b1 = t;
        else if (t > b2)
          b2 = t;
      }
    }
    a1 = b1, a2 = b2;
  }
  cout << n - 1 - a1.first << '\n';
  return 0;
}
