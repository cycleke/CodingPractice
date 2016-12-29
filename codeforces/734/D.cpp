#include <cstdio>
char type[3][3];
int dis[3][3];
inline int f(const int&x) {
	if(!x) return 1;
	return x<0?0:2;
}
inline int max(const int&a,const int&b){return a<b?b:a;}
inline int abs(const int&a){return a<0?-a:a;}
int main() {
	int n,kx,ky,x,y;
	char ts[3];
	scanf("%d%d%d",&n,&kx,&ky);
	for(register int i=0,j;i^3;++i)
		for(j=0;j^3;++j)
			dis[i][j]=~0U>>1;
	while(n--) {
		scanf("%s%d%d",ts,&x,&y);
		x-=kx,y-=ky;
		if(x&&y&&x+y&&x-y) continue;
		if(max(abs(x),abs(y))<dis[f(x)][f(y)])
			dis[f(x)][f(y)]=max(abs(x),abs(y)),type[f(x)][f(y)]=*ts;
	}
	for(register int i=0,j;i^3;++i)
		for(j=0;j^3;++j) {
			if(type[i][j]=='Q') return puts("YES"),0;
			if(!(i+j&1)&&type[i][j]=='B') return puts("YES"),0;
			if((i+j&1)&&type[i][j]=='R') return puts("YES"),0;
		}
	puts("NO");
	return 0;
}
