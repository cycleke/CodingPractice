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

constexpr int MAXS = 203;
constexpr int MAXN = 1e5 + 3;

string str[MAXN];
bitset<MAXS> g[MAXS];
int it[MAXS], a[MAXN];
unordered_map<string, int> idx;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int s, l, n;
  cin >> s >> l >> n;

  for (int i = 0; i < s; ++i) cin >> str[i];
  sort(str, str + s);
  for (int i = 0; i < s; ++i) idx[str[i]] = i;

  string u, v;
  for (int i = 0; i < l; ++i) {
    cin >> u >> v;
    int iu = idx[u], iv = idx[v];
    g[iu][iv] = g[iv][iu] = 1;
  }

  for (int i = 0; i < n; ++i) {
    cin >> u;
    a[i] = idx[u];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < s; ++j) {
      while (it[j] < n && (a[it[j]] == -1 || g[j][a[it[j]]])) ++it[j];
      if (it[j] < n && a[it[j]] == j) {
        a[it[j]] = -1;
        cout << str[j] << " ";
        break;
      }
    }
  }
  cout << "\n";

  return 0;
}
