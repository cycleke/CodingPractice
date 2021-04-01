#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int ina; char inc;
inline int geti() {
    while((inc=getchar())<'0'||inc>'9'); ina=inc-'0';
while((inc=getchar())>='0'&&inc<='9')ina=(ina<<3)+(ina<<1)+inc-'0';
    return ina;
}
#define N 100005
#define cmax(a,b) ((a)<(b)?(a)=(b):1)
struct D {
    int l,r,l0,r0,l1,r1,mx0,mx1,sum0,sum1,re,c,all;
}C[N<<2];
#define ls u<<1
#define rs u<<1|1
inline void rever(int u) {
    swap(C[u].l0,C[u].l1); swap(C[u].r0,C[u].r1);
    swap(C[u].mx0,C[u].mx1); swap(C[u].sum0,C[u].sum1);
    if(~C[u].all) C[u].all^=1;
}
inline void modify(int u,int co) {
    C[u].all=co; C[u].re=0;
    if(co) {
        C[u].sum1=C[u].l1=C[u].r1=C[u].mx1=C[u].r-C[u].l+1;
        C[u].sum0=C[u].l0=C[u].r0=C[u].mx0=0;
    } else {
        C[u].sum0=C[u].l0=C[u].r0=C[u].mx0=C[u].r-C[u].l+1;
        C[u].sum1=C[u].l1=C[u].r1=C[u].mx1=0;
    }
}
D operator + (const D&a,const D&b) {
    D t; t.l=a.l,t.r=b.r;t.re=0; t.c=-1;
    t.l0=a.l0,t.l1=a.l1;t.r0=b.r0,t.r1=b.r1;
    t.mx0=max(a.mx0,b.mx0);t.mx1=max(a.mx1,b.mx1);
    cmax(t.mx0,a.r0+b.l0),cmax(t.mx1,a.r1+b.l1);
    t.sum0=a.sum0+b.sum0,t.sum1=a.sum1+b.sum1;
    if(a.all==0) t.l0=a.mx0+b.l0; else if(a.all==1) t.l1=a.mx1+b.l1;
    if(b.all==0) t.r0=b.mx0+a.r0; else if(b.all==1) t.r1=b.mx1+a.r1;
    (a.all^b.all)?t.all=-1:t.all=a.all; return t;
}
inline void Down(int u) {
    if(C[u].l==C[u].r) return;
    if(~C[u].c) {
        modify(ls,C[u].c),modify(rs,C[u].c);
        C[ls].c=C[rs].c=C[u].c; C[u].c=-1;
    }
    if(C[u].re){
        C[ls].re^=1,C[rs].re^=1;
        rever(ls), rever(rs);
        C[u].re=0;
    }
}
void Build(int u,int l,int r) {
    C[u].l=l,C[u].r=r,C[u].c=-1;
    if(l==r) {modify(u,geti());return;}
    int mid=l+r>>1;
    Build(ls,l,mid);Build(rs,mid+1,r); C[u]=C[ls]+C[rs];
}
void Update(int u,int x,int y,int op) {
    int l=C[u].l,r=C[u].r; Down(u);
    if(x==l&&r==y) {
        if(op<2) modify(u,op),C[u].c=op;
        else rever(u),C[u].re=1;
        return;
    }int mid=(l+r)>>1;
    if(y<=mid) Update(ls,x,y,op);
    else if(x>mid) Update(rs,x,y,op);
    else Update(ls,x,mid,op),Update(rs,mid+1,y,op);
    C[u]=C[ls]+C[rs];
}
D QC(int u,int x,int y) {
    int l=C[u].l,r=C[u].r; Down(u);
    if(x==l&&r==y) return C[u];
    int mid=(l+r)>>1;
    if(y<=mid) return QC(ls,x,y);
    else if(x>mid) return QC(rs,x,y);
    return QC(ls,x,mid)+QC(rs,mid+1,y);
}
int QSum(int u,int x,int y) {
    int l=C[u].l,r=C[u].r; Down(u);
    if(l==x&&r==y) return C[u].sum1;
    int mid=(l+r)>>1;
    if(y<=mid) return QSum(ls,x,y);
    else if(x>mid) return QSum(rs,x,y);
    else return QSum(ls,x,mid) + QSum(rs,mid+1,y);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("operator.in","r",stdin);
    freopen("operator.out","w",stdout);
#endif
    int n=geti(),m=geti(),x,y,op;
    Build(1,0,n-1);
    while(m--) {
        op=geti(),x=geti(),y=geti();
        if(op<3)  Update(1,x,y,op);
        else if(op==3) printf("%d\n",QSum(1,x,y));
        else printf("%d\n",QC(1,x,y).mx1);
    }return 0;
} 
