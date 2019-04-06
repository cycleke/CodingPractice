#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;
typedef vector<pii> vpii;

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1e5 + 3;

vi adj[MAXN], res;
int c[MAXN];

void dfs(int u) {
  bool flag = c[u] == 1;
  for (int v : adj[u]) {
    flag &= c[v] == 1;
    dfs(v);
  }
  if (flag) {
    res.push_back(u);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, root = -1;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int p;
    cin >> p >> c[i];
    if (~p) {
      adj[p - 1].push_back(i);
    } else {
      root = i;
    }
  }
  dfs(root);
  sort(ALL(res));
  if (res.empty()) {
    cout << "-1\n";
  } else {
    for (int u : res) {
      cout << u + 1 << " ";
    }
    cout << "\n";
  }
  return 0;
}
