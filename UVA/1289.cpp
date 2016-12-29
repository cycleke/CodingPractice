#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define cmin(a,b) ((b)<a?a=(b):1)
const int N=2505,M=55;
int dp[N][M],cnt[N], in[N][M], in_Tim,n,m;
pair<int,int> s[N];

void init() {
	int i,j,t,c;
	m=c=0; ++in_Tim;
	for(i=1;i<=n;++i) {
		scanf("%d",&t);
		while(t--) {
			scanf("%d",&s[++c].first);
			s[c].second=i;
		}
	}
	sort(s+1,s+c+1);
	c=unique(s+1,s+c+1)-s-1;
	for(i=1;i<=c;++i) {
		++m;t=i;
		while(s[t].first==s[t+1].first&&t<c) ++t;
		for(j=i;j<=t;++j)
		  in[m][s[j].second]=in_Tim;
		cnt[m]=t-i+1;
		i=t;
	}
}

int cal() {
	memset(dp,63,sizeof dp);
	int ans=0x3f3f3f3f,i,j,k;
	for(i=1;i<=n;++i)
	  if(in[1][i]==in_Tim) dp[1][i]=cnt[1];
	for(i=2;i<=m;++i)
	  for(j=1;j<=n;++j)
		if(in[i][j]==in_Tim) for(k=1;k<=n;++k)
		  if(in[i][k]==in_Tim&&(cnt[i]==1||k!=j))
			cmin(dp[i][j],dp[i-1][k]+cnt[i]-1);
		  else cmin(dp[i][j],dp[i-1][k]+cnt[i]);
	for(i=1;i<=n;++i)
	  cmin(ans,dp[m][i]);
	return (ans<<1)-n-1;
}

int main() {
	int ca=0;
	while(scanf("%d",&n)^EOF) {
		init(); 
		printf("Case %d: %d\n",++ca,cal());
	}
	return 0;
}
