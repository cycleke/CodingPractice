#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

struct edge{
	int to; edge *next;
}E[20010];
edge *head[101];
int n, dfs_time, totedge, per[101];
bool ins[101], is_cut[101];
stack<int>s;
void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}
#define clr(a,b) memset(a,b,sizeof(a))

void readdata(char *S,const int& k) {
	int a;
	while(*S) {
		a = 0;
		while(*S <'0' || *S > '9') ++S;
		while(*S >= '0' && *S <= '9') {
			a = (a << 3) + (a << 1) + *S - '0';
			++S;
		}
		adde(k,a); adde(a,k);
	}
}

int dfs(const int& u,const int& fa) {
	int lowu = per[u] = ++dfs_time;
	int lowv, child = 0;
	s.push(u); ins[u] = true;
	for (edge *i = head[u]; i; i = i->next) {
		if (!per[i->to]) {
			++child;
			lowv = dfs(i->to,u); lowu = min(lowu,lowv);
			if (lowv >= per[u]) is_cut[u] = true;
		}else if (i->to != fa && ins[i->to]) lowu = min(lowu,per[i->to]);
	}
	if (fa < 0 && child == 1) is_cut[u] = false;
	if (lowu == per[u]) {
		int v;
		while (1) {
			v = s.top(); s.pop();
			ins[v] = false;
			if (u == v) break;
		}
	}
	return lowu;
}

int main() {
	int k, ans;
	char S[10000];
	clr(S,0);
	while(scanf("%d", &n)==1) {
		if (!n) return 0;
		totedge = -1; dfs_time = 0;
		clr(per,0); clr(is_cut,0); clr(head,0);
		while(1) {
			scanf("%d" ,&k);
			if (k == 0) break;
			gets(S); readdata(S,k);
		}
		for (int i = 1; i <= n; ++i) if(!per[i]) dfs(i,-1);
		ans = 0;
		for (int i = 1; i <= n; ++i) ans += is_cut[i];
		printf("%d\n", ans);
	}
	return 0;
}
