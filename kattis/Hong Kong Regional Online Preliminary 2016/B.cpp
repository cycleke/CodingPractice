#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200005;

vector < int > edge[maxn];
int in[maxn], out[maxn], size[maxn], order, a[20];

void dfs(int u) {
    in[u] = ++order;
    size[u] = 1;
    for (int v : edge[u]) {
        dfs(v);
        size[u] += size[v];
    }
    out[u] = order;
}

inline bool compare(const int &x, const int &y) {
    return size[x] > size[y];
}

int main() {

    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        int fa;
        scanf("%d", &fa);
        edge[fa].push_back(i);
    }

    dfs(0);

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; ++i)
            scanf("%d", a + i);
        sort(a, a + m, compare);
        int Total = 0;
        //for (int i = 0; i < m; ++i) printf("%d%c", a[i], " \n"[i == m - 1]);
        for (int i = 0; i < m; ++i) {
            bool flag = true;
            for (int j = 0; j < i; ++j)
                if (in[a[j]] <= in[a[i]] && out[a[j]] >= out[a[i]]) {
                    flag = false;
                    break;
                }
            if (flag) Total += size[a[i]];
        }
        printf("%d\n", Total);
    }

    return 0;
}
