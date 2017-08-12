#include <bits/stdc++.h>

using namespace std;

#define S 230
#define N 50003
#define Q 200003

struct Query {
    int indedx, m, k;

    inline bool operator < (const Query &other) const {
        return m < other.m;
    }

} QueryList[Q];

struct YoungTable {

    vector < int > a[S + 1];

    pair < int, int > insert(int x) {
        int xx = 0, yy = 0;
        for (int i = 1; i <= S; ++i)
            if (a[i].empty() || a[i].back() < x) {
                a[i].push_back(x);
                xx = i, yy = a[i].size();
                break;
            } else {
                auto k = lower_bound(a[i].begin(), a[i].end(), x);
                swap(*k, x);
            }
        return make_pair(xx, yy);
    }

} u, d;

int n, q, ans[Q], sum[N], a[N], rk[N];

void Add(int o) {
    for (; o <= n; o += o & -o) ++sum[o];
}

int Ask(int o) {
    int res = 0;
    for (; o; o ^= o & -o) res += sum[o];
    return res;
}

void Insert(int o) {
    int k = u.insert(o).first;
    if (k) Add(k);
    k = d.insert(-o).second;
    if (k > S) Add(k);
}

int main() {

    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        rk[i] = i;
        scanf("%d", a + i);
    }
    sort(rk + 1, rk + n + 1, [&](const int &x, const int &y) { return a[x] < a[y] || (a[x] == a[y] && x > y); } );
    for (int i = 1; i <= n; ++i)
        a[rk[i]] = n - i + 1;

    for (int i = 1; i <= q; ++i) {
        QueryList[i].indedx = i;
        scanf("%d %d", &QueryList[i].m, &QueryList[i].k);
    }
    sort(QueryList + 1, QueryList + q + 1);

    int now = 1;
    for (int i = 1; i <= n; ++i) {
        Insert(a[i]);
        for (; now <= q && QueryList[now].m == i; ++now)
            ans[QueryList[now].indedx] = Ask(QueryList[now].k);
    }

    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);

    return 0;
}