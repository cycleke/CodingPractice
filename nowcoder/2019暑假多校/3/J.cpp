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
  cout << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
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

const int MAXQ = 5e5 + 3;
const int MAXS = MAXQ * 10;

int ch[MAXS][10], idx[MAXS], nc, idc, iter[MAXQ];
int pre[MAXQ], nxt[MAXQ], val[MAXQ], ridx[MAXQ], lst_c, head, tail;

int insert_io() {
  string s;
  cin >> s;

  int u = 1;
  for (auto c : s) {
    if (ch[u][c - '0'] < 0) {
      ch[u][c - '0'] = nc;
      FOR(i, 0, 10) ch[nc][i] = -1;
      idx[nc] = -1;
      ++nc;
    }
    u = ch[u][c - '0'];
  }

  if (idx[u] < 0) {
    idx[u] = idc;
    iter[idc] = -1;
    ++idc;
  }
  return idx[u];
}

void del(int u) {
  if (~pre[u]) {
    nxt[pre[u]] = nxt[u];
  }
  if (~nxt[u]) {
    pre[nxt[u]] = pre[u];
  }
  if (u == head) {
    head = nxt[u];
  }
  if (u == tail) {
    tail = pre[u];
  }
  pre[u] = nxt[u] = -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  MUL_CASE {
    int m, q, lst_size = 0;
    cin >> m >> q;

    idc = 0;

    lst_c = 0;
    head = tail = -1;

    nc = 1;
    idx[0] = -1;
    FOR(i, 0, 10) { ch[0][i] = -1; }

    while (q--) {
      int opt, v, id;
      cin >> opt;
      id = insert_io();
      cin >> v;

      if (opt == 0) {
        if (~iter[id]) {
          cout << val[iter[id]] << "\n";

          del(iter[id]);
          pre[lst_c] = tail;
          if (~tail) {
            nxt[tail] = lst_c;
          }
        }
      }
    }
  }

  return 0;
}
