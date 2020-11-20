#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb,insign;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
#define noti(a) (a<'0'||'9'<a)
inline int geti() {
		for(insign=0;inc=getc(),noti(inc);insign|=inc=='-');
		for(ina=inc-'0';inc=getc(),!noti(inc);)ina=(ina<<3)+(ina<<1)+inc-'0';
		return insign?-ina:ina;
}
#define N 1005
int n,m,dp[10][10][N][N],lg2[N];
inline void cmax(int &a,int b) {a<b?a=b:1;}
inline int ask(int x1,int y1,int x2,int y2) {
	int k1=lg2[x2-x1+1],k2=lg2[y2-y1+1];
	int ret=max(dp[k1][k2][x1][y1],dp[k1][k2][x1][y2-(1<<k2)+1]);
	cmax(ret,dp[k1][k2][x2-(1<<k1)+1][y1]);
	cmax(ret,dp[k1][k2][x2-(1<<k1)+1][y2-(1<<k2)+1]);
	return ret;
}
void init() {
	int i,j,x,y;
	for(i=1;i<=lg2[n];++i)
		for(x=1;x+(1<<i)-1<=n;++x)
			for(y=1;y<=m;++y)
				dp[i][0][x][y]=max(dp[i-1][0][x][y],dp[i-1][0][x+(1<<i-1)][y]);
	for(i=0;i<=lg2[n];++i)
		for(j=1;j<=lg2[m];++j)
			for(x=1;x+(1<<i)-1<=n;++x)
				for(y=1;y+(1<<j)-1<=m;++y)
					dp[i][j][x][y]=max(dp[i][j-1][x][y],dp[i][j-1][x][y+(1<<j-1)]);
}
int a[N][N];
int main() {
	//freopen("D.in","r",stdin);
	int i,j,l,r,mid,T,x1,x2,y1,y2;
	for(i=2;i<N;++i) lg2[i]=lg2[i>>1]+1;
	n=geti(),m=geti();
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			if(a[i][j]=geti())
				l=min(dp[0][0][i-1][j],dp[0][0][i][j-1]),dp[0][0][i][j]=l+a[i-l][j-l];
	for(init(),T=geti();T;--T) {
		x1=geti(),y1=geti(),x2=geti(),y2=geti();
		l=0,r=min(x2-x1+1,y2-y1+1);
		while(l<r)
			if(mid=l+r+1>>1,ask(x1+mid-1,y1+mid-1,x2,y2)>=mid) l=mid;
			else r=mid-1;
		printf("%d\n",l);
	}return 0;
}
