#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int dp[1010], mx[20], num[20], a[20][20];

int main() {
	int s, n;
	while (~scanf("%d",&s)&&s) {
		scanf("%d", &n);
		for (int i=1;i<=n;++i) {
			scanf("%d",num+i);
			for (int j=1;j<=num[i];++j) scanf("%d",a[i]+j);
			memset(dp, 63, sizeof dp);
			dp[0] = 0;
			for (int j = 1; j < 1010; ++j) {
				for (int k=1;k<=num[i]&&j>=a[i][k];++k)
				  dp[j] = min(dp[j],dp[j-a[i][k]]+1);
				if (dp[j]>s) {mx[i]=j-1;break;}
			}
		}
		int mxx = -1, id=0;
		for (int i = 1; i <= n; ++i)
		  if (mx[i]>mxx) mxx=mx[i],id=i;
		  else if (mx[i]>=mxx) {
			  if (num[i]<num[id]) id = i;
			  else if(num[i]==num[id]){
				  bool ok = false;
				  for (int j= num[i]; j>0; --j)
					if (a[i][j]^a[id][j]) {
						ok = a[i][j]<a[id][j];
						break;
					}
				  if (ok) id = i;
			  }
		  }
		printf("max coverage =%4d :",mx[id]);
		for (int i = 1; i <= num[id]; ++i)
		  printf("%3d",a[id][i]);
		printf("\n");
	}
	return 0;
}
