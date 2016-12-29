#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int Nmax = 100005;

int N, Q, M;
int bfr[Nmax], aft[Nmax];

namespace CMT {
    
    struct node {
        node *lc, *rc;
        int w, sum;
        
        void clear() { lc = rc = NULL; w = sum = 0; }
        void maintain()
        {
            sum = w;
            if (lc) sum += lc -> sum;
            if (rc) sum += rc -> sum;
        }
    }t[30 * Nmax], *root[4 * Nmax], *null = new node();
    
	int tot;
    
    inline void init() { tot = -1; for(int i = 0; i <= N; ++i) root[i] = NULL; }
    inline node *NewNode() { t[++ tot].clear(); return &t[tot]; }
    
    void update(node *an, node *&nw, int l, int r, int x)
    {
        nw = NewNode();
        if (l == r) {
            *nw = an ? *an : *null;
            ++ nw -> w; ++ nw -> sum;
            return;
        }
        
        int mid = (l + r) >> 1;
        
        if (x <= aft[mid]) {
            update(an ? an -> lc : null, nw -> lc, l, mid, x);
            nw -> rc = an ? an -> rc : NULL; nw -> maintain();
        } else {
            update(an ? an -> rc : null, nw -> rc, mid + 1, r, x);
            nw -> lc = an ? an -> lc : NULL; nw -> maintain();
        }
    }
    
    int query(node *L, node *R, int l, int r, int k)
    {
        if (l == r) return aft[l];
        
        int mid = (l + r) >> 1, lsize = 0;
        if (R && R -> lc) lsize += R -> lc -> sum;
        if (L && L -> lc) lsize -= L -> lc -> sum;
        
        if (lsize >= k) return query(L ? L -> lc : null, R ? R -> lc : null, l, mid, k);
        return query(L ? L -> rc : null, R ? R -> rc : null, mid + 1, r, k - lsize);
    }
    
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
    while (~scanf("%d%d", &N, &Q)) {
        for (int i = 1; i <= N; ++i) scanf("%d", &bfr[i]);
        memcpy(aft + 1, bfr + 1, sizeof(aft[0]) * N);
        sort(aft + 1, aft + N + 1);
        M = unique(aft + 1, aft + N + 1) - aft - 1;
        
        using namespace CMT; init();
        for (int i = 1; i <= N; ++i) update(root[i - 1], root[i], 1, M, bfr[i]);
        int L, R, rank;
        for (int i = 1; i <= Q; ++i) {
            scanf("%d%d%d", &L, &R, &rank);
            printf("%d\n", query(root[L - 1], root[R], 1, M, rank));
        }
    }
    return 0;
}
