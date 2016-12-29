#include<cstdio>
#include<cstring>
#define R(u) (u<<1|1)
#define L(u) (u<<1)
#define cint const int&
#define maxn 30010

struct node{
    int l,r;
    int s;
    int num;
}N[maxn << 2];
int cnt = 0;

inline int read(int& a){
	a = 0;
	char s = getchar();
	while(s < '0' || s > '9') s = getchar();
	while(s >='0' && s <= '9') a = a*10 + s - '0',s = getchar();
	return a;
}

void pushup(cint u){
    N[u].s = N[R(u)].s+N[L(u)].s;
}

void build(cint u,cint l,cint r){
    N[u].l = l;N[u].r = r;
    if(l == r){
        N[u].s = 1;
        N[u].num = ++cnt;
        return;
    }
    int mid = (l+r)>>1;
    build(L(u),l,mid);
    build(R(u),mid+1,r);
    pushup(u);
}

int remove(cint u,cint x){
	if(N[u].num) { 
		N[u].s = 0;
		return N[u].num;
	}
	int ans;
	if(N[L(u)].s >= x) ans = remove(L(u),x);
	else ans = remove(R(u), x - N[L(u)].s);
	pushup(u);
	return ans;
}


int main(){
	int n,m;
	read(n);
	read(m);
	build(1,1,n);
	int a,b(1);
	while(n){
		a = (b - 1 + m)%n;
		if(!a)printf("%d ",remove(1,b = n));
		else printf("%d ",remove(1,b = a));
		--n;
	}
	return 0;
}
