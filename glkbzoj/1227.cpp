#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
#define maxn 100010

#define mod 2147483647

int hx[maxn],lx[maxn],cntx[maxn];
int C[maxn][12];
int tree[maxn];
struct node{
	int l,r,d,u,tx,x,y;
	bool is;
	int read(){
		scanf("%d%d",&x,&y);
		return x;
	}
	bool operator < (const node& a) const {
		if(y==a.y) return x < a.x;
		return y < a.y;
	}
}N[maxn];
void into(){
	for(int i = 0;i < maxn;++i){
		C[i][0] = 1;
		for(int j = 1;j <= min(i,10);++j){
			C[i][j] = C[i-1][j] + C[i-1][j-1];
		}
	}
}

int sum(int x){
	int ans(0);
	while(x){
		ans+=tree[x];
		x-=x&-x;
	}
	return ans;
}

void add(int x,int val){
	while(x<maxn){
		tree[x]+=val;
		x+=x&-x;
	}
}

int main(){
	freopen("A.in","r",stdin);
	int n,m,w,k;
	into();
	scanf("%d%d%d",&n,&m,&w);
	for(int i = 1;i <= w;++i)
		hx[i] = N[i].read();
	scanf("%d",&k);
	sort(hx+1,hx+w+1);
	int len = unique(hx+1,hx+w+1) - hx - 1;
	sort(N+1,N+w+1);
	for(int i = 1,y = -1,t;i <= w;++i){
		if(N[i].y != y) y = N[i].y,t = 0;
		N[i].l = t;++t;
		N[i].tx = lower_bound(hx+1,hx+len+1,N[i].x)-hx;
		N[i].d = cntx[N[i].tx];
		++cntx[N[i].tx];
		if(N[lx[N[i].tx]].y+1==N[i].y) N[lx[N[i].tx]].is = 1;
		lx[N[i].tx] = i;
	}
	for(int i = w,y = -1,t;i;--i){
		if(N[i].y != y) y = N[i].y,t = 0;
		N[i].r = t++;
		N[i].u = cntx[N[i].tx] - N[i].d - 1;
	}
	int ans = 0;
	for(int i = 1,y = -1;i <= w;++i){
		if(N[i].is!=1) 
		add(N[i].tx,C[N[i].u][k]*C[N[i].d+1][k]-(sum(N[i].tx)-sum(N[i].tx-1)));
		if(N[i].y==N[i+1].y) 
		ans+=C[N[i].l+1][k]*C[N[i+1].r+1][k]*(sum(N[i+1].tx-1)-sum(N[i].tx));
	}
	printf("%d",(ans)&mod); 
	return 0;
}
