#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0'||'9'<c);a=c-'0';
	while(c=getchar(),c>='0'&&'9'>=c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int dp[1005][1030],mod,n,cnt[12],T,ans,i,j,k,en,t;
char str[12],ch;
int main() {
	T=geti();
	while(T--) {
		n=0;
		while(ch=getchar(),ch<'0'||'9'<ch);str[n++]=ch;
		while(ch=getchar(),ch>='0'&&'9'>=ch)
		  str[n++]=ch;
		mod=geti();str[n]=0;
		memset(dp,0,sizeof dp);
		memset(cnt,0,sizeof cnt);
		dp[0][0]=1,en=1<<n;
		for(j=1;j<en;++j)
			for(i=0;i<mod;++i)
				for(k=0;k<n;++k)
					if(j&(1<<k))
						dp[i][j]+=dp[(i*10+str[k]-'0')%mod][j&(~(1<<k))];
		t=dp[0][en-1];
		for(i=0;i<n;++i) t/=(++cnt[str[i]-'0']);
		printf("%d\n",t);
	}return 0;
}
