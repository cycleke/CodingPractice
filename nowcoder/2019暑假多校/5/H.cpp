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

#define fi first
#define se second
#define pb push_back
#define mp make_pair

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())
#define ZERO(a) memset((a), 0, sizeof(a))

#define FOR(i, a, b) for (int i = int(a); i < int(b); ++i)
#define REP(i, a, b) for (int i = int(b) - 1; i >= a; --i)
#define FOR2(i, a, b, j, c, d) FOR(i, a, b) FOR(j, c, d)
#define REP2(i, a, b, j, c, d) REP(i, a, b) REP(j, c, d)
#define EACH(i, s) for (auto i = (s).begin(); i != (s).end(); ++i)
#define MUL_CASE                                                               \
  int o_o;                                                                     \
  cin >> o_o;                                                                  \
  for (int case_count = 0; case_count < o_o; ++case_count)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define dbg(x)                                                                 \
  cerr << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
       << __FILE__ << " L" << __LINE__ << "\n"                                 \
       << #x " = " << (x) << endl

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 1e4 + 5;

map<pair<char, int>, int> idx;
vi adj[MAXN];
pair<char, int> ind[MAXN];
int pred[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, idc = 0;
  cin >> n >> m;

  REP(i, 0, m * (m - 1) / 2) {
    string c, s;
    int l;
    cin >> c >> l;
    if (l == 0) {
      continue;
    }
    cin >> s;
    int c0 = 0, c1 = 0, pre = -1, id;
    for (auto &ch : s) {
      if (ch == c[0]) {
        if (!EXIST(idx, mp(ch, c0))) {
          id = idx[mp(ch, c0)] = idc;
          ind[idc++] = mp(ch, c0);
          if (idc > n) {
            cout << "-1\n";
            return 0;
          }
        } else {
          id = idx[mp(ch, c0)];
        }
        ++c0;
      } else {
        if (!EXIST(idx, mp(ch, c1))) {
          id = idx[mp(ch, c1)] = idc;
          ind[idc++] = mp(ch, c1);
          if (idc > n) {
            cout << "-1\n";
            return 0;
          }
        } else {
          id = idx[mp(ch, c1)];
        }
        ++c1;
      }

      if (~pre) {
        adj[pre].pb(id);
        ++pred[id];
      }
      pre = id;
    }
  }

  queue<int> que;

  if (idc != n) {
    cout << "-1\n";
    return 0;
  }

  FOR(i, 0, idc) {
    // debug("%c %d %d\n", ind[i].fi, ind[i].se, pred[i]);
    if (pred[i] == 0) {
      que.push(i);
      break;
    }
  }

  string ans;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    ans += ind[u].first;
    for (int &v : adj[u]) {
      --pred[v];
      if (pred[v] == 0) {
        que.push(v);
      }
    }
  }
  if (ans.length() != n) {
    cout << "-1\n";
  } else {
    cout << ans << "\n";
  }

  return 0;
}
