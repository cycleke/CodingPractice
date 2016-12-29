#include <bits/stdc++.h>
using namespace std;
int cnt[10];
bool check(int i,int j,int n,int m) {
	memset(cnt,0,sizeof cnt);
	if(!n) ++(*cnt); if(!m) ++(*cnt);
	while(n) {++cnt[i%7]; i/=7,n/=7;}
	while(m) {++cnt[j%7]; j/=7,m/=7;}
	for(i=0;i<7;++i) if(cnt[i]>1) return 0;
	return 1;
}
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	if((long long)n*m > 1e7) return puts("0"),0;
	int res=0;
	for(int i=0,j;i<n;++i)
	  for(j=0;j<m;++j)
		res+=check(i,j,n-1,m-1);
	return printf("%d\n",res),0;
}
