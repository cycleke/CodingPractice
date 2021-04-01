#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <cstring>
using namespace std;

struct edge {
	int to; edge *next;
}E[80005], *head[10005];
int Belong[40005], Bcnt, totedge, tottime, totv, ans;
int v[10005], nv[10005], n, m, per[10005], sum[10005], low[10005];
bool ins[10005];
typedef pair<int,int> pii;
edge *Edge[10005];
stack<int>s;
pii tmpe[20005];
#define clr(a,b) memset(a,b,sizeof(a))
#define MK make_pair
void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}

void addE(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = Edge[a];
	Edge[a] = ne;
}

void dfs1(const int& u,const int& fa) {
	low[u] = per[u] = ++tottime;
	bool flag = 0;
	s.push(u); ins[u] = true;
	for (edge* i = head[u]; i; i = i->next) {
		if(i->to == fa && !flag) {flag=1;continue;}
        if(!per[i->to]) dfs1(i->to,u);
        low[u]=min(low[u],low[i->to]);
	}
	if (per[u] == low[u]) {
		++Bcnt; int v;
		while (1){
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			if (u == v) break;
		}
	}
}

int dfs2(const int& u) {
	sum[u] = nv[u];
	for (edge* i = Edge[u]; i; i = i->next) 
		if (!sum[i->to]) sum[u] += dfs2(i->to);
	return sum[u];
}

void dfs3(const int& u,const int& fa) {
	for (edge* i = Edge[u]; i; i = i->next) 
		if (i->to != fa) {
			ans = min(ans,abs(totv - (sum[i->to]<<1)));
			dfs3(i->to,u);
		}
}

int main() {
	int a, b;
	while (scanf("%d%d", &n, &m) == 2) {
		clr(head,0); clr(Belong,0); clr(nv,0);
		clr(Edge,0); clr(sum,0); clr(per,0);
		while(!s.empty()) s.pop();
		totv = tottime = totedge = Bcnt = 0; ans = 1 << 30;
		for (int i = 0; i < n; ++i) scanf("%d", v + i), totv += v[i];
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b); adde(a,b); adde(b,a);
			tmpe[i] = MK(a,b);
		}
		for (int i = 0; i < n; ++i) if(!per[i]) dfs1(i,-1);
		if (Bcnt == 1) {
			puts("impossible");
		}else {
			for (int i = 0; i < n; ++i) nv[Belong[i]] += v[i];
			for (int i = 0; i < m; ++i) {
				a = tmpe[i].first, b = tmpe[i].second;
				a = Belong[a], b = Belong[b];
				if (a != b) {
					addE(a,b); addE(b,a);
				}
			}
			dfs2(1); dfs3(1,0);
			printf("%d\n", ans);
		}
	}
	return 0;
}
