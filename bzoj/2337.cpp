#include <cmath>
#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct E{int to,v;E*nt;}CD[20001],*cd=CD,*hd[101];
#define adde(a,b,c) (cd->to=b,cd->v=c,cd->nt=hd[a],hd[a]=cd++)
double a[102][102];
int deg[102],n;
const double eps=1e-9;
inline void swap(double&a,double&b){double t=b;b=a,a=t;}
inline void guass() {
	register int i,j,k;
	double t;
	for(i=1;i<=n;++i) {
		for(k=i;k<=n&&fabs(a[k][i])<eps;++k);
		if(k^i)for(j=i;j<=n+1;++j)swap(a[k][j],a[i][j]);
		for(t=a[i][i],j=i+1;j<=n+1;++j)a[i][j]/=t;
		for(j=1;j<=n;++j)
			if((i^j)&&fabs(a[j][i])>eps)
				for(t=a[j][i],k=1;k<=n+1;++k)
					a[j][k]-=t*a[i][k];
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("2337.in","r",stdin);
#endif
	n=geti();
	for(register int m=geti(),i,j,k;m;--m) {
		i=geti(),j=geti(),k=geti();
		if(i^j)adde(i,j,k),adde(j,i,k),++deg[i],++deg[j];
		else adde(i,i,k),++deg[i];
	}
	double ans=0; E*it;
	for(register int i,bit=1<<30;bit;bit>>=1) {
		memset(a,0,sizeof a);
		for(i=1;i<n;++i) {
			a[i][i]=deg[i];
			for(it=hd[i];it;it=it->nt)
				if(it->v&bit)
					a[i][n+1]+=1,a[i][it->to]+=1;
				else a[i][it->to]-=1;
			a[n][n]=1;
		}
		guass();
		ans+=bit*a[1][n+1];
	}
	printf("%.3lf\n",ans);
	return 0;
}
