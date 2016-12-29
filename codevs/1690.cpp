#include<cstdio>
#define cint const int&
#define maxn 100010
#define L(u) (u<<1)
#define R(u) (u<<1|1)

struct node{
	int l,r;
	int sum;
	bool change;
}N[maxn<<2];

void build(cint u,cint l,cint r){
	N[u].l = l;N[u].r = r;
	N[u].sum = 0;N[u].change = false;
	if(l == r) return;
	int mid = (l+r)>>1;
	build(L(u),l,mid);
	build(R(u),mid+1,r);
}

void pushdown(cint u){
	N[R(u)].change = !N[R(u)].change;
	N[L(u)].change = !N[L(u)].change;
	N[R(u)].sum = N[R(u)].r - N[R(u)].l + 1 - N[R(u)].sum;
	N[L(u)].sum = N[L(u)].r - N[L(u)].l + 1 - N[L(u)].sum;
	N[u].change = false;
}

void pushup(cint u){
	N[u].sum = N[R(u)].sum + N[L(u)].sum;
}

int query(cint u,cint x,cint y){
	if(N[u].l >= x && N[u].r <= y) return N[u].sum;
	if(N[u].change) pushdown(u);
	int mid = (N[u].l + N[u].r)>>1;
	if(y <= mid) return query(L(u),x,y);
	if(x > mid) return query(R(u),x,y);
	return query(L(u),x,mid) + query(R(u),mid+1,y);
}

void updata(cint u,cint x,cint y){
	if(x <= N[u].l && y >= N[u].r) {
		N[u].sum = N[u].r - N[u].l + 1 - N[u].sum;
		N[u].change = !N[u].change;
		return;
	}
	if(N[u].change) pushdown(u);
	int mid((N[u].l + N[u].r)>>1);
	if(y <= mid) updata(L(u),x,y);
	else if(x > mid) updata(R(u),x,y);
	else {
		updata(L(u),x,mid);
		updata(R(u),mid+1,y);
	}
	pushup(u);
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	int a,b,c;
	while(m--){
		scanf("%d%d%d",&a,&b,&c);
		if(a) printf("%d\n",query(1,b,c));
		else updata(1,b,c);
	}
	return 0;
}
