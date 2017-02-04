#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define  ll long long
#define endl '\n'
int dp[60][200][2100],ans,num[200],need[200],po[200],cost[200];
vector<int>v[200];
#define INF 0x3f3f3f3f
int m,g[2100],pre[100];
void treedp(int x)
{
	if(!v[x].size())
	{
		num[x]=min(num[x],m/cost[x]);
		for(int j=0;j<=num[x];j++)
		  for(int k=j;k<=num[x];k++)
			dp[x][j][k*cost[x]]=(k-j)*po[x];
		return;
	}
	num[x]=INF;
	for(int i=0;i<v[x].size();i++)
	{
		treedp(v[x][i]);
		num[x]=min(num[x],num[v[x][i]]/need[v[x][i]]);
	}
	for(int i=0;i<=num[x];i++) dp[x][i][0]=0;
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i];
		for(int j=0;j<=num[x];j++)
		{
			memcpy(g,dp[x][j],sizeof(dp[x][j]));
			memset(dp[x][j],-1,sizeof(dp[x][j]));
			for(int k=0;k<=m;k++)
			  for(int w=0;w<=k;w++)
				if(g[k-w]!=-1&&dp[y][j*need[y]][w]!=-1)
				  dp[x][j][k]=max(dp[x][j][k],g[k-w]+dp[y][j*need[y]][w]);
		}
	}
	for(int i=0;i<=num[x];i++)
	  for(int j=i;j<=num[x];j++)
		for(int k=0;k<=m;k++)
		  if(dp[x][j][k]!=-1)
			dp[x][i][k]=max(dp[x][i][k],dp[x][j][k]+(j-i)*po[x]),ans=max(ans,dp[x][i][k]);
}
int main()
{
	int n,x,y,z;
	char s[10];
	scanf("%d%d",&n,&m);
	memset(pre,0,sizeof(pre));
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++)
	{
		scanf("%d%s",&po[i],s);
		if(s[0]=='B') scanf("%d%d",&cost[i],&num[i]);
		else
		{
			scanf("%d",&x);
			while(x--)
			{
				scanf("%d%d",&y,&z);
				need[y]=z;pre[y]=i;
				v[i].push_back(y);
			}
		}
	}
	for(int i=1;i<=n;i++) 
	  if (!pre[i]){
		  v[0].push_back(i);
		  need[i] = 1;
		  po[0] += po[i];
	  }
	treedp(0);
	cout<<ans<<endl;
	return 0 ;
}
