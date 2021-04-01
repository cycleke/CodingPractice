#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
const int Maxn = 100005, Maxm = 200005;
struct edge {
	int to; edge *next;
}E[Maxm << 1], *head[Maxn];
int totedge, dfs_time, Bcnt, per[Maxn], Belong[Maxn], fa[Maxn], p[Maxn][20];
int f[Maxn], dep[Maxn];
typedef pair<int, int> pii;
bool ins[Maxn];
stack<int>s;
pii tmpe[Maxm];

inline void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}

int find(const int& a) {
	return (f[a] == a)?(a):(f[a] = find(f[a]));
}

int dfs1(const int& u,const int& fa) {
	int lowu = per[u] = ++dfs_time;
	bool flag = 0;
	s.push(u); ins[u] = true;
	for (edge *i = head[u]; i; i = i->next) {
		if (!per[i->to]) lowu = min(lowu,dfs1(i->to,u));
		else if(i->to == fa && !flag) flag = 1;
		else if (ins[i->to]) lowu = min(lowu,per[i->to]);
	}
	if (per[u] == lowu) {
		++Bcnt; int v;
		while (true){
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			if (u == v) break;
		}
	}
	return lowu;
}

void dfs2(const int& u,const int& father) {
	p[u][0] = fa[u] = father; dep[u] = dep[father] + 1;
	for (int i = 1; i < 20; ++i) 
	if ((1 << i) <= dep[u]) p[u][i] = p[p[u][i-1]][i-1];
	else break;
	for (edge* i = head[u]; i; i = i->next) {
		if (i->to == father) continue;
		dfs2(i->to,u);
	}
}

int lca(int a,int b){
	if(dep[a]>dep[b]) {
		a = a^b; b = a^b; a = a^b;
	}
	for(int i = 19; ~i;--i)
	if(dep[a]<=dep[b] - (1<<i)) b = p[b][i];
	if(a==b) return a;
	for(int i = 19;i >= 0;--i){
		if(p[a][i]==p[b][i]) continue;
		a = p[a][i];b = p[b][i];
	}
	return p[a][0];
}

#define clr(a,b) memset(a,b,sizeof(a))
int main() {
	int N, M, Q, a, b, Case = 0, ans;
	while (scanf("%d%d", &N, &M)) {
		if (!N && !M) return 0;
		++Case;
		clr(head,0); clr(per,0); clr(fa,0); clr(p,0);
		Bcnt = dfs_time = 0; totedge = -1;
		for (int i = M; i; --i) {
			scanf("%d%d", &a, &b); adde(a,b); adde(b,a);
			tmpe[i] = make_pair(a,b);
		}
		for (int i = 1; i <= N; ++i)
			if (!per[i]) dfs1(i,-1);
		clr(head,0); totedge = -1; clr(dep,0); ans = 0;
		for (int i = 1; i <= Bcnt; ++i) f[i] = i;
		for (int i = M; i; --i) {
			a = tmpe[i].first; b = tmpe[i].second;
			a = Belong[a]; b = Belong[b];
			if (a != b) {
				adde(a,b); adde(b,a);
				++ans;
			}
		}
		for (int i = 1; i <= Bcnt; ++i) if(!fa[i]) dfs2(i,0);
		scanf("%d", &Q);
		printf("Case %d:\n", Case);
		for (int i = 1; i <= Q; ++i) {
			scanf("%d%d", &a, &b);
			a = find(Belong[a]); b = find(Belong[b]);
			if (a != b) {
				int fl = lca(a,b), u, ff, cnt(0);
				u = a;  ff = find(fl);
				while (u != fl) {
					if (find(u) != find(fa[u]))++cnt;
					f[u] = ff;
					u = fa[u];
				}
				u = b;
				while(u != fl) {
					if (find(u) != find(fa[u]))++cnt;
					f[u] = ff; 
					u = fa[u];
				}
				ans -= cnt;
			}
			printf("%d\n", ans);
		}
		puts("");
	}
	return 0;
}
