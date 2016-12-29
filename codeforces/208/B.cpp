#include <bits/stdc++.h>
using namespace std;
char ca[60][4];
int n,cnt;
bool vis[60][60][60][60],can[60][60];
bool cal(int a,int b,int c,int d) {
	if(vis[a][b][c][d]) return 0;
	if(a==3&&can[d][c]&&can[d][b])return 1;
	if(can[d][c]&&cal(a-1,a-4,b,d))return 1;
	if(a>=4&&can[d][a-4]&&cal(a-1,d,b,c))return 1;
	vis[a][b][c][d]=true;
	return 0;
}
int main() {
	int i,j,k; scanf("%d",&n);
	for(i=0;i<n;++i)
		scanf("%s",ca[i]);
	for(i=0;i<n;++i)
		for(j=i+1;j<n;++j)
			can[i][j]=can[j][i]=(ca[i][0]==ca[j][0]||ca[i][1]==ca[j][1]);
	if(n==1||cal(n,n-3,n-2,n-1)) puts("YES");
	else puts("NO");
	return 0;
}
