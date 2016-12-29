#include <cstdio>
#include <cstring>
int dp[102][102][12],s[102][3];
#define ni(a) (a<'0'||'9'<a)
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),ni(c))f|=c=='-';a=c-'0';
	while(c=getchar(),!ni(c))a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
inline void cmax(int &a,int b){a<b?a=b:1;}
inline int max(int a,int b){return a<b?b:a;}
int main() {
	int n=geti(),m=geti(),k=geti(),i,j,o,h;
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			s[i][j]=s[i-1][j]+geti();
	if(m<2) {
		int (*f)[12]=dp[0];
		for(i=1;i<=n;++i)
			for(j=1;j<=k;++j) {
				f[i][j]=f[i-1][j];
				for(o=0;o<i;++o)
					cmax(f[i][j],f[o][j-1]+s[i][1]-s[o][1]);
			}
		printf("%d\n",f[n][k]);
	}else{
		for(i=1;i<=n;++i)
			for(j=1;j<=n;++j)
				for(o=1;o<=k;++o) {
					dp[i][j][o]=max(dp[i][j-1][o],dp[i-1][j][o]);
					for(h=0;h<i;++h)
						cmax(dp[i][j][o],dp[h][j][o-1]+s[i][1]-s[h][1]);
					for(h=0;h<j;++h)
						cmax(dp[i][j][o],dp[i][h][o-1]+s[j][2]-s[h][2]);
					if(i==j)
						for(h=0;h<i;++h)
							cmax(dp[i][j][o],dp[h][h][o-1]+s[i][1]-s[h][1]+s[i][2]-s[h][2]);			 
				}
		printf("%d\n",dp[n][n][k]);
	}
	return 0;
}
