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

constexpr int MAXN = 2e5;

string s[MAXN], hit;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, cnt = 0;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    if (cnt == 0) {
      cnt = 1;
      hit = s[i];
    } else if (s[i] == hit) {
      ++cnt;
    } else {
      --cnt;
    }
  }

  cnt = 0;
  for (int i = 0; i < n; ++i) cnt += s[i] == hit;
  cout << (cnt > n / 2 ? hit : "NONE") << "\n";

  return 0;
}
