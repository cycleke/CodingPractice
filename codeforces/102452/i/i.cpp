#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

int k[MAXN], q[MAXN][3];
long long took[MAXN], pre[MAXN][3], goal[MAXN];

priority_queue<pair<long long, int>> heap[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n, m, opt, x, y, last = 0, idx = 0;
  for (cin >> n >> m; m; --m) {
    cin >> opt;
    if (opt == 1) {
      x = ++idx;
      cin >> goal[x] >> k[x];
      goal[x] ^= last;
      for (int i = 0; i < k[x]; ++i) {
        cin >> q[x][i];
        q[x][i] ^= last;
        pre[x][i] = took[q[x][i]];
        heap[q[x][i]].emplace(-took[q[x][i]] - (goal[x] + k[x] - 1) / k[x], x);
      }
    } else {
      cin >> x >> y;
      x ^= last, y ^= last;

      took[x] += y;
      auto &h = heap[x];
      static int ans[MAXN];
      static bitset<MAXN> mark;
      static auto gao = [&](int x) {
        if (mark[x]) return;
        for (int i = 0; i < k[x]; ++i) {
          goal[x] -= took[q[x][i]] - pre[x][i];
          pre[x][i] = took[q[x][i]];
        }
        if (goal[x] <= 0) {
          mark[x] = 1;
          ans[last++] = x;
        } else {
          for (int i = 0; i < k[x]; ++i)
            heap[q[x][i]].emplace(-took[q[x][i]] - (goal[x] + k[x] - 1) / k[x],
                                  x);
        }
      };

      last = 0;
      while (!h.empty()) {
        auto p = h.top();
        if (p.first + took[x] < 0) break;
        h.pop();
        gao(p.second);
      }

      sort(ans, ans + last);
      cout << last;
      for (int i = 0; i < last; ++i) cout << " " << ans[i];
      cout << "\n";
    }
  }

  return 0;
}
