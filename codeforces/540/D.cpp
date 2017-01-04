#include <cstdio>
double dp[102][102][102];
int main() {
	int r,s,p;
	scanf("%d%d%d",&r,&s,&p);
	dp[r][s][p]=1;
	for(int i=r;i;--i)
		for(int j=s;j;--j)
			for(int k=p;k;--k) {
				int ij=i*j,jk=j*k,ik=i*k,tot=ij+jk+ik;
				double t=dp[i][j][k];
				dp[i-1][j][k]+=t*ik/tot;
				dp[i][j-1][k]+=t*ij/tot;
				dp[i][j][k-1]+=t*jk/tot;
			}
	double pr=0,ps=0,pp=0;
	for(int i=1;i<=100;++i)
		for(int j=1;j<=100;++j)
			pr+=dp[i][j][0],ps+=dp[0][i][j],pp+=dp[i][0][j];
	printf("%.9lf %.9lf %.9lf",pr,ps,pp);
	return 0;
}
