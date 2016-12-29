#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int p[15]={1,2,3,5,7,11,13,17,19,23,29,31};
int n,a,ac;
void dfs(int k,int v,int c,int la) {
	if(k>13) {
		if(v>a&&c>ac)a=v,ac=c;
		else if(v<=a&&c>=ac)a=v,ac=c;
	}else {
		int t=1;
		for(int i=0;i<=la;++i) {
			dfs(k+1,v*t,c*(i+1),i);
			if(1LL*v*(t*=p[k])>n)break;
		}
	}
}
int main() {
	n=geti(),a=ac=1;
	dfs(1,1,1,20);
	printf("%d",a);
	return 0;
}
