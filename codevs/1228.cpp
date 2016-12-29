#include<cstdio>
#include<cstring>
#define R(u) (u<<1|1)
#define L(u) (u<<1)
#define cint const int&
#define maxn 100010

struct node{
    int l,r;
    int sum;
}N[maxn << 2];
int tot(0);
struct edge{
	int to;
	edge* next;
};
edge* head[maxn];
bool mark[maxn];
int in[maxn],out[maxn];

void pushup(cint u){
    N[u].sum = N[R(u)].sum+N[L(u)].sum;
}

void adde(cint a,cint b){
	edge* n = new edge;
	n->to = b;
	n->next = head[a];
	head[a] = n;
}

void dfs(cint x){
	mark[x] = true;
	in[x] = ++tot;
	for(edge* i = head[x];i != NULL;i = i->next){
		if(!mark[i->to]) dfs(i->to);
	}
	out[x] = tot;
}

void build(cint u,cint l,cint r){
	N[u].l = l,N[u].r = r;
	if(l == r){
		N[u].sum = 1;
		return;
	}
	int mid = (l+r)>>1;
	build(L(u),l,mid);
	build(R(u),mid+1,r);
	pushup(u);
}

int query(cint u,cint x,cint y){
	if(x <= N[u].l && y >= N[u].r) return N[u].sum;
	int mid = (N[u].l + N[u].r)>>1;
	if(y <= mid) return query(L(u),x,y);
	if(x > mid) return query(R(u),x,y);
	return query(L(u),x,mid) + query(R(u),mid + 1,y);
}

void change(cint u,cint x){
	if(N[u].l == N[u].r){
		if(mark[N[u].l]) --N[u].sum;
		else ++N[u].sum;
		mark[N[u].r] = !mark[N[u].r];
		return;
	}
	int mid = (N[u].l + N[u].r)>>1;
	if(x <= mid) change(L(u),x);
	else  change(R(u),x);
	pushup(u);
}

int main(){
	freopen("1228.in","r",stdin);
	int n;
	scanf("%d",&n);
	int a,b;
	for(int i = 1;i < n;++i){
		scanf("%d%d",&a,&b);
		adde(a,b);adde(b,a);
	}
	dfs(1);
	build(1,1,n);
	int m;
	char s[3];
	int x;
	scanf("%d",&m);
	//memset(mark,-1,sizeof(mark));
	while(m--){
		scanf("%s%d",s,&x);
		if(s[0] == 'Q') {printf("%d\n",query(1,in[x],out[x])); }
		else change(1,in[x]);
	}
	return 0;
}
