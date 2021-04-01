#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <set>
using namespace std;

const int Maxn = 200005;
struct edge {
	int to,dis; edge *next;
}E[Maxn << 1], *head[Maxn];
int N, totedge(-1), pos, from[Maxn];
bool vis[Maxn];
edge *f[Maxn];
long long maxdis;
typedef long long LL;
inline void adde(const int& a,const int& b,const int& c) {
	edge *ne = E + (++totedge);
	ne->dis = c; ne->to = b;
	ne->next = head[a]; head[a] = ne;
}

#define clr(a,b) memset(a,b,sizeof(a))

void dfs1(const int& u,const int& fa,const long long& d) {
	if (d > maxdis) {
		maxdis = d; pos = u;
	}
	for (edge *it = head[u]; it; it = it->next) {
		if (it->to == fa) continue;
		dfs1(it->to,u,d + it->dis);
	}
}

void dfs2(const int& u,const int& fa,const long long& d) {
	if (d > maxdis) {
		maxdis = d; pos = u;
	}
	for (edge *it = head[u]; it; it = it->next) {
		if (it->to == fa) continue;
		from[it->to] = u; f[it->to] = it;
		dfs2(it->to,u,d + it->dis);
	}
}

LL newdis;

void dfs3(const int& u,const int& fa,const LL& d) {
	if (d > newdis) {
		newdis = d;
	}
	for (edge *it = head[u]; it; it = it->next) {
		if (it->to == fa || vis[it->to]) continue;
		dfs3(it->to,u,d + it->dis);
	}
}

int main() {
	int N, a, b, c, ans, cnt;
	scanf("%d", &N); clr(f,0); clr(from,-1);
	for (int i = 1; i < N; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		adde(a,b,c); adde(b,a,c);
	}
	maxdis = -1; dfs1(1,-1,0L);
	a = pos; ans = 0;
	maxdis = -1; dfs2(a,-1,0L);
	cout << maxdis << endl;
	vis[pos] = 1; vis[a] = 1;
	for (edge *it = f[pos]; it; it = f[from[it->to]]) {
		 vis[it->to] = 1;
	}
	LL ndis(0); ans = cnt = 0;
	for (edge *it = f[pos]; it; it = f[from[it->to]]) {
		++cnt;
		newdis = -1; dfs3(from[it->to],-1,0); ndis += it->dis;
		if (ndis == newdis) ans = cnt;
		if (ndis + newdis == maxdis) break;
	}
	ans = cnt - ans;
	cout << ans;
	return 0;
}
