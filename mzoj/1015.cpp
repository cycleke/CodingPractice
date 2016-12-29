#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100010
#define SN 500
int v[N], add[SN], d[N];
int l[SN], r[SN], belong[N], block;
 
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
    while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
    return ina;
}
 
void ReBuild(int u) {
    for (int i = l[u]; i <= r[u]; ++i)
      d[i] = v[i];
    sort(d + l[u], d + r[u] + 1);
}
 
void Update(int x, int y, int val) {
    if (belong[x] == belong[y]) {
        for (int i = x; i <= y; ++i)
          v[i] += val;
        ReBuild(belong[x]); return;
    }
    for (int i = x; i <= r[belong[x]]; ++i)
      v[i] += val;
    ReBuild(belong[x]);
 
    for (int i = l[belong[y]]; i <= y; ++i)
      v[i] += val;
    ReBuild(belong[y]);
 
    for (int i = belong[x] + 1; i < belong[y]; ++i)
      add[i] += val;
}
 
int Query(int x, int y, int val) {
    int ret = -1;
    if (belong[x] == belong[y]) {
        for (int i = x; i <= y; ++i)
          if (v[i] + add[belong[x]] < val && v[i] + add[belong[x]] > ret)
            ret = v[i] + add[belong[x]];
        return ret;
    }
 
    for (int i = x; i <= r[belong[x]]; ++i)
      if (v[i] + add[belong[x]] < val && v[i] + add[belong[x]] > ret)
        ret = v[i] + add[belong[x]];
 
    for (int i = l[belong[y]]; i <= y; ++i)
      if (v[i] + add[belong[y]] < val && v[i] + add[belong[y]] > ret)
        ret = v[i] + add[belong[y]];
 
    for (int i = belong[x] + 1; i < belong[y]; ++i) {
        int ll = l[i], rr = r[i], mid, ans = l[i];
        if (d[ll]+add[i] >= val) continue;
        while (ll <= rr) {
            mid = ll + rr >> 1;
            if (d[mid]+add[i] < val) ll = mid + 1, ans = mid;
            else rr = mid - 1;
        }
        if (d[ans]+add[i]>ret) ret=d[ans]+add[i];
    }
    return ret;
}
 
int main() {
    int n = geti(), num;
    for (int i = 1; i <= n; ++i) v[i] = geti();
    block = floor(sqrt(n));
    num = n / block; if (n % block) ++num;
    for (int i = 1; i <= num; ++i)
      l[i]=(i-1)*block+1,r[i]=i*block;
    r[num] = n;
    for (int i = 1; i <= n; ++i)
      belong[i]=(i-1)/block+1;
    for (int i = 1; i <= n; ++i)
      d[i] = v[i];
    for (int i = 1; i <= num; ++i)
      sort(d + l[i], d + r[i] + 1);
 
    for (int T = 0; T < n; ++T) {
        int f = geti(), a = geti(), b = geti(), c = geti();
        if (f) printf("%d\n", Query(a,b,c));
        else Update(a,b,c);
    }
    return 0;
}
