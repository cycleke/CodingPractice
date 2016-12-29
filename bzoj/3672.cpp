#include <cstdio>
#include <algorithm>
using namespace std;
#define bus 1<<16
char B[bus],*S=B,*E=B;
#define gc() ((S==E&&(E=(S=B)+fread(B,1,bus,stdin),S==E))?EOF:*S++)
template<class integer>inline void gi(integer&a) {
	static char c;
	for(;c=gc(),c<'0';);a=c-'0';
	while(c=gc(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
}
template<class integer>inline void oi(integer a) {
	static char st[20],*s; s=st+18;
	if(a==0) {puts("0");return;}
	if(a<0) putchar('-'),a=-a;
	while(a)*s--=a%10+'0',a/=10;
	puts(s+1);
}
template<class data>inline void cmin(data&a,const data&b){if(b<a)a=b;}
typedef long long ll;
typedef long double ld;
typedef double db;
#define N 200010
#define eps 1e-9
/**********************************/
struct vec {
	ll x,y;
	vec(){}
	vec(ll _x,ll _y) : x(_x),y(_y){}
	vec operator - (const vec&a) const {return vec(x-a.x,y-a.y);}
	bool operator < (const vec&a) const {return (x^a.x)?x<a.x:y<a.y;}
	ld operator * (const vec&a) const {return (ld)x*a.y-(ld)y*a.x;}
	ll f(int k) const {return -k*x+y;}
	ld slope() const {return (ld)y/x;}
}MSET[N*20];
db PSET[N*20];int stp;
class Data {
protected:
	vec*v;db*sl;int n;
public:
	vec*begin() const {return v;}
	vec*end() const {return v+n;}
	void set() {v=MSET+stp;sl=PSET+stp;n=0;}
	bool empty() const {return n==0;}
	void clr() {n=0;}
	void pb(const vec&a) {
		while(1<n&&(a-v[n-2])*(v[n-1]-v[n-2])>-eps)--n;
		v[n++]=a;
	}
	void merge(const Data&a,const Data&b) {
		set();
		for(vec*p=a.begin(),*q=b.begin();p!=a.end()||q!=b.end();)
			if(q==b.end()||(p!=a.end()&&*p<*q)) pb(*p++);
			else pb(*q++);
		for(int i=0;i+1<n;++i)
			sl[i]=(v[i+1]-v[i]).slope();
		stp+=n;
	}
	ll query(const ll&a) const {
		int l=lower_bound(sl,sl+n-1,a)-sl;
		return v[l].f(a);
	}
}da[N<<2];
int lst[20],n,p[N];
ll dis[N],dp[N],low[N],q[N],s[N];
struct edge{int to;edge*nt;}CD[N],*cd=CD,*hd[N];
inline void adde(const int&a,const int&b){cd->to=b,cd->nt=hd[a],hd[a]=cd++;}
void insert(const int&pos,const vec&v){
	int u=1,l=0,r=n-1,md,dep=0;
	while(true) {
		if(r==pos) {
			int &lt=lst[dep];
			if(lt) da[lt].merge(da[lt<<1],da[lt<<1|1]);
			lt=(l==r)?0:u;
		}
		if(l==r) {da[u].set();da[u].pb(v);++stp;break;}
		md=l+r>>1;
		(pos<=md)?(u=u<<1,r=md):(u=u<<1|1,l=md+1);
		++dep;
	}
}
void erase(const int&pos) {
	int u=1,l=0,r=n-1,md,dep=0;
	while(true) {
		da[u].clr();
		if(l==r) break;
		if(lst[dep]==u)lst[dep]=0;
		md=l+r>>1;
		(pos<=md)?(u=u<<1,r=md):(u=u<<1|1,l=md+1);
		++dep;
	}
}
ll query(int u,int l,int r,int dep,const int&x,const int&y,const ll&k) {
	if(!da[u].empty()&&(x<=l&&r<=y)) return da[u].query(k);
	ll ret=1LL<<60; int md=l+r>>1;
	if(x<=md) cmin(ret,query(u<<1,l,md,dep+1,x,y,k));
	if(md< y) cmin(ret,query(u<<1|1,md+1,r,dep+1,x,y,k));
	return ret;
}
void dfs(int u,int dep) {
	s[dep]=dis[u];
	insert(dep,vec(dis[u],dp[u]));
	int v,t; edge*it;
	for(it=hd[u];it;it=it->nt) {
		v=it->to; t=lower_bound(s,s+dep,dis[v]-low[v])-s;
		dp[v]=query(1,0,n-1,0,t,dep,p[v]);
		dp[v]+=dis[v]*p[v]+q[v];
		dfs(v,dep+1);
	}
	erase(dep);
}
int main() {
	gi(n);
	int fa; gi(fa);
	for(int i=2;i<=n;++i) {
		gi(fa),gi(dis[i]);
		gi(p[i]),gi(q[i]),gi(low[i]);
		adde(fa,i);
		dis[i]+=dis[fa];
	}
	dfs(1,0);
	for(int i=2;i<=n;++i)oi(dp[i]);
	return 0;
}
