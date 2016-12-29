#include <cstdio>
#include <algorithm>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0'||'9'<c)f|=c=='-';a=c-'0';
	while(c=getchar(),c>='0'&&c<='9')a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define MS 200002
#define W 2000005
struct D{int x,y,v,op,id,pos;}p[MS],t[MS];
bool operator <(const D&a,const D&b){
	if(a.x^b.x)return a.x<b.x;
	if(a.y^b.y)return a.y<b.y;
	return a.op<b.op;
}
int ans[10002],C[W];
inline void add(int x,int v){for(;x<W;x+=x&-x)C[x]+=v;}
inline int sum(int x){int r=0;for(;x;x-=x&-x)r+=C[x];return r;}
void solve(int l,int r){
	if(l>=r)return;
	int m=l+r>>1,t1=l,t2=m+1,i;
	for(i=l;i<=r;++i)
		if(p[i].id<=m&&!p[i].op)add(p[i].y,p[i].v);
		else if(p[i].id>m&&p[i].op)ans[p[i].pos]+=p[i].v*sum(p[i].y);
	for(i=l;i<=r;++i)
		if(p[i].id<=m&&!p[i].op)add(p[i].y,-p[i].v);
	for(i=l;i<=r;++i)t[(p[i].id<=m)?t1++:t2++]=p[i];
	for(i=l;i<=r;++i)p[i]=t[i];
	solve(l,m);solve(m+1,r);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1176.in","r",stdin);
	freopen("1176.out","w",stdout);
#endif
	geti(),geti();
	int t,cnt=0,x1,x2,y1,y2;
	while(true) {
		t=geti();
		if(t<2){
			x1=geti(),y1=geti();
			p[++cnt]=(D){x1,y1,geti(),0,cnt,0};
		} else if(t<3){
			x1=geti(),y1=geti(),x2=geti(),y2=geti();
			++*ans;
			p[++cnt]=(D){x1-1,y1-1, 1,1,cnt,*ans};
			p[++cnt]=(D){x2  ,y2  , 1,1,cnt,*ans};
			p[++cnt]=(D){x1-1,y2  ,-1,1,cnt,*ans};
			p[++cnt]=(D){x2  ,y1-1,-1,1,cnt,*ans};
		}else break;
	}
	std::sort(p+1,p+cnt+1);
	solve(1,cnt);
	for(t=1;t<=*ans;++t)printf("%d\n",ans[t]);
	return 0;
}
