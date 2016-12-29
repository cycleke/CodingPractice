#include <map>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 50005
#define S 550
int l[S], r[S], bl[N], f[S][S], cnt[N], v[N], n, m, blo;
int HASH[N], Pos[N], R[N], L[N];
//Input
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
    while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
    return ina;
}
 
#define getcnt(a,b,c) (int)(upper_bound(Pos+L[c],Pos+R[c],b)-lower_bound(Pos+L[c],Pos+R[c],a))
 
int Stack[N], top, vis[N], TTTT;
 
inline int query(int a, int b) {
    if (a > b) swap(a, b);
    top = 0; ++TTTT;
    int ans = f[bl[a]+1][bl[b]-1], mx = getcnt(a,b,ans), t;
    t = (b<r[bl[a]])?b:r[bl[a]];
    for (int i = a; i <= t; ++i) 
      if (vis[v[i]] ^ TTTT) vis[v[i]] = TTTT, Stack[++top] = v[i];
    if (bl[a]^bl[b]) {
        for (int i = l[bl[b]]; i <= b; ++i) 
          if (vis[v[i]] ^ TTTT) vis[v[i]] = TTTT, Stack[++top] = v[i];
    }
 
    for (; top; --top) {
        t = getcnt(a,b,Stack[top]);
        if (t>mx||(t>=mx&&Stack[top]<ans)) ans=Stack[top],mx=t;
    }
 
    return HASH[ans];
}
 
int main() {
    n = geti(); blo=sqrt(n);
    for (int i=1;i<=n;++i) HASH[i]=v[i]=geti(),bl[i]=(i-1)/blo+1;
 
    sort(HASH + 1, HASH + n + 1);
    int *end = unique(HASH + 1, HASH + n + 1);
 
    for (int i = 1; i <= n; ++i) {
        v[i] = lower_bound(HASH + 1, end, v[i]) - HASH;
        ++cnt[v[i]];
    }
    int sum = 0, tot = end - HASH - 1;
    for (int i = 1; i <= tot; ++i) {
        R[i] = L[i] = sum + 1; sum += cnt[i];
    }
     
    for (int i = 1; i <= n; ++i) Pos[R[v[i]]++] = i;
    m = bl[n];
    for (int i = 1; i <= m; ++i) l[i]=(i-1)*blo+1, r[i]=i*blo;
    r[m] = n;
    int ans, mx;
    for (int u = 1; u <= m; ++u) {
        memset(cnt, 0, N << 2);
        ans = 0, mx = 0;
        for (int j = u; j <= m; ++j) {
            for (int i = l[j]; i <= r[j]; ++i) {
                ++cnt[v[i]];
                if (cnt[v[i]]>mx||(cnt[v[i]]==mx&&v[i]<ans))
                  ans = v[i], mx = cnt[v[i]];
            }
            f[u][j] = ans;
        }
    }
 
    for (int i = 1; i <= n; ++i) printf("%d\n", query(geti(), geti()));
 
    return 0;
}
