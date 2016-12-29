#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
#define maxn 500010
#define L(u) (u<<1)
#define R(u) (u<<1|1)
#define cint const int&

struct data{
	int lc,rc,part;
	data operator  + (const data& a) const{
		data tmp;
		tmp.lc = lc;
		tmp.rc = a.rc;
		tmp.part = part + a.part;
		if(rc == a.lc) --tmp.part;
		return tmp;
	}
	void read(){
        scanf("%d",&lc);
        rc = lc;
        part = 1;
	}
	void ch(cint u){
        lc = rc = u;
        part = 1;
	}
};

struct node{
	int l,r;
	int change;
	data t;
}N[maxn<<2];
int n,c;
bool d;
int dis;

void Ro(){
	int k;
	scanf("%d",&k);
	if(d) dis = (dis + n - k)%n;
	else dis = (dis + k)%n;
}

void pushup(cint u){
    N[u].t = N[L(u)].t + N[R(u)].t;
}

void build(cint u,cint l,cint r){
    N[u].l =l;N[u].r = r;
    if(l==r){
        N[u].t.read();
        return;
    }
    int mid = (l + r)>>1;
    build(L(u),l,mid);
    build(R(u),mid+1,r);
    pushup(u);
}

void pushdown(cint u){
    N[R(u)].change = N[L(u)].change = N[u].change;
    N[R(u)].t.ch(N[u].change);N[L(u)].t.ch(N[u].change);
    N[u].change = 0;
}

void update(cint u,cint x,cint y,cint k){
    if(x<=N[u].l&&N[u].r<=y){
        N[u].change = k;
        N[u].t.ch(k);
        return;
    }
    if(N[u].change) pushdown(u);
    int mid = (N[u].l + N[u].r)>>1;
    if(y<=mid) update(L(u),x,y,k);
    else if(x>mid) update(R(u),x,y,k);
    else {
        update(L(u),x,mid,k);
        update(R(u),mid+1,y,k);
    }
    pushup(u);
}

void cal(int& x,int &y){
    if(d){
        x = (n + 2 - x - dis + n)%n;
        y = (n + 2 - y - dis + n)%n;
        x = x^y;
        y = x^y;
        x = x^y;
    }else{
        x = (x - dis + n)%n;
        y = (y - dis + n)%n;
    }
    if(!x) x = n;
    if(!y) y = n;
}

void P(){
    int x,y,k;
    scanf("%d%d%d",&x,&y,&k);
    cal(x,y);
    if(x>y) {update(1,x,n,k); update(1,1,y,k);}
    else update(1,x,y,k);
}

int fin(cint u,cint x){
    if(N[u].l==N[u].r){
        return N[u].t.lc;
    }
    if(N[u].change) pushdown(u);
    int mid = (N[u].l + N[u].r)>>1;
    if(x<=mid) return fin(L(u),x);
    return fin(R(u),x);
}

void S(){
    int x,y;
    scanf("%d%d",&x,&y);
    cal(x,y);
    int cx = fin(1,x),cy = fin(1,y);
    update(1,x,x,cy);
    update(1,y,y,cx);
}

data query(cint u,cint x,cint y){
    if(x<=N[u].l&&N[u].r<=y){
        return N[u].t;
    }
    if(N[u].change) pushdown(u);
    int mid = (N[u].l + N[u].r)>>1;
    if(y<=mid) return query(L(u),x,y);
    else if(x>mid) return query(R(u),x,y);
    else {
        return query(L(u),x,mid) + query(R(u),mid + 1,y);
    }
}

void C(){
    int ans;
    ans = query(1,1,n).part;
    if(N[1].t.lc == N[1].t.rc) --ans;
    if(!ans) ans = 1;
    printf("%d\n",ans);
}

void CS(){
    int x,y;
    scanf("%d%d",&x,&y);
    cal(x,y);
     if(x>y) {
        printf("%d\n",(query(1,x,n) + query(1,1,y)).part);
    }
    else {
    printf("%d\n",query(1,x,y).part);
    }
}

int main(){
	freopen("A.in","r",stdin);
	scanf("%d%d",&n,&c);
	build(1,1,n);
	int Q;
	string k;
	scanf("%d",&Q);
	while(Q--){
		cin >> k;
		if(k == "R")Ro();
		else if(k =="F")d = !d;
		else if(k =="P")P();
		else if(k =="S")S();
		else if(k =="C")C();
		else CS();
	}
	return 0;
}
