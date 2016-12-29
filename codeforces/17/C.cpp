#include <bits/stdc++.h>
using namespace std;
#define mod 51123987
#define add(a,b) ((a+=b)>=mod)?a-=mod:1
int nxt[155][3],dp[155][55][55][55],n,i,a,b,c,o,res;
char str[155];
int main() {
	scanf("%d%s",&n,str+1);
	nxt[n][0]=nxt[n][1]=nxt[n][2]=mod;
	for(i=n;i;--i) {
		nxt[i][0]=nxt[i+1][0];
		nxt[i][1]=nxt[i+1][1];
		nxt[i][2]=nxt[i+1][2];
		if(str[i]=='a') nxt[i][0]=i;
		else if(str[i]=='b') nxt[i][1]=i;
		else nxt[i][2]=i;
	}
	memset(dp,0,sizeof dp); 
	dp[1][0][0][0]=1,o=(n+2)/3,res=0;
	for(i=1;i<=n;++i)
	  for(a=0;a<=o;++a)
		for(b=0;b<=o;++b)
		  for(c=0;c<=o;++c)
			if(dp[i][a][b][c]) {
				if(a+b+c==n&&abs(a-b)<2&&abs(b-c)<2&&abs(a-c)<2) {
					add(res,dp[i][a][b][c]); continue;
				} else if(a+b+c>n) continue;
				if(nxt[i][0]<mod) add(dp[nxt[i][0]][a+1][b][c],dp[i][a][b][c]);
				if(nxt[i][1]<mod) add(dp[nxt[i][1]][a][b+1][c],dp[i][a][b][c]);
				if(nxt[i][2]<mod) add(dp[nxt[i][2]][a][b][c+1],dp[i][a][b][c]);
			}return printf("%d\n",res),0;
}
