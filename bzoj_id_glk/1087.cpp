#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define LL long long
LL f[2][90][512];
int S[512];
int cnt;
int k,n;
inline int c(int x){
	int ans(0);
	x = S[x];
	while(x){
		if(x&1)++ans;
		x>>=1;
	}
	return ans;
}

inline void dfs(int p,int s){
	if(p==n) {S[cnt++] = s;return;}
	dfs(p+1,s<<1);
	if(!(s&1)) dfs(p+1,s<<1|1);
}

inline bool cp(int x,int y){
	x = S[x];y = S[y];
	if((x&y)||(x<<1&y)||(x>>1&y)) return false;
	return true;
}

int main(){
	scanf("%d%d",&n,&k);
	if(k>(n+1)/2*(n+1)/2) {putchar('0');return 0;};
	int cur = 0;
	//for(int i = 1;i <= 10;++i) cout<<c(i)<<' ';
	f[cur][0][0] = 1;dfs(0,0);
	for(int i = 1;i <= n;++i){
		cur^=1;memset(f[cur],0,sizeof(f[cur]));
		for(int ck = 0;ck <= k;++ck)
		for(int ps = 0;ps < cnt;++ps)
		for(int cs = 0;cs < cnt;++cs){
			if(ck - c(cs)>=0&&cp(cs,ps))
			f[cur][ck][cs] += f[cur^1][ck - c(cs)][ps];
		}
	}
	LL ans(0);
	for(int i = 0;i < cnt;++i)
	ans+=f[cur][k][i];
	cout<<ans;
	return 0;
}
