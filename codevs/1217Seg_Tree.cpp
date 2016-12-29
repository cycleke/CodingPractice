#include<cstdio>
#define R(u) (u<<1|1)
#define L(u) (u<<1)
#define cint const int&
#define maxn 1000010

struct node{
    int l,r;
    int mind,sub;
}N[maxn << 2];

inline int min(cint a,cint b){
    return (a > b)?b:a;
}

inline int read(){
	int a = 0;
	char s = getchar();
	while(s < '0' || s > '9') s = getchar();
	while(s >='0' && s <= '9') a = a*10 + s - '0',s = getchar();
	return a;
}

void pushup(cint u){
    N[u].mind = min(N[R(u)].mind,N[L(u)].mind);
}

void pushdown(cint u){
    N[R(u)].sub+=N[u].sub;
    N[L(u)].sub+=N[u].sub;
    N[R(u)].mind -= N[u].sub;
    N[L(u)].mind -= N[u].sub;
    N[u].sub = 0;
}

void build(cint u,cint l,cint r){
    N[u].l = l;N[u].r = r;
    N[u].sub = 0;
    if(l == r){
        scanf("%d",&N[u].mind);
        return;
    }
    int mid = (l+r)>>1;
    build(L(u),l,mid);
    build(R(u),mid+1,r);
    pushup(u);
}

int query(cint u,cint x,cint y){
    if(N[u].l >= x && N[u].r <= y) return N[u].mind;
    if(N[u].sub) pushdown(u);
    int mid = (N[u].l + N[u].r)>>1;
    if(y <= mid) return query(L(u),x,y);
    if(x > mid) return query(R(u),x,y);
    return min(query(L(u),x,mid),query(R(u),mid+1,y));
}

void updata(cint u,cint x,cint y,cint z){
    if(N[u].l >= x && N[u].r <= y) {
        N[u].mind -= z;
        N[u].sub += z;
        return;
    }
    if(N[u].sub) pushdown(u);
    int mid = (N[u].l + N[u].r)>>1;
    if(y <= mid) updata(L(u),x,y,z);
    else if(x > mid) updata(R(u),x,y,z);
    else {updata(L(u),x,mid,z); updata(R(u),mid+1,y,z);}
    pushup(u);
}

int main(){
    int n,m;
    n = read();
    m = read();
    build(1,1,n);
    int d,s,t,i = 1;
    while(i <= m){
        d = read();s = read();t = read();
        if(query(1,s,t)>=d) updata(1,s,t,d);
        else{
            puts("-1");
            printf("%d",i);
            return 0;
        }
        ++i;
    }
    putchar('0');
    return 0;
}
