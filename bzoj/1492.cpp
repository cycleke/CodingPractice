#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define eps 1e-9
#define oo 1e20
struct D{
	double a,b,r,x,y,k;int id;
	inline void init(int _id){
		scanf("%lf%lf%lf",&a,&b,&r);
		k=-a/b;id=_id;
	}
	inline bool operator < (const D&x)const{return x.k<k;}
}p[N],t[N];
double dp[N];int st[N];
inline void cmax(double&a,double b){if(a<b)a=b;}
inline double getk(int i,int j) {
	if(!j) return -oo;
	if(fabs(p[i].x-p[j].x)<eps)return oo;
	return (p[i].y-p[j].y)/(p[i].x-p[j].x);
}
void solve(int l,int r){
	if(l>=r) {
		cmax(dp[l],dp[l-1]);
		p[l].y=dp[l]/(p[l].a*p[l].r+p[l].b);
		p[l].x=p[l].r*p[l].y;return;
	}
	int m=l+r>>1,t1=l,t2=m+1,i,j,tp=0;
	for(i=l;i<=r;++i)(p[i].id<=m)?t[t1++]=p[i]:t[t2++]=p[i];
	for(i=l;i<=r;++i)p[i]=t[i];
	solve(l,m);tp=0;
	for(i=l;i<=m;++i){
		while(1<tp&&getk(st[tp-1],st[tp])<getk(st[tp-1],i)+eps)--tp;
		st[++tp]=i;
	}st[++tp]=0;j=1;
	for(i=m+1;i<=r;++i) {
		while(j<tp&&getk(st[j],st[j+1])+eps>p[i].k)++j;
		cmax(dp[p[i].id],p[st[j]].x*p[i].a+p[st[j]].y*p[i].b);
	}solve(m+1,r);
	for(i=l,t1=l,t2=m+1;i<=r;++i)
		if(t1<=m&&(p[t1].x<p[t2].x||((fabs(p[t1].x-p[t2].x)<eps&&p[t1].y<p[t2].y))||t2>r))t[i]=p[t1++];
		else t[i]=p[t2++];
	for(i=l;i<=r;++i)p[i]=t[i];
}
int main() {
	int n;
	scanf("%d%lf",&n,dp);
	for(register int i=1;i<=n;++i)(p+i)->init(i);
	std::sort(p+1,p+n+1);
	solve(1,n);
	printf("%.3lf",dp[n]);
	return 0;
}
