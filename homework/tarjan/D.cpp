#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;

struct edge {
	int to; edge *next;
}E[20005], *head[5005];
int totedge(-1), Bcnt(0), dfs_time(0), per[5005], Belong[5005], d[5005];
bool ins[5005];
stack<int>s;
typedef pair<int,int> pii;
pii tmpe[10005];
void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}

int dfs(const int& u,const int& fa) {
	int lowu = per[u] = ++dfs_time, flag = 0;
	s.push(u); ins[u] = true;
	for (edge *i = head[u]; i; i = i->next) {
		if (!per[i->to]) lowu = min(lowu,dfs(i->to,u));
		else if(i->to == fa && !flag) flag = 1;
		else if (ins[i->to]) lowu = min(lowu,per[i->to]);
	}
	if (lowu == per[u]) {
		int v; ++Bcnt;
		while (true) {
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			if (u == v) break;
		}
	}
	return lowu;
}

int main() {
	int F, R, a, b;
	scanf("%d%d", &F, &R);
	for (int i = R; i; --i) {
		scanf("%d%d", &a, &b); adde(a,b); adde(b,a);
		tmpe[i] = make_pair(a,b);
	}
	for (int i = 1; i <= F; ++i) 
		if (!per[i]) dfs(i,-1);
	for (int i = 1; i <= R; ++i) {
		a = tmpe[i].first; b = tmpe[i].second;
		a = Belong[a]; b = Belong[b];
		if (a != b) {
			++d[a]; ++d[b];
		}
	}
	int cnt(0);
	for (int i = 1; i <= Bcnt; ++i) if (d[i] == 1) ++cnt;
	cnt = (cnt + 1) >> 1;
	printf("%d\n", cnt);
	return 0;
}
