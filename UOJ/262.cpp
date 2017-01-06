#include <cstdio>
#include <cstring>
template<class data>data min(const data&a,const data&b){return a<b?a:b;}
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
double f[2005][2005],g[2005][2005],p[2005];
int dis[302][302],c[2005],d[2005];
//f chose ; g don't chose
int main() {
	int n=gi(),m=gi(),v=gi(),e=gi();
	for(int i=1;i<=n;++i)c[i]=gi();
	for(int i=1;i<=n;++i)d[i]=gi();
	for(int i=1;i<=n;++i)scanf("%lf",p+i);
	for(int i=1;i<=v;++i)
		for(int j=1;j<=v;++j)
			dis[i][j]=(i==j)?0:0x3f3f3f3f;
	for(int x,y,z;e;--e) {
		x=gi(),y=gi(),z=gi();
		if(z>=dis[x][y]) continue;
		dis[x][y]=dis[y][x]=z;
	}
	for(int k=1;k<=v;++k)
		for(int i=1;i<=v;++i)
			for(int j=1;j<=v;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=m;++j)
			f[i][j]=g[i][j]=1e9;
	f[1][1]=g[1][0]=0;
	for(int i=2;i<=n;++i) {
		int lim=min(i,m)+1;
		g[i][0]=g[i-1][0]+dis[c[i-1]][c[i]];
		for(int j=1;j<lim;++j) {
			g[i][j]=min(g[i-1][j]+dis[c[i-1]][c[i]],
						f[i-1][j]+dis[d[i-1]][c[i]]*p[i-1]+dis[c[i-1]][c[i]]*(1-p[i-1]));
			f[i][j]=min(g[i-1][j-1]+dis[c[i-1]][c[i]]*(1-p[i])+dis[c[i-1]][d[i]]*p[i],
						f[i-1][j-1]+dis[c[i-1]][c[i]]*(1-p[i])*(1-p[i-1])+
						dis[c[i-1]][d[i]]*(1-p[i-1])*p[i]+dis[d[i-1]][c[i]]*p[i-1]*(1-p[i])
						+dis[d[i-1]][d[i]]*p[i-1]*p[i]);
		}
	}
	double ans=1e9;
	for(int i=0;i<=m;++i)
		ans=min(ans,min(f[n][i],g[n][i]));
	printf("%.2lf\n",ans);
	return 0;
}
