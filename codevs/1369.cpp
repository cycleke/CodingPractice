#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define R(u) (u<<1)
#define L(u) (u<<1|1)
#define maxn 200010
#define cint const int&
struct node{
	int l,r;
	int sum;
}N[maxn<<2];

void pushup(cint u){
	N[u].sum = N[R(u)].sum + N[L(u)].sum;
}

void build(cint u,cint l,cint r){
	N[u].l = l;N[u].r = r;
	if(l == r){
		scanf("%d",&N[u].sum);
		return;
	}
	int mid = (l + r)>>1;
	build(L(u),l,mid);
	build(R(u),mid+1,r);
	pushup(u);
}

int query(cint u,cint x,cint y)
{
	if(N[u].l >= x && N[u].r <=y) return N[u].sum;
	int mid = (N[u].l + N[u].r)>>1;
	if(y <= mid) return query(L(u),x,y);
	if(x > mid) return query(R(u),x,y);
	return query(L(u),x,mid) + query(R(u),mid+1,y);
}

void del(cint u,cint x){
	if(N[u].l == N[u].r){
		N[u].sum = 0;
		return;
	}
	int mid = (N[u].l + N[u].r)>>1;
	if(x <= mid) del(L(u),x);
	else del(R(u),x);
	pushup(u);
}

int main()
{
	int n,m;
	scanf("%d",&n);
	build(1,1,n);
	scanf("%d",&m);
	int x,y;
	while(m--){
		scanf("%d%d",&x,&y);
		printf("%.2lf\n",query(1,x,y)*3.14);
		del(1,(x+y)>>1);
	}
	return 0;
}
