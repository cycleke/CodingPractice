#include <cstdio>

const int maxn(200010);

inline int min(const int &a, const int &b) {
    return a < b ? a : b;
}

inline int gi() {
    static int a;
    static char c;
    do c = getchar_unlocked(); while (c < 48);
    a = c - 48;
    while (47 < (c = getchar_unlocked()))
        a = (a << 3) + (a << 1) + c - 48;
    return a;
}

struct node {
    int val, s0, s1, dep, mindep;
    node *ch[2], *fa;
    inline void maintain() {
        s0 = ch[0]->s0 ^ ch[1]->s0;
        s1 = ch[0]->s1 ^ ch[1]->s1;
        if (dep & 1)
            s1 ^= val;
        else
            s0 ^= val;
        mindep = min(dep, min(ch[0]->mindep, ch[1]->mindep));
    }
    inline bool which() const {
        return this == fa->ch[1];
    }
} *f[maxn], *nil, *root;

inline node *newnode(int dep = maxn, int val = 0) {
    static node node_mset[maxn], *cnode = node_mset;
    *cnode = (node) {val, 0, 0, dep, dep, {nil, nil}, nil};
    return cnode++;
}

inline void rot(node *u) {
    static int d;
    static node *f;
    f = u->fa;
    d = u->which();
    if ((f->ch[d] = u->ch[d ^ 1]) != nil)
        f->ch[d]->fa = f;
    if ((u->fa = f->fa) != nil)
        f->fa->ch[f->which()] = u;
    u->ch[d ^ 1] = f;
    f->fa = u;
    f->maintain();
}

inline void splay(node *u, node *tag) {
    for (static node *f; (f = u->fa) != tag; rot(u))
        if (f->fa != tag) rot(u->which() == f->which() ? f : u);
    u->maintain();
    if (tag == nil) root = u;
}

inline node *find_node(node *x, int y) {
    while (true) {
        if (x->ch[0]->mindep <= y)
            x = x->ch[0];
        else if (x->dep <= y)
            return x;
        else
            x = x->ch[1];
    }
}

struct edge {
    int to;
    edge *nxt;
} *g[maxn];

inline void add_edge(int u, int v) {
    static edge edge_mset[maxn * 2], *cedge = edge_mset;
    *cedge = (edge) {v, g[u]};
    g[u] = cedge++;
}

int dep[maxn], dq[maxn], dfn, sg[maxn];

void dfs(int u) {
    dq[++dfn] = u;
    for (edge *it = g[u]; it; it = it->nxt)
        if (!dep[it->to]) {
            dep[it->to] = dep[u] + 1;
            dfs(it->to);
        }
}

node *build(int l, int r) {
    if (l > r) return nil;
    int mid = (l + r) >> 1;
    node *u = newnode(dep[dq[mid]], sg[dq[mid]]);
    f[dq[mid]] = u;
    if ((u->ch[0] = build(l, mid - 1)) != nil)
        u->ch[0]->fa = u;
    if ((u->ch[1] = build(mid + 1, r)) != nil)
        u->ch[1]->fa = u;
    u->maintain();
    return u;
}

inline void Print_Tree();

inline bool win(int u) {
    node *l = f[u], *r;
    Print_Tree();
    splay(l, nil);
    Print_Tree();
    r = find_node(l->ch[1], dep[u]);
    splay(r, l);
    Print_Tree();
    if (dep[u] & 1)
        return r->ch[0]->s0;
    else
        return r->ch[0]->s1;
}

inline void modify(int u, int x) {
    splay(f[u], nil);
    root->val = x;
    root->maintain();
}

inline void add_son(int u, int v, int x) {
    dep[v] = dep[u] + 1;
    sg[v] = x;
    node *l = f[u], *r, *n;
    splay(l, nil);
    r = find_node(l->ch[1], dep[u]);
    splay(r, l);
    f[v] = n = newnode(dep[v], sg[v]);
    n->ch[0] = r->ch[0];
    n->ch[0]->fa = n;
    n->fa = r;
    r->ch[0] = n;
    n->maintain();
    r->maintain();
    l->maintain();
}

void Print_Tree(node *u) {
    if (u->ch[0] != nil)
        Print_Tree(u->ch[0]);
    printf("%d ", u->val);
    if (u->ch[1] != nil)
        Print_Tree(u->ch[1]);
}

inline void Print_Tree() {
    //Print_Tree(root);
    //puts("");
}

int main() {
    // freopen("3729.in", "r", stdin);
    // freopen("t.out", "w", stdout);
    int n = gi(), L = gi() + 1;
    for (register int i = 1; i <= n; ++i)
        sg[i] = gi() % L;
    for (register int i = 1, a, b; i < n; ++i)
        add_edge(a = gi(), b = gi()), add_edge(b, a);
    dep[1] = dep[0] = 1;
    dfs(1);
    nil = newnode();
    nil->ch[0] = nil->ch[1] = nil->fa = nil;
    root = build(1, n + 1);
    for (int m = gi(), opt, a, b, c, cnt = 0; m; --m) {
        opt = gi();
        //  cnt = 0;
        if (opt == 1) {
            a = gi() ^ cnt;
            if (win(a))
                puts("MeiZ"), ++cnt;
            else
                puts("GTY");
        } else if (opt == 2) {
            a = gi() ^ cnt, b = gi() ^ cnt;
            modify(a, b % L);
        } else {
            a = gi() ^ cnt, b = gi() ^ cnt, c = gi() ^ cnt;
            add_son(a, b, c % L);
        }
    }
    return 0;
}
