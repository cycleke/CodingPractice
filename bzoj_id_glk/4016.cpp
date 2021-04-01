#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 30010;
typedef pair<int, int>pii;
vector<pii> G[N];
int n, m, mv, cnt, root, Siz, K;
int s[N], froot, f[2][N], g[2][N];
bool vis[N];
int to[N << 1], nxt[N << 1], head[N], W[N << 1], totE;
 
#define Adde(a,b,c) (to[totE] = b, nxt[totE] = head[a], W[totE] = c, head[a] = totE++)
 
//dijkstra
priority_queue<pii, vector<pii>, greater<pii> >heap;
int d[N];
 
void dijkstra() {
    memset(d, 127, sizeof d);
    heap.push(make_pair(d[1] = 0, 1));
    int p, dis, w, v;
    while (!heap.empty()) {
        dis = heap.top().first, p = heap.top().second;
        heap.pop(); if (d[p] ^ dis) continue;
        sort(G[p].begin(), G[p].end());
        for (int i = 0; i < G[p].size(); ++i) 
          if (d[v = G[p][i].first] > dis + (w = G[p][i].second)) heap.push(make_pair(d[v] = dis + w, v));
    }
}
 
void Build(int u) {
    int v; vis[u] = true;
    for (int i = 0; i < G[u].size(); ++i)
      if (!vis[v = G[u][i].first] && d[v] == d[u] + G[u][i].second) {
          Adde(v, u, G[u][i].second); Adde(u, v, G[u][i].second); Build(v);
      }
}
 
void getroot(int u, int fa) {
    s[u] = 1; int mx = 0, v;
    for (int it = head[u]; ~it; it = nxt[it]) 
      if (!vis[v = to[it]] && (v ^ fa)) {
            getroot(v, u); s[u] += s[v];
            if (s[v] > mx) mx = s[v];
      }
    if (Siz - mx > mx) mx = Siz - mx;
    if (froot > mx) root = u, froot = mx; 
}
 
void dfs(int u, int fa, int dep) {
    if (dep > K) return; int v;
    if (d[u] > g[0][dep]) g[0][dep] = d[u], g[1][dep] = 0;
    if (d[u] >= g[0][dep]) ++g[1][dep];
    for (int i = head[u]; ~i; i = nxt[i]) 
      if (!vis[v = to[i]] && (v ^ fa)) {
          d[v] = d[u] + W[i]; dfs(v, u, dep + 1);
      }
}
 
 
void solve(int u, int S) {
    vis[u] = true; f[0][0] = 0; f[1][0] = 1;
    int v;
    for (int i = head[u]; ~i; i = nxt[i]) 
      if (!vis[v = to[i]]) {
            d[v] = W[i]; dfs(v, u, 1);
            for (int j = 1; j <= K; ++j) {
                if (g[0][j] + f[0][K - j] > mv) mv = g[0][j] + f[0][K - j], cnt = 0;
                if (g[0][j] + f[0][K - j] >=  mv) cnt += g[1][j] * f[1][K - j];
            }
            for (int j = 1; j <= K; ++j) {
                if (g[0][j] > f[0][j]) f[0][j] = g[0][j], f[1][j] = 0;
                if (g[0][j] >= f[0][j]) f[1][j] += g[1][j];
                g[0][j] = g[1][j] = 0;
            }
      }
    for (int i = 0; i <= K; ++i) f[0][i] = f[1][i] = 0;
    for (int i = head[u]; ~i; i = nxt[i]) 
      if (!vis[v = to[i]]) {
          froot = Siz = s[v]; root = 0;
          getroot(v, u); 
          solve(root, s[v]);
      }
}
 
int main() {
    scanf("%d%d%d", &n, &m, &K);
    --K;
    int a, b, c;
    while (m--) {
        scanf("%d%d%d", &a, &b, &c);
        G[a].push_back(make_pair(b, c));
        G[b].push_back(make_pair(a, c));
    }
    dijkstra();
    memset(head, -1, sizeof head);
    Build(1);
    memset(vis, 0, sizeof vis);
    froot = Siz = n;
    getroot(1, root = 0);
    solve(root, n);
    printf("%d %d\n", mv, cnt);
    return 0;
}
