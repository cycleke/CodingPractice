#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps=1e-6;
const int inf=0x3f3f3f3f,N=105;

int n, m;
struct P {
	double x, y;
	P(double _x=0.,double _y=0.) : x(_x),y(_y){}
	void Read() { scanf("%lf%lf",&x,&y);}
}p[N];
struct Q {
	int l,r,v;
}q[1005];
bool judge(P a,P b,P c) {
	return ((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y)) < -eps;
}
int vis[N],vis_Tim, f[N];
Q Get(P t, int v) {
	Q ret; ++vis_Tim;
	for(int i=0; i < n; ++i) 
	  if (judge(t,p[i],p[i+1]))
		vis[i]=vis_Tim;
	if (vis[0]==vis_Tim&&vis[n-1]==vis_Tim) {
		int le = n - 1, re = 0;
		while (vis[le-1]==vis_Tim) --le;
		while (vis[re+1]==vis_Tim) ++re;
		ret.l = le, ret.r = re + n;
	} else {
		int le = 0, re = n - 1;
		while (vis[le]^vis_Tim) ++le;
		while (vis[re]^vis_Tim) --re;
		ret.l = le, ret.r = re;
	}
	ret.v = v;
	return ret;
}

bool cal() {
	int ans = inf;
	for (int i = 0; i < n; ++i) {
		memset(f, 63, sizeof f);
		f[i]=0;
		for (int j = 0; j < n; ++j) {
			int r = i + j;
			for (int k = 0; k < m; ++k) {
				if (q[k].l > r) continue;
				if (q[k].r < r) continue;
				int tmp = min(q[k].r + 1, i + n);
				f[tmp] = min(f[tmp], f[r] + q[k].v);
			}
		}
		if (f[i+n]<ans) ans=f[i+n];
	}
	if (ans<inf) {
		printf("%d\n", ans);
		return true;
	} else return false;
}

int main() {
	P tmp; int v;
	while (scanf("%d", &n) ^ EOF) {
		if (!n) break;
		for (int i = 0; i < n; ++i) p[i].Read();
		p[n] = p[0];
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			tmp.Read();
			scanf("%d", &v);
			q[i] = Get(tmp, v);
		}
		if (!cal()) puts("Impossible.");
	}
	return 0;
}
