#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1001010
//Input
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9');ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9')ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
struct D{
	int a,id,sa;
	bool operator < (const D &x) const {return (a^x.a)?a>x.a:sa>x.sa;}
};
priority_queue<D>heap;
int wa[N],wb[N],sa[N],c[N],rk[N],s[N],lsc;
inline void DA(int m) {
	int *x=wa,*y=wb,p,i,j,k,n=lsc;
	for(i=0;i<m;++i) c[i]=0;
	for(i=0;i<n;++i) ++c[x[i]=s[i]];
	for(i=1;i<m;++i) c[i]+=c[i-1];
	for(i=n-1;~i;--i) sa[--c[x[i]]]=i;
	for(j=1,p=1;j<=n&&p<n;j<<=1,m=p) {
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<m;++i) c[i]=0;
		for(i=0;i<n;++i) ++c[x[y[i]]];
		for(i=1;i<m;++i) c[i]+=c[i-1];
		for(i=n-1;~i;--i) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);p=1;
		for(x[sa[0]]=0,i=1;i<n;++i)
		  x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p-1:p++;
	}
	for(i=0;i<n;++i) rk[sa[i]]=i;
}

int HA[N],Cnt,n,ca[1005][1005],p[1005];
#define FI "card"
int main() {
	int i,j,k;
	for(n=geti(),i=1;i<=n;++i) {
		p[i]=1; *ca[i]=geti();
		for(j=1;j<=*ca[i];++j) HA[Cnt++]=ca[i][j]=geti();
	}k=Cnt;
	sort(HA,HA+Cnt); Cnt=unique(HA,HA+Cnt)-HA;
	for(i=1;i<=n;++i) {
		for(j=1;j<=*ca[i];++j) s[lsc++]=lower_bound(HA,HA+Cnt,ca[i][j])-HA+1;
		s[lsc++]=1000005;
	}
	DA(1000010);
	for(i=2;i<=n;++i) *ca[i]+=*ca[i-1];
	heap.push((D){ca[1][1],1,rk[1]});
	for(i=2;i<=n;++i) heap.push((D){ca[i][1],i,rk[*ca[i-1]+i]});
	while(k--) {
		i=heap.top().a,j=heap.top().id; heap.pop();
		printf("%d ",i);
		if(p[j]>=*ca[j]-*ca[j-1]) continue;
		heap.push((D){ca[j][++p[j]],j,rk[*ca[j-1]+p[j]+j-1]});
	}return 0;
}
