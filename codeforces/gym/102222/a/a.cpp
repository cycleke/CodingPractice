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

constexpr int MAXN = 5e6 + 3;
using u32 = unsigned int;

u32 SA, SB, SC;
int n, p, q, m, top;

u32 rng61() {
  SA ^= SA << 16;
  SA ^= SA >> 5;
  SA ^= SA << 1;
  u32 t = SA;
  SA = SB;
  SB = SC;
  SC ^= t ^ SA;
  return SC;
}

int stk[MAXN];

void push(int x) {
  stk[top + 1] = max(stk[top], x);
  ++top;
}

void pop() {
  if (top) --top;
}

void solve() {
  top = 0;
  cin >> n >> p >> q >> m >> SA >> SB >> SC;
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    (rng61() % (p + q) < p) ? push(rng61() % m + 1) : pop();
    ans ^= 1ll * i * stk[top];
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
