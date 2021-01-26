#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 3;
const double EPS = 1e-9;
const int BIAS = 20;
const int LOWER_BITS = (1 << BIAS) - 1;

struct Box {
  int x, y;
  double score;
} boxes[MAXN];

double threshold, a, b;
int ord[MAXN], ans[MAXN], n, S, vis[MAXN], vis_clk;
map<long long, vector<int>> idx;

int sign(double x) {
  if (fabs(x) < EPS) return 0;
  return x < 0 ? -1 : 1;
}

long long encode(int x, int y) { return (1ll * x) << BIAS | y; }
long long split(int x, int y) { return (1ll * x / S) << BIAS | (y / S); }

bool checkIoU(int x1, int y1, int x2, int y2) {
  int ix = max(0, S - abs(x1 - x2));
  int iy = max(0, S - abs(y1 - y2));
  return sign(a * ix * iy - b) <= 0;
}

void gao(const Box &box) {
  int bx = box.x / S, by = box.y / S;
  for (int dx = -1; dx <= 1; ++dx)
    for (int dy = -1; dy <= 1; ++dy) {
      int x = bx + dx, y = by + dy;
      long long code = encode(x, y);
      auto it = idx.find(code);
      if (it == idx.end()) continue;
      for (int i : it->second) {
        if (vis[i] != vis_clk &&
            !checkIoU(box.x, box.y, boxes[i].x, boxes[i].y)) {
          vis[i] = vis_clk;
        }
      }
    }
}

void solve() {
  cin >> n >> S >> threshold;
  a = 1 + threshold, b = 2ll * S * S * threshold;
  for (int i = 0; i < n; ++i) {
    ord[i] = i;
    cin >> boxes[i].x >> boxes[i].y >> boxes[i].score;
  }
  sort(ord, ord + n,
       [&](int a, int b) { return boxes[a].score > boxes[b].score; });

  idx.clear();
  for (int i = 0; i < n; ++i) {
    long long code = split(boxes[i].x, boxes[i].y);
    if (idx.find(code) == idx.end()) idx[code] = vector<int>();
    idx[code].push_back(i);
  }

  ++vis_clk;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x = ord[i];
    if (vis[x] == vis_clk) continue;
    vis[x] = vis_clk;
    ans[cnt++] = x + 1;
    gao(boxes[x]);
  }
  sort(ans, ans + cnt);
  cout << cnt << "\n";
  for (int i = 0; i < cnt; ++i) cout << ans[i] << " \n"[i == cnt - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int step = 1; step <= o_o; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}
