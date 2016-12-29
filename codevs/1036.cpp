#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
#define maxn 30010
#define exc(a,b) { a = a^b;b = a^b;a = a^b; }
#define cint const int&
int p[maxn][16];
struct edge{
	int to;
	edge* next;
};

edge* head[maxn];
int dep[maxn];
void dfs(cint u,cint fa){
	dep[u] = dep[fa]+1;
	p[u][0] = fa;
	for(int i = 1;i <= 15;++i) p[u][i] = p[p[u][i-1]][i-1];
	for(edge* i = head[u];i!=NULL;i=i->next){
		if(i->to != fa) dfs(i->to,u);
	}
}

void adde(cint a,cint b){
	edge* n = new edge;
	n->to = b;n->next = head[a];
	head[a] = n;
}

int lca(int a,int b){
	if(dep[a]>dep[b]) exc(a,b);
	for(int i = 15;i>=0;--i)
	if(dep[a]<=dep[b] - (1<<i)) b = p[b][i];
	if(a==b) return a;
	for(int i = 15;i >= 0;--i){
		if(p[a][i]==p[b][i]) continue;
		a = p[a][i];b = p[b][i];
	}
	return p[a][0];
}

int main(){
	int n,m;
	scanf("%d",&n);
	int a,b;
	for(int i = 1;i < n;++i){
		scanf("%d%d",&a,&b);
		adde(a,b);adde(b,a);
	}
	dfs(1,0);
	int ans(0);
	scanf("%d",&m);
	scanf("%d",&a);
	for(int i = 1;i < m;++i){
		scanf("%d",&b);
		ans += dep[a] + dep[b] - 2 * dep[lca(a,b)];
		a = b;
	}
	cout << ans;
	return 0;
}
