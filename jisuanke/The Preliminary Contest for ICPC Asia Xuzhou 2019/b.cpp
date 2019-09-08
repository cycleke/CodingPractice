#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int z[MAXN], x[MAXN], idx[MAXN * 2], f[MAXN * 2];

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q, idc = 0;
  cin >> n >> q;
  for (int i = 0; i < q; ++i) {
    cin >> z[i] >> x[i];
    idx[idc++] = x[i];
    if (x[i] < n) idx[idc++] = x[i] + 1;
  }

  sort(idx, idx + idc);
  idc = unique(idx, idx + idc) - idx;

  for (int i = 0; i < idc; ++i) f[i] = i;
  f[idc] = idc;
  for (int i = 0, id; i < q; ++i) {
    id = lower_bound(idx, idx + idc, x[i]) - idx;
    if (z[i] == 1) {
      if (f[id] == id) f[id] = find(id + 1);
    } else {
      id = find(id);
      if (id < idc)
        cout << idx[id] << '\n';
      else
        cout << "-1\n";
    }
  }

  return 0;
}
