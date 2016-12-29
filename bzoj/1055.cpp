#include <cstdio>
#include <cstring>
int t[4];
char replace[4][20][2],s[202],f[202][202][4];
const char p[]={'W','I','N','G'};
inline int ps(const char&c) {
	if(c=='W') return 0;
	if(c=='I') return 1;
	if(c=='N') return 2;
	return 3;
}
bool dp(const int&l,const int&r,const int&k) {
	if(l>=r)return s[l]==p[k];
	char&rt=f[l][r][k];
	if(~rt)return rt;
	for(int i=0;i<t[k];++i)
		for(int j=l;j<r;++j)
			if(dp(l,j,ps(replace[k][i][0]))&&dp(j+1,r,ps(replace[k][i][1])))
				return rt=1;
	return rt=0;
}
int main() {
	for(int i=0;i<4;++i)scanf("%d",t+i);
	for(int i=0;i<4;++i)
		for(int j=0;j<t[i];++j)
			scanf("%s",replace[i][j]);
	scanf("%s",s);
	int le=strlen(s),ok=0;
	memset(f,-1,sizeof f);
	for(int i=0;i<4;++i)
		if(dp(0,le-1,i))ok=1,putchar(p[i]);
	if(!ok)puts("The name is wrong!");
	return 0;
}
