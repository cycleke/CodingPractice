#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define cint const int&

int C[110][110];
int f[110];
int n,m,k,e;
struct edge{
	int to,w;
	edge* next;
};
edge* head[110];
int vis[110];
int pos[23];
int dis[23];
bool inq[23];
void adde(cint a,cint b,cint c){
	edge* n = new edge;
	n->to = b;n->w = c;
	n->next = head[a];head[a]=n;
}

int SPFA(cint cur){
	memset(dis,127,sizeof(dis));
	queue<int>q;
	q.push(1);
	int p;
	dis[1]=0;
	while(!q.empty()){
		p = q.front();q.pop();
		inq[p] = 0;
		for(edge* i = head[p];i!=NULL;i=i->next){
			if(dis[i->to] > dis[p]+i->w&&!(pos[i->to]&cur)){
				dis[i->to] = dis[p]+i->w;
				if(!inq[i->to]){
					q.push(i->to);
					inq[i->to] = 1;
				}
			}
		}
	}
	if(dis[m] < *dis) return dis[m];
	return -1;
}

void work(){
	int cur,x;
	for(int i = 1;i<=n;++i){
		cur = 0;
		for(int j = i;j <= n;++j){
			cur |= vis[j];
			x = SPFA(cur);
			if(x==-1){
				for(int o = j;o<=n;++o) C[i][o] = -1;
				break;
			}
			C[i][j] = x;
		}
		
	}
	f[0] = 0;f[1] = C[1][1];
	for(int i = 2;i <= n;++i){
		f[i] = (C[1][i]==-1)?(*dis):(C[1][i]*i);
		for(int j = 1;j <= i;++j)
		if(C[j][i]!=-1)
		f[i] = min(f[i],f[j-1]+C[j][i]*(i-j+1)+k);
	}
	printf("%d",f[n]);
}

int main(){
	scanf("%d%d%d%d",&n,&m,&k,&e);
	int a,b,c;
	for(int i = 0;i<e;++i){
		scanf("%d%d%d",&a,&b,&c);
		adde(a,b,c);adde(b,a,c);
	}
	for(int i = 1;i<=m;++i)pos[i]=1<<(i-1);
	int x;
	scanf("%d",&x);
	for(int i = 0;i < x;++i){
		scanf("%d%d%d",&a,&b,&c);
		for(int j = b;j<=c;++j)vis[j]|=pos[a];
	}
	work();	
	return 0;
}
