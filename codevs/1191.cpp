#include<cstdio>
#define R(u) (u<<1)
#define L(u) (u<<1|1)
#define cint const int&
#define maxn 200010
struct node{
	int l,r;
	int sum;
}N[maxn<<2];

void build(cint u,cint l,cint r)
{
	N[u].l = l;N[u].r = r;
	N[u].sum = r - l + 1;
	if(l == r) return;
	int mid((l + r)>>1);
	build(L(u),l,mid);
	build(R(u),mid+1,r);
}

void pushup(cint u)
{
	N[u].sum = N[R(u)].sum + N[L(u)].sum;
}

void pushdowm(int u)
{
	N[R(u)].sum = N[L(u)].sum = 0;
}

void updata(cint u,cint x,cint y)
{
	if(x <= N[u].l && y >= N[u].r) {
		N[u].sum = 0;
		return;
	}
	if(!N[u].sum) pushdowm(u);
	int mid((N[u].l + N[u].r)>>1);
	if(y <= mid) updata(L(u),x,y);
	else if(x > mid) updata(R(u),x,y);
	else {
		updata(L(u),x,mid);
		updata(R(u),mid+1,y);
	}
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
		updata(1,x,y);
		printf("%d\n",N[1].sum);
	}
	return 0;
}
