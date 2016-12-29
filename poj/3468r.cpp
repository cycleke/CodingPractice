#include<cstdio>
#include<cstring>
#include<iostream>
#define R(a) (a << 1)
#define L(a) (a << 1|1)
using namespace std;
#define maxn 100002
#define LL long long

struct node{
	int l,r;
	LL sum,add;
}N[maxn << 2];

LL A[maxn];

inline char read(){
	char a = 0;
	while(a != 'Q' && a !='C') a = getchar();
	return a;
}

void PushUp(const int& u){
    N[u].sum = N[R(u)].sum + N[L(u)].sum;
}

void Build(const int& u,const int& l,const int& r){
    N[u].l = l,N[u].r = r;
    if(l == r){
        N[u].sum = A[l];
        return;
    }
    int mid = (l + r)>>1;
    Build(L(u),l,mid);
    Build(R(u),mid + 1,r);
    PushUp(u);
}

void Pushdown(const int& u)
{
    N[R(u)].add += N[u].add;
    N[R(u)].sum += (N[R(u)].r - N[R(u)].l + 1)*N[R(u)].add;
    N[L(u)].add += N[u].add;
    N[L(u)].sum += (N[L(u)].r - N[L(u)].l + 1)*N[L(u)].add;
    N[u].add = 0;
}

LL Query(const int& u,const int& l,const int& r){
    if(l <= N[u].l && r >= N[u].r) return N[u].sum;
    if(N[u].add) Pushdown(u);
    int mid = (N[u].l + N[u].r) >> 1;
    if(r <= mid) return Query(L(u),l,r);
    if(l > mid) return Query(R(u),l,r);
    return Query(L(u),l,mid) + Query(R(u),mid + 1,r);
}

void Updata(const int& u,const int& l,const int& r,const LL& c){
     if(l <= N[u].l && r >= N[u].r) {
        N[u].add += c;
        if(l != r)N[u].sum +=(N[u].r - N[u].l + 1) * N[u].add;
        return;
     }
     N[u].sum +=(r - l + 1)*c;
     if(N[u].add) Pushdown(u);
     int mid = (N[u].l + N[u].r) >> 1;
     if(r <= mid) Updata(L(u),l,r,c);
     else if(l > mid) Updata(R(u),l,r,c);
     else {
        Updata(L(u),l,mid,c);
        Updata(R(u),mid+1,r,c);
     }
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i)scanf("%I64d",&A[i]);
	Build(1,1,n);
	int a,b;
	LL c;
	char Q;
	while(m--)
	{
		 Q = read();
		if(Q == 'Q'){
            scanf("%d%d",&a,&b);
            printf("%I64d\n",Query(1,a,b));
		}else {
            scanf("%d%d%I64d",&a,&b,&c);
            Updata(1,a,b,c);
		}
	}
	return 0;
}
