#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define dep(i, a, b) for (int i = a; i >= b; i--)
#define fill(a, x) memset(a, x, sizeof(a))

const int N = 100000 + 5;
const int INF = 10000;

typedef long long ll;

int k, cnt;
int fa[N];
int w[N];


int dfs(int k, int x) {
    if (k == 0) return 0;
    if (k == 1) return w[x] = 1;
    int leaf_sum;
    bool flag = false;
    if (k & 1) {
        flag = true;
        k--;
    }
    // else {
    cnt++;
    fa[cnt] = x;
    w[cnt] = 1;

    cnt++;
    fa[cnt] = cnt - 1;
    w[cnt] = 1;

    cnt++;
    fa[cnt] = x;
    leaf_sum = dfs(k >> 1, cnt) + 1;
    w[x] = flag ? leaf_sum : INF;
    // }
    return leaf_sum;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("g.in", "r", stdin);
    #endif

    scanf("%d", &k);
    if (k == 1) {
        puts("2\n1\n5000 1");
        return 0;
    }
    cnt = 1;
    fill(w, -1);
    dfs(k, 1);
    printf("%d\n", cnt);
    rep(i, 2, cnt - 1) printf("%d ", fa[i]);
    printf("%d", fa[cnt]);
    puts("");
    rep(i, 1, cnt - 1) printf("%d ", w[i]);
    printf("%d\n", w[cnt]);
    return 0;
}

/**
 * 10
1 2 1 4 5 4 7 8 7
1000000000 1 1 3 1 1 1000000000 1 1 1

10
1 2 1 4 5 4 7 8 7
4 1 1 3 1 1 1000000000 1 1 1
**/
