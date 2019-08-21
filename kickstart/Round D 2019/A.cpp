#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

set<int> s;
int a[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int o_o;
  cin >> o_o;
  for (int case_count = 0; case_count < o_o;) {
    int n, q;
    cin >> n >> q;
    s.clear();
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      if (__builtin_popcount(a[i]) & 1) s.insert(i);
    }

    cout << "Case #" << ++case_count << ":";
    for (int p, v; q; --q) {
      cin >> p >> v;
      if (__builtin_popcount(v) & 1) {
        s.insert(p);
      } else {
        s.erase(p);
      }
      cout << ' ';
      if (s.size() & 1) {
        cout << max(n - *s.begin() - 1, *s.rbegin());
      } else {
        cout << n;
      }
    }
    cout << '\n';
  }

  return 0;
}
