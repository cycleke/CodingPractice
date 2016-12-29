#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int n, m, totedge, dfs_time, Bcnt;
int per[20005], Belong[20005], in[20005], out[20005];
struct edge{
	int to; edge* next;
}E[50005];
edge *head[20005];
stack<int>s;
typedef pair<int,int> pii;
pii tmpe[50005];
bool ins[20005];
void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->next = head[a]; ne->to = b;
	head[a] = ne;
}
#define clr(a,b) memset(a,b,sizeof(a))

int dfs(const int& u) {
	int lowu = per[u] = ++dfs_time;
	s.push(u); ins[u] = true;
	for (edge *i = head[u]; i; i = i->next) {
		if (!per[i->to]) lowu = min(lowu,dfs(i->to));
		else if(ins[i->to]) lowu = min(lowu,per[i->to]);
	}
	if (lowu == per[u]) {
		int v; ++Bcnt;
		while(1) {
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			if (v == u) break;
		}
	}
	return lowu;
}

int main() {
	int T, a, b, in0, out0;
	scanf("%d", &T);
	while (T--) {
		clr(head,0); clr(per,0);
		clr(in,0); clr(out,0);
		Bcnt = dfs_time = 0; totedge = -1;
		in0 = out0 = 0;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b); adde(a,b);
			tmpe[i] = make_pair(a,b);
		}
		for (int i = 1; i <= n; ++i) if (!per[i]) dfs(i);
		if (Bcnt == 1) {
			puts("0"); continue;
		}
		for (int i = 0; i < m; ++i) {
			a = tmpe[i].first; b = tmpe[i].second;
			a = Belong[a], b = Belong[b];
			if (a != b) {
				++out[a]; ++in[b];
			}
		}
		for (int i = 1; i <= Bcnt; ++i){
			if (!in[i]) ++in0; if(!out[i]) ++out0;
		}
		printf("%d\n",max(in0,out0));
	}
	return 0;
}
