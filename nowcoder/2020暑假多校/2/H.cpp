#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 2e5 + 5;
const int INF = 0x7f7f7f7f;

struct Node {
  int value, min_value, size;
  pii pri, max_pri;
  Node *fa, *ch[2];
};

template <int MAX_SIZE> class Splay {
public:
  Node *nil, *root;

  void init() {
    pool_ptr = node_pool;
    nil = pool_ptr++;
    *nil = {INF, INF, 0, pii(0, 0), pii(0, 0), nil, {nil, nil}};
    Node *left = new_node(pii(-1, 0));
    Node *right = new_node(pii(INF, 0));
    root = left;
    left->ch[1] = right, right->fa = left;
    left->value = INF;
    right->value = right->pri.first - left->pri.first;
    maintain(left);
  }

  void splay(Node *u, Node *target) {
    for (Node *f; u->fa != target; rotate(u)) {
      if ((f = u->fa)->fa != target)
        ((u == f->ch[1]) ^ (f == f->fa->ch[1])) ? rotate(u) : rotate(f);
    }
    if (target == nil) root = u;
  }

  void insert(pii pri) {
    Node *u = root;
    while (u != nil) {
      int d = pri >= u->pri;
      if (u->ch[d] == nil) break;
      u = u->ch[d];
    }
    splay(u, nil);

    Node *v = new_node(pri);
    if (pri < u->pri) {
      Node *pred = u->ch[0];
      while (pred->ch[1] != nil) pred = pred->ch[1];
      splay(pred, u);
      v->fa = pred, pred->ch[1] = v;
      u->value = u->pri.first - pri.first;
      v->value = pri.first - pred->pri.first;
      maintain(v), maintain(pred), maintain(u);
    } else {
      Node *succ = u->ch[1];
      while (succ->ch[0] != nil) succ = succ->ch[0];
      splay(succ, u);
      v->fa = succ, succ->ch[0] = v;
      succ->value = succ->pri.first - pri.first;
      v->value = pri.first - u->pri.first;
      maintain(v), maintain(succ), maintain(u);
    }
    splay(v, nil);
  }

  void erase(Node *u) {
    splay(u, nil);
    Node *pred = u->ch[0];
    while (pred->ch[1] != nil) pred = pred->ch[1];
    splay(pred, u);
    Node *succ = u->ch[1];
    while (succ->ch[0] != nil) succ = succ->ch[0];
    splay(succ, u);
    succ->value = succ->pri.first - pred->pri.first;
    succ->fa = nil, succ->ch[0] = pred, pred->fa = succ;
    maintain(succ);
    root = succ;
  }

  Node *lower_bound(Node *u, const pii &pri) {
    if (u->pri < pri) return lower_bound(u->ch[1], pri);
    if (u->ch[0]->max_pri < pri) return u;
    return lower_bound(u->ch[0], pri);
  }

private:
  Node node_pool[MAX_SIZE], *pool_ptr;

  Node *new_node(const pii &pri) {
    *pool_ptr = {0, 0, 1, pri, pri, nil, {nil, nil}};
    return pool_ptr++;
  }

  void maintain(Node *u) {
    u->size = u->ch[0]->size + u->ch[1]->size + 1;
    u->min_value = min(u->value, min(u->ch[0]->min_value, u->ch[1]->min_value));
    u->max_pri = u->ch[1] != nil ? u->ch[1]->max_pri : u->pri;
  }

  void rotate(Node *u) {
    Node *f = u->fa, *ff = f->fa;
    int d = u == f->ch[1];
    if ((f->ch[d] = u->ch[d ^ 1]) != nil) f->ch[d]->fa = f;
    if ((u->fa = ff) != nil) ff->ch[f == ff->ch[1]] = u;
    f->fa = u, u->ch[d ^ 1] = f;
    maintain(f), maintain(u);
  }
};

Splay<MAXN> splay;
set<pii> pii_set;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;
  splay.init();
  for (int step = 1, op, x; step <= q; ++step) {
    cin >> op >> x;
    switch (op) {
    case 1: {
      pii p(x, step);
      pii_set.insert(p);
      splay.insert(p);
      break;
    }
    case 2: {
      pii p(x, 0);
      pii_set.erase(pii_set.lower_bound(p));
      splay.erase(splay.lower_bound(splay.root, p));
      break;
    }
    case 3: {
      bool flag = false;
      pii p(x, 0);
      auto it = pii_set.lower_bound(p);
      if (it != pii_set.begin()) {
        int a = (--it)->first;
        if (it != pii_set.begin()) {
          int b = (--it)->first;
          flag = a + b > x;
        }
      }
      Node *u = splay.lower_bound(splay.root, p);
      splay.splay(u, splay.nil);
      int m = min(u->value, u->ch[1]->min_value);
      flag |= m < x;
      cout << (flag ? "Yes\n" : "No\n");
      break;
    }
    default: break;
    }
  }

  return 0;
}
