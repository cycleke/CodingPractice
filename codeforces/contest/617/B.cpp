#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n,a[110],i,j;
long long dp[110];
int main() {
	cin>>n;
	for(i=1;i<=n;++i) cin>>a[i];
	for(i=1;i<=n;++i) if(a[i]) break;
	dp[i]=1LL;j=0;
	for(++i;i<=n;++i)
	  if(a[i]) dp[i]=dp[i-1]*(j+1),j=0;
	  else dp[i]=dp[i-1],++j;
	cout<<dp[n]<<endl;
	return 0;
}
