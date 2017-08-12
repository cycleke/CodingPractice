#include <bits/stdc++.h>

using namespace std;

#define DEBUG false

inline void syntax_error() {
  puts("syntax error");
  exit(0);
}

struct event {
  int x, yi, yj, type;
  event(int x, int yi, int yj, int type) :
    x(x), yi(yi), yj(yj), type(type) {}
  inline bool operator < (const event & another) const {
    if (x != another.x) {
      return x < another.x;
    } else {
      return type > another.type;
    }
  }
};

vector < event > e;

#define MAXN 2000007

int n, ans[MAXN];
int x[MAXN], y[MAXN];
pair < pair < int, int >, int > p[MAXN];
inline void make_rect(int xi, int yi, int xj, int yj) {
  e.push_back(event(xi, yi, yj, 1));
  e.push_back(event(xj, yi, yj, -1));
}

inline void make(int i, int j) {
  ans[i] = j - n + 1;
  if (x[i] == x[j] || y[i] == y[j]) {
    make_rect(x[i], y[i], x[j], y[j]);
  } else {
    make_rect(x[i], y[i], x[j] - 1, y[i]);
    make_rect(x[j], y[i], x[j], y[j] - 1);
    make_rect(x[i] + 1, y[j], x[j], y[j]);
    make_rect(x[i], y[i] + 1, x[i], y[j]);
  }
}

int add[MAXN << 2], mx[MAXN << 2];

void push(int u) {
  if (add[u] == 0) {
    return;
  }
  add[u << 1] += add[u];
  add[u << 1 | 1] += add[u];
  add[u] = 0;
}

void pull(int u) {
  mx[u] = max(mx[u << 1] + add[u << 1], mx[u << 1 | 1] + add[u << 1 | 1]);
}

int modify(int u, int l, int r, int x, int y, int delta) {
  if (DEBUG) {
    puts("segment tree:");
    printf("%d %d %d %d %d %d %d\n", u, l, r, x, y, mx[u], add[u]);
  }
  if (x <= l && r <= y) {
    int res = mx[u] + add[u];
    add[u] += delta;
    return res;
    if (DEBUG) {
      puts("segment tree end:");
      printf("%d %d %d %d %d %d %d\n", u, l, r, x, y, mx[u], add[u]);
    }
  }
  push(u);
  int m = (l + r) >> 1;
  int res = 0;
  if (x <= m) {
    res = max(res, modify(u << 1, l, m, x, y, delta));
  }
  if (y > m) {
    res = max(res, modify(u << 1 | 1, m + 1, r, x, y, delta));
  }
  pull(u);
  if (DEBUG) {
    puts("segment tree end:");
    printf("%d %d %d %d %d %d %d\n", u, l, r, x, y, mx[u], add[u]);
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n + n; ++i) {
    scanf("%d %d", x + i, y + i);
    p[i] = make_pair(make_pair(x[i], y[i]), i);
  }
  sort(p, p + n + n);
  static set < pair < int, int > > s;
  for (int id = 0; id < n + n; ++id) {
    int i = p[id].second;
    if (i < n) {
      s.insert(make_pair(y[i], i));
    } else {
      auto it = s.lower_bound(make_pair(y[i] + 1, -1));
      if (it == s.begin()) {
        if (DEBUG) {
          puts("pre-work");
        }
        syntax_error();
      }
      --it;
      make(it->second, i);
      s.erase(it);
    }
  }
  vector < pair < int, int > > ys;
  for (size_t i = 0; i < e.size(); ++i) {
    ys.emplace_back(e[i].yi, i);
    ys.emplace_back(e[i].yj + 1, ~i);
  }
  sort(ys.begin(), ys.end());
  int t = 0;
  for (size_t i = 0; i < ys.size(); ++i) {
    if (i == 0 || ys[i].first != ys[i - 1].first) {
      ++t;
    }
    const int id = ys[i].second;
    if (id >= 0) {
      e[id].yi = t;
    } else {
      e[~id].yj = t - 1;
    }
  }
  sort(e.begin(), e.end());
  if (DEBUG) {
    for (event eve : e) {
      printf("%d %d %d %d\n", eve.x, eve.yi, eve.yj, eve.type);
    }
  }
  for (size_t i = 0; i < e.size(); ++i) {
    int value = modify(1, 1, t, e[i].yi, e[i].yj, e[i].type);
    if (e[i].type == 1 && value > 0) {
      if (DEBUG) {
        printf("%d %d\n", int(i), value);
        printf("%d %d %d %d\n", e[i].x, e[i].yi, e[i].yj, e[i].type);
        puts("oh my segment tree");
      }
      syntax_error();
    }
    //printf("%d %d %d %d\n", e[i].x, e[i].yi, e[i].yj, e[i].type);
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
