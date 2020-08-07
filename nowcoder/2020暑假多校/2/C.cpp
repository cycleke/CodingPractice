#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MAXN = 2e5 + 5;

vi adj[MAXN], leaves;

void dfs(int u, int from) {
  if (adj[u].size() == 1) {
    leaves.push_back(u);
    return;
  }
  for (int v : adj[u]) {
    if (v == from) continue;
    dfs(v, u);
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int root = 0;
  for (int i = 1; !root && i <= n; ++i)
    if (adj[i].size() > 1) root = i;

  dfs(root, root);
  int low = leaves.size() / 2, up = (leaves.size() + 1) / 2;
  cout << up << "\n";
  for (int i = 0; i < low; ++i)
    cout << leaves[i] << " " << leaves[i + up] << "\n";
  if (leaves.size() & 1) cout << root << " " << leaves[up - 1] << "\n";
  return 0;
}
