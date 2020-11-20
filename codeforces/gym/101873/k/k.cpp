#include <bits/stdc++.h>
using namespace std;

pair<int, string> p[10000];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, d, k;
  cin >> n >> d >> k;
  for (int i = 0; i < n; ++i)
    cin >> p[i].second >> p[i].first;

  sort(p, p + n);
  int x = 0;
  long long saved = 0;
  for (int i = 1; i <= k; ++i) {
    saved += p[n - i].first;
    if (saved >= d) {
      x = i;
      break;
    }
  }
  if (saved < d) {
    cout << "impossible\n";
  } else {
    cout << x << '\n';
    for (int i = 1; i <= x; ++i) {
      cout << p[n - i].second << ", YOU ARE FIRED!\n";
    }
  }
  return 0;
}
