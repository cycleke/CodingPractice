#include<cstdio>
#include<iostream>
using namespace std;
#define maxn 50010
#define cint const int&
int dis[maxn];
int dep[maxn<<1];
int oe[maxn<<1],first[maxn];
int p[maxn][18];
int cnt(0);
struct edge{
	int to,wei;
	edge* next;
};
edge* head[maxn];
int n;
void adde(cint x,cint y,cint z){
	edge* ne = new edge;
	ne->to = y;ne->wei = z;
	ne->next = head[x];head[x] = ne;
}

void dfs(cint u,cint deep,cint fa){
	oe[++cnt] = u;
	dep[cnt] = deep;
	if(!first[u]) first[u] = cnt;
	for(edge* i = head[u];i!=NULL;i=i->next)
	if(i->to!=fa){
		dis[i->to] = dis[u] + i->wei;
		dfs(i->to,deep+1,u);
		oe[++cnt] = u;
		dep[cnt] = deep;
	}
}

inline int gmin(cint a,cint b){
	if(dep[first[a]]>dep[first[b]]) return b;
	return a;
}

void rmq(){
	for(int i = 1;i <= cnt;++i) p[i][0] = oe[i];
	for(int i = 1;i <= 17;++i)
			for(int j = 1;j <= cnt;++j)
			if(j + (1<<i)-1 <= cnt)
			p[j][i] = gmin(p[j][i-1],p[j+(1<<(i-1))][i-1]);
}

int lca(int a,int b){
	int x(0);
	a = first[a],b = first[b];
	if(a>b){
		a = a^b;b = a^b;a = a^b;
	}
	while(1<<(x+1)<=b-a+1) ++x;
	return gmin(p[a][x],p[b+1-(1<<x)][x]);
}

int main(){
	freopen("A.in","r",stdin);
	scanf("%d",&n);
	int a,b,c;
	for(int i = 1;i < n;++i){
		scanf("%d%d%d",&a,&b,&c);
		adde(++a,++b,c);adde(b,a,c);
	}
	dfs(1,1,0);
	rmq();
	int m;
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&a,&b);
		printf("%d",dis[a+1] + dis[b+1] - dis[lca(a+1,b+1)]*2);
		if(m) puts("");
	}
	return 0;
}
