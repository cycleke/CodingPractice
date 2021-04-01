#include <cstring>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;

const int Maxn = 10005, Maxm = 100005;
struct edge{
	int to; edge* next;
}E[Maxm];
int n, m, totedge, Belong[Maxn], Bcnt, per[Maxn], tottime, low[Maxn];
bool ins[Maxn];
stack<int>s;
edge *head[Maxn];
void adde(const int& x,const int& y) {
	edge *ne = E + (++totedge);
	ne->next = head[x];ne->to = y;
	head[x] = ne;
}

int dfs(const int& u){
	per[u] = low[u] = ++tottime;
	ins[u] = true; s.push(u);
	for (edge* i = head[u]; i; i = i->next) {
		if (!per[i->to]) low[u] = min(low[u],dfs(i->to));
		else if(ins[i->to]) low[u] = min(low[u],per[i->to]);
	}
	if (low[u] == per[u]) {
		int v; ++Bcnt;
		while(1) {
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			if (v == u) break;
		}
	}
	return low[u];
}

#define clr(a,b) memset(a,b,sizeof(a))
void work() {
	clr(ins,0); clr(Belong,0); clr(per,0); clr(head,0); 
	totedge = -1; tottime = 0; Bcnt = 0;
	int a,b;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &a, &b); adde(a,b);
	}
	for (int i = 1; i <= n; ++i) if(!per[i]) dfs(i);
	if (Bcnt > 1) puts("No"); 
	else puts("Yes");
}

int main() {
	while(scanf("%d%d", &n, &m) == 2){
		if (!n) return 0;
		work();
	}
}
