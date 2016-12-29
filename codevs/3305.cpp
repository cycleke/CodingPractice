#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
#define maxn 400010
#define cint const int&
#define exc(a,b) { a = a^b;b = a^b;a = a^b; }
#define LL long long
#define maxx(a,b,c) max(max(a,b),c)
int p[maxn][20],fmax[maxn][20],fmin[maxn][20];
int from[maxn][20],to[maxn][20];
int dep[maxn];
int A[maxn];
struct edge{
	int to;
	edge* next;
};
edge* head[maxn];

inline int readint(){
	int a(0);
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		a = a * 10 + c - '0';
		c = getchar();
	}
	return a;
}

void adde(cint a,cint b){
	edge* ne = new edge;
	ne->to = b;ne->next = head[a];
	head[a] = ne;
}

void dfs(cint u,cint fa){
	p[u][0] = fa;
	dep[u] = dep[fa] + 1;
	fmax[u][0] = max(A[u],A[fa]);
	fmin[u][0] = min(A[u],A[fa]);
	from[u][0] = A[fa] - A[u];
	to[u][0] = A[u] - A[fa];
	for(int i = 1;i < 20;++i){
		if(dep[u] < (1 << i)) break;
		p[u][i] = p[p[u][i-1]][i-1];
		fmax[u][i] = max(fmax[p[u][i-1]][i-1],fmax[u][i-1]);
		fmin[u][i] = min(fmin[p[u][i-1]][i-1],fmin[u][i-1]);
		from[u][i] = maxx(from[p[u][i-1]][i-1],from[u][i-1],fmax[p[u][i-1]][i-1] - fmin[u][i-1]);
		to[u][i] = maxx(to[p[u][i-1]][i-1],to[u][i-1],fmax[u][i-1]- fmin[p[u][i-1]][i-1]);
	}
	for(edge* i = head[u];i != NULL;i = i->next){
		if(i->to != fa)dfs(i->to,u);
	}
}
int ans;

int lca(int a,int b){
	if(dep[a]>dep[b]) exc(a,b);
	for(int i = 19;i>=0;--i)
	if(dep[a]<=dep[b] - (1<<i)) b = p[b][i];
	for(int i = 19;i >= 0;--i){
		if(p[a][i]==p[b][i]) continue;
		a = p[a][i];b = p[b][i];
	}
	if(a==b) return a;
	return p[a][0];
}


void work(int a,int b){
	ans = 0;
	int fa = lca(a,b);
	int mi = 123456789,ma = 0;
	int t = dep[a] - dep[fa];
	if (t>0)
	{
		for (int i=0;i<20;++i)
		{
			if (t&(1<<i))
			{
				ans=max(from[a][i],ans);
				ans=max(fmax[a][i]-mi,ans);
				mi=min(mi,fmin[a][i]);
				a=p[a][i];
			}
		}
	}
	t=dep[b]-dep[fa];
	if (t>0)
	{
		for (int i=0;i<20;++i)
		{
			if (t&(1<<i))
			{
				ans=max(to[b][i],ans);
				ans=max(ans,ma-fmin[b][i]);
				ma=max(ma,fmax[b][i]);
				b=p[b][i];
			}
		}
	}
	ans=max(ans,ma-mi);
}

int main(){
	freopen("A.in","r",stdin);
	int n,m;
	n = readint();
	for(int i = 1;i <= n;++i) A[i] = readint();
	int a,b;
	for(int i = 1;i < n;++i){
		a = readint();b = readint();
		adde(a,b);adde(b,a);
	}
	memset(fmin[0],127,sizeof(fmin[0]));
	dfs(1,0);
	m = readint();
	while(m--){
		a = readint();b = readint();
		work(a,b);
		printf("%d\n",ans);
	}
	return 0;
}
