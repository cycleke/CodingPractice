#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int MAXN = 500;

bitset<MAXN> a[MAXN], id[MAXN], cur, curid;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0, x; j < n; ++j) {
      cin >> x;
      cur[j] = x;
    }
    curid.reset();
    curid[i] = 1;
    for (int j = 0; j < n; ++j) {
      if (!cur[j]) continue;
      if (id[j].count()) {
        cur ^= a[j];
        curid ^= id[j];
      } else {
        ++cnt;
        a[j] = cur;
        id[j] = curid;
        break;
      }
    }
  }

  if (cnt < n) {
    cout << "-1\n";
    return 0;
  }

  vector<int> res;
  res.reserve(n);
  for (int i = 0; i < n; ++i) {
    res.clear();
    cur.reset(), curid.reset();
    cur[i] = 1;
    for (int j = 0; j < n; ++j) {
      if (!cur[j]) continue;
      cur ^= a[j], curid ^= id[j];
    }
    bool first = true;
    for (int j = 0; j < n; ++j) {
      if (!curid[j]) continue;
      if (first) {
        first = false;
      } else {
        cout << " ";
      }
      cout << j + 1;
    }
    cout << "\n";
  }

  return 0;
}
