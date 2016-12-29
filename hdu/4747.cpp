#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10;
typedef long long LL;
//Input
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
//Mex
int a[N], nxt[N], pos[N], mex[N];
bool vis[N];

//Seg_Tree
int ly[N << 2], Max[N << 2];
LL Sum[N << 2];
#define ls u<<1
#define rs u<<1|1
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
#define MID int mid = l + r >> 1
#define Up(u) (Sum[u]=Sum[ls]+Sum[rs],Max[u]=max(Max[ls],Max[rs]))

void Down(int u, int l, int r) {
	if (~ly[u]) {
		ly[ls] = ly[rs] = ly[u]; MID;
		Sum[ls] = (mid - l + 1LL) * ly[ls];
		Sum[rs] = (r - mid) * (LL)ly[rs];
		Max[ls] = Max[rs] = ly[u]; ly[u] = -1;
	}
}
void Update(int u, int l, int r, int x, int y, int val) {
	if (l >= x && r <= y) {
		Sum[u] = (r - l + 1LL) * val;
		ly[u] = Max[u] = val;
	} else {
		MID; Down(u, l, r);
		if (y <= mid) Update(lson, x, y, val);
		else if (x > mid) Update(rson, x, y, val);
		else Update(lson, x, mid, val), Update(rson, mid + 1, y, val);
		Up(u);
	}
}
void Build(int u, int l, int r) {
	if (l < r) {
		MID; Build(lson); Build(rson); Up(u);
	} else {
		Sum[u] = Max[u] = mex[l];
	}
	ly[u] = -1;
}
LL Query(int u, int l, int r, int x, int y) {
	if (l >= x && r <= y) return Sum[u];
	MID; Down(u, l, r);
	if (y <= mid) return Query(lson, x, y);
	else if (x > mid) return Query(rson, x, y);
	else return Query(lson, x, mid) + Query(rson, mid + 1, y);
}
int Find(int u, int l, int r, int x, int y, int val) {
	if (l == r) return (val < Max[u])?l:0;
	MID, k; Down(u, l, r);
	if (x <= mid && val < Max[ls]) if (k = Find(lson, x, mid, val)) return k;
	if (y >  mid && val < Max[rs]) if (k = Find(rson, mid + 1, y, val)) return k;
	return 0;
}

#define clr(a) memset(a,0,sizeof a)

int main() {
	freopen("T.in", "r", stdin);
	int n, i, head, l; LL ans;
	while (n = geti()) {
		clr(nxt), clr(pos), clr(vis), clr(mex);
		for (i = 1; i <= n; ++i) if ((a[i] = geti()) >= N) a[i] = N - 5;
		for (ans = head = 0, i = 1; i <= n; ++i) {
			vis[a[i]] = true; nxt[i] = n + 1;
			if (pos[a[i]]) nxt[pos[a[i]]] = i; pos[a[i]] = i;
			while (vis[head]) ++head; ans += (mex[i] = head);
		}
		Build(1, 1, n);
		for (i = 1; i < n; ++i) {
			l = Find(1, 1, n, i + 1, nxt[i] - 1, a[i]);
			if (l && l < nxt[i]) Update(1, 1, n, l, nxt[i] - 1, a[i]);
			ans += Query(1, 1, n, i + 1, n);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
