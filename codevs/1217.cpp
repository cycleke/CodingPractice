#include<cstdio>
#include<iostream>
#include<cstring>
#define cint const int&
#define maxn 1000010
using namespace std;
inline int read(int& a){
	a = 0;
	char s = getchar();
	while(s < '0' || s > '9') s = getchar();
	while(s >='0' && s <= '9') a = a*10 + s - '0',s = getchar();
	return a;
}

int a[maxn],r[maxn],d[maxn],s[maxn],t[maxn];

bool check(cint n){
	int ma(0),mi(1e7);
	memset(a,0,sizeof(a));
	for(int i = 1;i <= n;++i){
		a[s[i]]+=d[i],a[t[i]+1]-=d[i];
		ma = max(ma,t[i]+1),mi = min(mi,s[i]);
	}
	int sum(0);
	for(int i = mi;i <= ma;++i){
		sum+=a[i];
		if(sum>r[i]) return false;
	}
	return true;
}

int main(){
	int n,m;
	read(n),read(m);
	for(int i = 1;i <= n;++i) read(r[i]);
	for(int i = 1;i <= m;++i) read(d[i]),read(s[i]),read(t[i]);
	int l = 1,r = m,mid;
	int ans(0);
	while(l <= r){
		mid = (l + r)>>1;
		if(!check(mid)){
			ans = mid;
			r = mid - 1;
		}else l = mid + 1;
	}
	if(ans){
		puts("-1");
		printf("%d",ans);
	}else putchar('0');
	return 0;
}
