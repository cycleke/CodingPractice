#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
const int N=200005;
const double bal=0.6180339887498949;
int n,cnd,cmp_d,Q[4],rt,tp,stk[N],ans,p;
struct node{int d[2],mx[2],mi[2],size,sum,ls,rs,val;}C[N];
inline void cmin(int&a,const int&b){if(b<a)a=b;}
inline void cmax(int&a,const int&b){if(a<b)a=b;}
bool cmp(const int&a,const int&b) {return C[a].d[cmp_d]<C[b].d[cmp_d];}
inline void update(int x) {
	static int i,l,r;
	node&u=C[x];
	l=u.ls,r=u.rs;
	u.sum=C[l].sum+C[r].sum+u.val;
	u.size=C[l].size+C[r].size+1;
	for(i=0;i^2;++i) {
		if(l)cmin(u.mi[i],C[l].mi[i]),cmax(u.mx[i],C[l].mx[i]);
		if(r)cmin(u.mi[i],C[r].mi[i]),cmax(u.mx[i],C[r].mx[i]);
	}
}
void build(int&u,int l,int r,int _d) {
	int md=l+r>>1;  cmp_d=_d;
	nth_element(stk+l,stk+md,stk+r+1,cmp);
	u=stk[md]; C[u].sum=C[u].val;
	C[u].mx[0]=C[u].mi[0]=C[u].d[0];
	C[u].mx[1]=C[u].mi[1]=C[u].d[1];
	if(l<md)build(C[u].ls,l,md-1,_d^1);
	if(md<r)build(C[u].rs,md+1,r,_d^1);
	update(u);
}
void del(int&u) {
	if(!u) return;
	stk[++tp]=u; del(C[u].ls),del(C[u].rs); u=0;
}
inline void rebuild(int&u,int _d) {
	stk[tp=1]=++cnd; C[cnd].size=1;
	C[cnd].mx[0]=C[cnd].mi[0]=C[cnd].d[0]=Q[0];
	C[cnd].mx[1]=C[cnd].mi[1]=C[cnd].d[1]=Q[1];
	C[cnd].sum=C[cnd].val=Q[2];
	del(u); build(u,1,tp,_d);
}
void insert(int&u,int _d) {
	if(!u) {
		u=++cnd; C[u].size=1;
		C[cnd].mx[0]=C[cnd].mi[0]=C[cnd].d[0]=Q[0];
		C[cnd].mx[1]=C[cnd].mi[1]=C[cnd].d[1]=Q[1];
		C[cnd].sum=C[cnd].val=Q[2];
		return;
	}
	if(Q[_d]<C[u].d[_d]) {
		if(C[C[u].ls].size>C[u].size*bal)rebuild(u,_d);
		else insert(C[u].ls,_d^1);
	} else {
		if(C[C[u].rs].size>C[u].size*bal)rebuild(u,_d);
		else insert(C[u].rs,_d^1);
	}update(u);
}
inline bool inside(const int&u) {
	if(!u)return 0;
	return Q[0]<=C[u].mx[0]&&Q[2]>=C[u].mi[0]&&Q[1]<=C[u].mx[1]&&Q[3]>=C[u].mi[1];
}
void query(int u) {
	if(Q[0]<=C[u].mi[0]&&Q[2]>=C[u].mx[0]&&Q[1]<=C[u].mi[1]&&Q[3]>=C[u].mx[1]){ans+=C[u].sum;return;}
	if(Q[0]<=C[u].d[0]&&Q[2]>=C[u].d[0]&&Q[1]<=C[u].d[1]&&Q[3]>=C[u].d[1])ans+=C[u].val;
	if(inside(C[u].ls))query(C[u].ls);
	if(inside(C[u].rs))query(C[u].rs);
}
int main() {
	for(n=gi(),p=gi();p^3;p=gi()) {
		if(p<2)Q[0]=gi()^ans,Q[1]=gi()^ans,Q[2]=gi()^ans,insert(rt,0);
		else Q[0]=gi()^ans,Q[1]=gi()^ans,Q[2]=gi()^ans,Q[3]=gi()^ans,ans=0,query(rt),printf("%d\n",ans);
	}
	return 0;
}
