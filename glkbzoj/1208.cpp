#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MS = 81000, Mod = 1000000;

void Add(int &a, const int &b) {
    a = a + b;
    a %= Mod;
}

inline int getint(int &a) {
    a = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        a = (a << 3) + (a << 1) + c - '0';
        c = getchar();
    }
    return a;
}
struct node {
    int v;
    node *fa, *ch[2];
}NN[MS], *root = NULL;
int totN = -1;

node *NewNode(const int &val, node* f) {
    node *ne = NN + (++totN);
    ne->v = val; ne->fa = f;
    memset(ne->ch, 0, sizeof ne->ch);
    return ne;
}

void Rot(node *u) {
    if (u->fa == NULL) return;
    node *f = u->fa, *ff = u->fa->fa;
    int d = u == f->ch[1];
    node *o = u->ch[d ^ 1];
    f->ch[d] = o; f->fa = u;
    u->ch[d ^ 1] = f; u->fa = ff;
    if (o) o->fa = f;
    if (ff) ff->ch[ff->ch[1] == f] = u;
}

void splay(node *u, node *tag) {
    while (u->fa != tag) {
        if (u->fa->fa == tag) {
            Rot(u); break;
        }
        int d = u == u->fa->ch[1];
        int dd = u->fa == u->fa->fa->ch[1];
        if (d ^ dd) Rot(u->fa);
        else Rot(u);
        Rot(u);
    }
    if (tag == NULL) root = u;
}

void ins(node* &u, const int &val, node* f) {
    if (u == NULL) {
        u = NewNode(val, f);
    } else {
        if (val < u->v) ins(u->ch[0], val, u);
        else ins(u->ch[1], val, u);
    }
}

void Insert(const int &val) {
    ins(root, val, NULL);
    splay(NN + totN, NULL);
}
node* pred(node *u, const int &val) {
    if (u == NULL) return NULL;
    if (val < u->v) return pred(u->ch[0], val);
    node *ans = pred(u->ch[1], val);
    if (!ans) ans = u;
    return ans;
}

node *succ(node *u, const int &val) {
    if (u == NULL) return NULL;
    if (val > u->v) return succ(u->ch[1], val);
    node *ans = succ(u->ch[0], val);
    if (!ans) ans = u;
    return ans;
}

void del(node *u) {
    splay(u, NULL);
    if (root->ch[0] == NULL) {
        root = root->ch[1];
        if (root) root->fa = NULL;
    } else {
        node *cur = root->ch[0];
        while (cur->ch[1]) cur = cur->ch[1];
        splay(cur, root);
        cur->ch[1] = root->ch[1];
        cur->fa = NULL;
        if (root->ch[1]) root->ch[1]->fa = cur;
        root = cur;
    }
}

int query(const int &val) {
    node *a = pred(root, val), *b = succ(root, val);
    if (a && b) {
        if (val - a->v <= b->v - val) { del(a); return val - a->v; }
        else { del(b); return b->v - val; }
    } else if (a) { del(a); return val - a->v; }
    else { del(b); return b->v - val; }
}

int main() {
    int T, flag = 0, a, b, ans = 0;
    getint(T);
    while (T--) {
        getint(a); getint(b);
        if (!a) a = -1;
        if (a * flag >= 0) Insert(b);
        else Add(ans, query(b));
        flag += a;
    }
    printf("%d", ans);
    return 0;
}
