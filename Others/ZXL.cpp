#include <cstdio>
#include <cstring>
const int mod=1e9+7,N=1005;
int f[N][N],g[N][N],lx,ly,L,ans,pos[26];
char x[N],y[N];
#define max(a,b) (a<b?b:a)
#define add(a,b) ((a+=b)>=mod?a-=mod:1)
int main() {
	int i,j,t;
	while(scanf("%s%s",x+1,y+1)^EOF) {
		lx=strlen(x+1),ly=strlen(y+1);
		for(i=0;i<=lx;++i) f[i][0]=0,g[i][0]=1;
		for(i=0;i<=ly;++i) f[0][i]=0,g[0][i]=1;
		for(i=1;i<=lx;++i)
			for(j=1;j<=ly;++j)
				if(x[i]^y[j]) f[i][j]=max(f[i][j-1],f[i-1][j]);
				else f[i][j]=f[i-1][j-1]+1;
		memset(pos,0,sizeof pos);
		for(j=1;j<=ly;++j) {
			pos[y[j]-'a']=j;
			for(i=1;i<=lx;++i) {
				g[i][j]=(f[i][j]==f[i-1][j]?g[i-1][j]:0);
				t=pos[x[i]-'a'];
				if(t&&f[i][j]==f[i-1][t-1]+1)
					add(g[i][j],g[i-1][t-1]);
			}
		}
		printf("%d\n",g[lx][ly]);
	}
	return 0;
}
