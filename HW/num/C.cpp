#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long LL;
int diga[30], digb[30];
int dp[30][15][7];
template<class T>
T readint(T &a) {
    a = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        a = (a << 3) + (a << 1) + c - '0';
        c = getchar();
    }
    return a;
}

int dfs(int pos, int per, int sta, bool fla, bool flb) {
    if (!pos) return sta == 6 ? 0 : -1;
    if (!(~sta)) return -1;
    int &tmp = dp[pos][per][sta];
    if (!fla && !flb && ~tmp) return tmp;
    int l = fla?diga[pos]:0;
    int r = flb?digb[pos]:9;
    int ns, ret = -1, cur;
    for (int i = l; i <= r; ++i) {
        ns = 0;
        if (sta == 0) {
            if (i) ns = 1; else ns = 0;
        } else if (sta == 1) {
            if (i > per) ns = 2;
            else ns = -1;
        } else if (sta == 2) {
            if (i > per) ns = 2;
            else if (i < per) ns = 3;
            else ns = -1;
        } else if (sta == 3) {
            if (i > per) ns = 4;
            else if (i < per) ns = 3;
            else {
                if (i) ns = 4; else ns = -1;
            }
        } else if (sta == 4) {
            if (i > per) ns = 5;
            else ns = -1;
        } else if (sta == 5) {
            if (i > per) ns = 5;
            else if (i < per) ns = 6;
            else ns = -1;
        } else if (sta == 6) {
            if (i < per) ns = 6;
            else ns = -1;
        }
        if (~ns) {
            cur = dfs(pos-1, i, ns,fla && i == l, flb && i == r);
            if (~cur) ret = max(ret,cur+i);
        }
    }
	if (!fla && !flb) tmp = ret;
	return ret;
}

int main() {
    int T, ca = 0, len, ans; LL a, b;
    readint(T);
    memset(dp, -1, sizeof(dp));
    while (T--) {
        readint(a); readint(b);
        len = 0;
        while (b) {
            diga[++len] = a % 10; digb[len] = b % 10;
            a /= 10; b /= 10;
        }
        ans = dfs(len, 0, 0, 1, 1);
        printf("Case %d: ",++ca);
          if(ans!=-1)
             printf("%d\n",ans);
          else
             printf("0\n");
    }
    return 0;
}
