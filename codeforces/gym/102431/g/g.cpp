#include <bits/stdc++.h>
using namespace std;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 3;

vector<int> adj[MAXN];
int pool[MAXN * 4], *f[MAXN], *tag[MAXN], *ptr;
int len[MAXN], son[MAXN], dp[MAXN][2], exdp[MAXN][2], h[MAXN];

void dfs(int u, int from) {
  int mx_len = son[u] = 0;
  for (int v : adj[u]) {
    if (v == from) continue;
    dfs(v, u);
    if (len[v] > mx_len) son[u] = v, mx_len = len[v];
  }
  len[u] = mx_len + 1;
}

void add(int &a, int b) { a += b, (a >= MOD) && (a -= MOD); }
void mul(int &a, int b) { a = 1ll * a * b % MOD; }

void push(int u, int i) {
  if (tag[u][i] == 1) return;
  mul(f[u][i], tag[u][i]);
  mul(tag[u][i + 1], tag[u][i]);
  tag[u][i] = 1;
}

void gao(int u, int from) {
  f[u][0] = tag[u][0] = 1;
  if (!son[u]) return;
  f[son[u]] = f[u] + 1;
  tag[son[u]] = tag[u] + 1;
  gao(son[u], u);
  for (int v : adj[u]) {
    if (v == from || v == son[u]) continue;
    f[v] = ptr, ptr += len[v] + 1;
    tag[v] = ptr, ptr += len[v] + 1;
    gao(v, u);
    h[0] = f[u][0];
    for (int i = 0; i < len[v]; ++i) {
      push(v, i), push(u, i);
      if (i > 0) {
        h[i] = h[i - 1];
        add(h[i], f[u][i]);
        add(f[v][i], f[v][i - 1]);
      }
    }
    for (int i = 0; i < len[v]; ++i) {
      push(u, i + 1);
      if (i > 0) {
        f[u][i + 1] = (1ll * f[u][i + 1] * (f[v][i] + 1) % MOD +
                       1ll * h[i] * (f[v][i] - f[v][i - 1]) % MOD + MOD) %
                      MOD;
      } else {
        f[u][i + 1] = (1ll * f[u][i + 1] * (f[v][i] + 1) % MOD +
                       1ll * h[i] * f[v][i] % MOD) %
                      MOD;
      }
    }
    mul(tag[u][len[v] + 1], f[v][len[v] - 1] + 1);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) adj[i].clear();
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  if (adj[1].size() < 2) {
    cout << "1\n";
    return;
  }

  dfs(1, 1);

  for (int i = 0; i <= len[1] + 1; ++i) {
    dp[i][0] = dp[i][1] = 0;
    exdp[i][0] = exdp[i][1] = 1;
  }
  dp[0][1] = 1;

  static auto update = [&](int i) {
    if (exdp[i][0] != 1) {
      mul(dp[i][0], exdp[i][0]);
      mul(exdp[i + 1][0], exdp[i][0]);
      exdp[i][0] = 1;
    }
    if (exdp[i][1] != 1) {
      mul(dp[i][1], exdp[i][1]);
      mul(exdp[i + 1][1], exdp[i][1]);
      exdp[i][1] = 1;
    }
  };

  for (int v : adj[1]) {
    ptr = pool + 1;
    f[v] = ptr, ptr += len[v] + 1;
    tag[v] = ptr, ptr += len[v] + 1;
    gao(v, 1);
    for (int i = 0; i < len[v]; ++i) {
      push(v, i);
      if (i > 0) add(f[v][i], f[v][i - 1]);
    }

    h[0] = dp[0][0] + dp[0][1];
    for (int i = 1; i <= len[v]; ++i) {
      update(i);
      h[i] = h[i - 1];
      add(h[i], dp[i][0]);
      add(h[i], dp[i][1]);
    }

    for (int i = 0; i < len[v]; ++i) {
      if (i > 0) {
        dp[i + 1][1] =
            (dp[i + 1][1] + 1ll * dp[i + 1][1] * f[v][i] % MOD +
             1ll * dp[i + 1][0] * (f[v][i] - f[v][i - 1]) % MOD + MOD) %
            MOD;
        dp[i + 1][0] = (1ll * dp[i + 1][0] * (f[v][i - 1] + 1) % MOD +
                        1ll * h[i] * (f[v][i] - f[v][i - 1]) % MOD + MOD) %
                       MOD;
      } else {
        dp[i + 1][1] =
            (dp[i + 1][1] + 1ll * (dp[i + 1][1] + dp[i + 1][0]) * f[v][i]) %
            MOD;
        dp[i + 1][0] = (dp[i + 1][0] + 1ll * h[i] * f[v][i]) % MOD;
      }
    }
    mul(exdp[len[v] + 1][0], f[v][len[v] - 1] + 1);
    mul(exdp[len[v] + 1][1], f[v][len[v] - 1] + 1);
  }

  int ans = 1;
  for (int i = 1; i <= len[1]; ++i) update(i), add(ans, dp[i][1]);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, omo = 0;
  for (cin >> o_o; omo < o_o; solve()) cout << "Case #" << ++omo << ": ";
  return 0;
}
