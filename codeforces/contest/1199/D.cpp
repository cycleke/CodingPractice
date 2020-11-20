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

const int MAXN = 2e5 + 3;

struct Node {
  int val, lazy;
  Node *fa, *ch[2];
} node_pool[MAXN], *pool_it, *root, *mp[MAXN], *nil;

void change(Node *u, int val) { u->val = u->lazy = val; }

void push_down(Node *u) {
  if (~u->lazy) {
    if (u->ch[0] != nil) {
      change(u->ch[0], u->lazy);
    }
    if (u->ch[1] != nil) {
      change(u->ch[1], u->lazy);
    }
    u->lazy = -1;
  }
}

void rot(Node *u) {
  Node *f = u->fa, *ff = f->fa;
  int d = u == f->ch[1];
  push_down(f);
  push_down(u);
  if ((f->ch[d] = u->ch[d ^ 1]) != nil)
    f->ch[d]->fa = f;
  if ((u->fa = ff) != nil)
    ff->ch[f == ff->ch[1]] = u;
  u->ch[d ^ 1] = f, f->fa = u;
}

void splay(Node *u, Node *target) {
  for (Node *f; u->fa != target; rot(u))
    if ((f = u->fa)->fa != target)
      ((u == f->ch[1]) ^ (f == f->fa->ch[1])) ? rot(u) : rot(f);
  if (target == nil)
    root = u;
}

void del(Node *u) {
  splay(u, nil);
  push_down(u);
  if (u->ch[0] == nil)
    root = u->ch[1], root->fa = nil;
  else {
    Node *v = u->ch[0];
    for (push_down(v); v->ch[1] != nil; push_down(v = v->ch[1]))
      ;
    splay(v, u);
    if ((v->ch[1] = u->ch[1]) != nil)
      v->ch[1]->fa = v;
    v->fa = nil;
    root = v;
  }
}

void ins(Node *u) {
  if (root == nil) {
    root = u;
    return;
  }

  Node *f = root;
  while (true) {
    int d = f->val < u->val;
    push_down(f);
    if (f->ch[d] == nil) {
      f->ch[d] = u;
      u->fa = f;
      break;
    } else {
      f = f->ch[d];
    }
  }
  splay(u, nil);
}

Node *find_it;
void find(Node *u, const int &val) {
  if (u == nil) {
    return;
  }
  push_down(u);
  if (val >= u->val) {
    find_it = u;
    find(u->ch[1], val);
  } else {
    find(u->ch[0], val);
  }
}

void all_down(Node *u) {
  if (u == nil) {
    return;
  }
  push_down(u);
  all_down(u->ch[0]);
  all_down(u->ch[1]);
}
int main() {

  // freopen("input.txt", "r", stdin);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  pool_it = node_pool;
  nil = pool_it++;
  nil->ch[0] = nil->ch[1] = nil->fa = nil;
  nil->val = nil->lazy = -1;
  root = nil;

  FOR(i, 0, n) {
    mp[i] = pool_it++;
    mp[i]->ch[0] = mp[i]->ch[1] = mp[i]->fa = nil;
    cin >> mp[i]->val;
    mp[i]->lazy = -1;

    ins(mp[i]);
  }

  int q;
  cin >> q;
  FOR(i, 0, q) {
    int op;
    cin >> op;
    if (op == 1) {
      int p, x;
      cin >> p >> x;
      del(mp[p - 1]);
      mp[p - 1]->val = x;
      mp[p - 1]->lazy = -1;
      mp[p - 1]->ch[0] = mp[p - 1]->ch[1] = mp[p - 1]->fa = nil;
      ins(mp[p - 1]);
    } else {
      int x;
      cin >> x;

      find_it = nil;
      find(root, x);
      if (find_it != nil) {
        splay(find_it, nil);
        push_down(root);
        root->val = x;
        if (root->ch[0] != nil) {
          change(root->ch[0], x);
        }
      }
    }
    // all_down(root);
    // FOR(i, 0, n) { cout << mp[i]->val << " "; }
    // cout << "\n";
  }

  all_down(root);
  FOR(i, 0, n) { cout << mp[i]->val << " "; }
  cout << "\n";
  return 0;
}
