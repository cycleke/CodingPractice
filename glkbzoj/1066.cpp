#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
using namespace std;

inline int rd(){
	char c = getchar();
	while(c<'0'||c>'9')c = getchar();
	return c - '0';
}
typedef pair<int,int> pii;
char mp[25][25];
int t, r, c, hx[1000], hy[1000], totp, totE = -1;
struct edge {
	int to, next, f, c;
}E[1000000];
int head[1000];

inline bool in_dis(const int& dx, const int& dy) {
	return (dx * dx + dy * dy) <= t;
}

inline void adde(const int& a, const int& b, const int& c) {
	E[++totE].to = b; E[totE].next = head[a];
	E[totE].c = c; E[totE].f = 0;
	head[a] = totE;
}
//
const int INF = 1 << 30;
int d[1000], dt[1000], S, T, last[1000];

int dfs(const int& u, int flow) {
	if (u == T || !flow) return flow;
	int tmp, res = 0, v;
	for (int i = last[u]; ~i; i = E[i].next) {
		v = E[i].to; last[u] = i;
		if (d[u] > d[v] && E[i].f < E[i].c) {
			tmp = dfs(v, min(flow, E[i].c - E[i].f));
			res += tmp; flow -= tmp;
			E[i].f += tmp; E[i^1].f -= tmp; 
			if (!flow) return res;
		}
	}
	if (d[S] >= INF) return res;
	if (!(--dt[d[u]])) d[S] = INF;
	if (d[u] != INF) {
		++d[u]; ++dt[d[u]]; last[u] = head[u];
	}
	return res;
}

int SAP() {
	memset(d, 0, sizeof d); memset(dt, 0, sizeof dt);
	dt[0] = totp+2; int ans = 0;
	for (int i = S; i <= T; ++i) last[i] = head[i];
	while (d[S] < INF) ans += dfs(S,INF);
	return ans;
}

//
#define MK make_pair
int main() {
	int d, a;
	scanf("%d%d%d", &r, &c, &d);
	t = d * d; 
	memset(head, -1, sizeof head);
	for (int i = 1; i <= r; ++i) 
		for (int j = 1; j <= c; ++j) {
			if (a = rd()) {
				hx[++totp] = i; hy[totp] = j;
				adde(totp,totp+1,a); adde(totp+1,totp,0);
				++totp;
			}
		}
	int tot = 0; S = 0; T = totp + 1;
	for(int i = 1; i <= r; ++i)
    {
        scanf("%s",mp[i] + 1);
        for(int j = 1;j <= c; ++j) if(mp[i][j] == 'L') ++tot;
    }
	
	for(int i = 1;i <= totp;i += 2){
        for (int j = i + 2; j <= totp; j += 2)
        if (in_dis(hx[i]-hx[j],hy[i]-hy[j])) {
        	adde(i + 1,j,tot),adde(j,i + 1,0);
        	adde(j + 1,i,tot),adde(i,j + 1,0);
        }
        if (mp[hx[i]][hy[i]] == 'L') adde(S, i, 1), adde(i ,S, 0);
        if (hx[i] <= d || hy[i] <= d || (r - hx[i] < d) || (c - hy[i] < d) ) 
			adde(i + 1, T, tot), adde(T, i + 1, 0);
	}
	//printf("%d\n", totE);
	printf("%d", tot - SAP());
	return 0;
}
