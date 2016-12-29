#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int INF = 0x7f7f7f7f;
struct edge {
	int to, f, c, w, next;
}Edge[40010];
int head[1010], totE, N, M, K;

void adde(const int &u, const int& v, const int &c, const int &w) {
	edge &ne = Edge[++totE];
	ne.to = v; ne.c = c; ne.f = 0; ne.w = w;
	ne.next = head[u]; head[u] = totE;
}

void adde(const int &u, const int& v, const int &c, const int &w, const int &f) {
	edge &ne = Edge[++totE];
	ne.to = v; ne.c = c; ne.f = f; ne.w = w;
	ne.next = head[u]; head[u] = totE;
}

//

int S, T, d[1010], dt[1010], last[1010];

int dfs(const int &u, int flow) {
	if (u == T) return flow;
	int res = 0, tmp;
	for (int i = last[u]; ~i; i = Edge[i].next) {
		edge &ne = Edge[i];
		if (d[u] > d[ne.to] && ne.c > ne.f) {
			tmp = dfs(ne.to, min(flow, ne.c - ne.f));
			res += tmp; flow -= tmp;
			ne.f += tmp; Edge[i ^ 1].f -= tmp;
			if (!flow) return res;
		}
	}
	if (d[S] >= INF) return res;
	if (!(--dt[d[u]])) d[S] = N;
	++d[u]; ++dt[d[u]]; last[u] = head[u];
	return res;
	
}

int SAP() {
	memset(d, 0, sizeof d);
	memset(dt, 0, sizeof dt);
	S = 1, T = N; dt[0] = N;
	for (int i = 1; i <= N; ++i) last[i] = head[i];
	int ans = 0;
	while (d[S] < N) 
		ans += dfs(S, INF);
	return ans;
}

//

bool inq[1010];
int dis[1010], from[1010], fe[1010];

bool SPFA() {
	memset(dis, 127, sizeof dis);
	queue<int>q;
	from[0] = -1;
	q.push(0); dis[0] = 0;
	int p, fen, v;
	while (!q.empty()) {
		p = q.front(); q.pop();
		inq[p] = 0;
		for (int i = head[p]; ~i; i = Edge[i].next) {
			fen = Edge[i].w; v = Edge[i].to;
			if (dis[p] + fen < dis[v] && Edge[i].c > Edge[i].f) {
				from[v] = p; fe[v] = i;
				dis[v] = dis[p] + fen;
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return dis[N] < INF;
}


int mcf() {
	int f = INF, p = N;
	while (p) {
		f = min(f, Edge[fe[p]].c - Edge[fe[p]].f);
		p = from[p];
	}
	int ans = 0; p = N;
	while (p) {
		ans += f * Edge[fe[p]].w;
		Edge[fe[p]].f += f;
		Edge[fe[p]^1].f -= f;
		p = from[p];
	}
	return ans;
}

int Expand() {
	memset(inq, 0, sizeof inq);
	memset(head, -1, sizeof head);
	int u, v, fe;
	//puts("");
	for (int i = totE; ~i; i -= 2) {
		u = Edge[i].to; v = Edge[i - 1].to;
		if (Edge[i-1].f < Edge[i-1].c) {
			adde(u, v, Edge[i-1].c, 0, Edge[i-1].f);
			//不能写adde(u, v, Edge[i-1].c - Edge[i-1].f,0)
			//不然流量没法回来
			adde(v, u, 0, 0, Edge[i].f);
		}
		adde(u, v, INF, Edge[i-1].w);
		adde(v, u, 0, -Edge[i - 1].w);
		//printf("%3d -> %3d c = %3d  w = %3d\n",u,v,Edge[i-1].c - Edge[i-1].f,Edge[i-1].w);
	}
	adde(0, 1, K, 0); adde(1, 0, 0, 0);
	int ans = 0;
	while (SPFA()) 
		ans +=mcf();
	return ans;
}

//

int main() {
	scanf("%d%d%d", &N, &M, &K);
	memset(head, -1, sizeof head); totE = -1;
	int u, v, c, w;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d%d", &u, &v, &c, &w);
		adde(u, v, c, w); adde(v, u, 0, 0);
	}
	printf("%d ", SAP());
	printf("%d\n", Expand());
	return 0;
}
