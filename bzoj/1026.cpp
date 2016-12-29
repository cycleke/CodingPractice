#include <cstdio>
#include <cstring>
int dp[12][10][2],dig[12];
inline int ibs(int a){return a<0?-a:a;}
int dfs(int p,int pre,bool zero,bool limited) {
	if(!p)return!zero;
	int&t=dp[p][pre][zero];
	if(!limited&&(~t))return t;
	int en=limited?dig[p]:9,r=0;
	if(zero)r=dfs(p-1,0,1,!en);
	else if(pre>=2)r=dfs(p-1,0,0,!en);
	for(int i=1;i<=en;++i)
		if(zero||ibs(i-pre)>1)
			r+=dfs(p-1,i,0,limited&&i>=en);
	if(!limited)t=r;
	return r;
}
int cal(int x){
	int l=0;
	while(x)dig[++l]=x%10,x/=10;
	return dfs(l,0,1,1);
}
int main() {
	int L,R;
	scanf("%d%d",&L,&R);
	memset(dp,-1,sizeof dp);
	printf("%d\n",cal(R)-cal(L-1));
	return 0;
}
