#include <assert.h>
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

struct Data {
  int prefix;
  int min_dep, max_dep;
  int max_lv, max_vr, max_lvr;
  Data AddDepth(int delta) const {
    return (Data){prefix + delta, min_dep + delta, max_dep + delta,
                  max_lv - delta, max_vr - delta,  max_lvr};
  }
};

struct Node {
  Data data;
  Node *left, *right;
} node_pool[MAXN * 2], *root;

static Data NewLeftData() { return (Data){1, 0, 1, 0, 1, 1}; }

static Data NewRightData() { return (Data){-1, -1, 0, 2, 1, 1}; }

static Data operator+(const Data &lhs, const Data &rhs) {
  Data rhs_added = rhs.AddDepth(lhs.prefix);

  return (Data){
      rhs_added.prefix,
      min(lhs.min_dep, rhs_added.min_dep),
      max(lhs.max_dep, rhs_added.max_dep),
      max({lhs.max_lv, rhs_added.max_lv, lhs.max_dep - 2 * rhs_added.min_dep}),
      max({lhs.max_vr, rhs_added.max_vr, -2 * lhs.min_dep + rhs_added.max_dep}),
      max({lhs.max_lvr, rhs_added.max_lvr, lhs.max_lv + rhs_added.max_dep,
           lhs.max_dep + rhs_added.max_vr})};
}

char bracket[MAXN];

void build(Node *&u, int l, int r) {
  static Node *it = node_pool;
  u = it;
  ++it;
  if (l == r) {
    u->data = (bracket[l] == '(') ? NewLeftData() : NewRightData();
  } else {
    int mid = (l + r) / 2;
    build(u->left, l, mid);
    build(u->right, mid + 1, r);
    u->data = u->left->data + u->right->data;
  }
}

void modify(Node *&u, int l, int r, const int &pos, const char &ch) {
  // assert(u != NULL);
  if (l == r) {
    u->data = (ch == '(') ? NewLeftData() : NewRightData();
    return;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    modify(u->left, l, mid, pos, ch);
  } else {
    modify(u->right, mid + 1, r, pos, ch);
  }
  u->data = u->left->data + u->right->data;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m >> bracket;
  n = 2 * n - 3;
  build(root, 0, n);
  cout << root->data.max_lvr << "\n";

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    modify(root, 0, n, a, bracket[b]);
    modify(root, 0, n, b, bracket[a]);
    swap(bracket[a], bracket[b]);

    cout << root->data.max_lvr << "\n";
  }

  return 0;
}
