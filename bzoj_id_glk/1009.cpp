#include <cstdio>
int n,m,mod,a[25][25],b[25][25],c[25][25],nxt[25];
char s[25];

inline void mul(int x[25][25],int y[25][25]) {
	int i,j,k;
	for(i=0;i<m;++i)
		for(j=0;j<m;++j) {
			c[i][j]=0;
			for(k=0;k<m;++k)
			  c[i][j]=(c[i][j]+x[i][k]*y[k][j])%mod;
		}
	for(i=0;i<m;++i)
	  for(j=0;j<m;++j)
		x[i][j]=c[i][j];
}

int main() {
	int i,j=0,t;
	for(scanf("%d%d%d%s",&n,&m,&mod,s+1),i=2;i<=m;++i) {
		while(j&&s[j+1]!=s[i])j=nxt[j];
		nxt[i]=((s[j+1]==s[i])?(++j):(j));
	}
	for(i=0;i<m;++i)
	  for(j=0;j<10;++j) {
		for(t=i;t&&s[t+1]!=j+'0';t=nxt[t]);
		if(((s[t+1]==j+'0')?++t:t)^m) (++b[t][i]<mod)?1:b[t][i]=0;
	  }
	for(i=0;i<m;++i) a[i][i]=1;
	while(n) {
		if(n&1) mul(a,b);
		mul(b,b);
		n>>=1;
	}
	int ans=0;
	for(i=0;i<m;++i) (ans+=a[i][0])<mod?1:ans-=mod;
	printf("%d\n",ans);
	return 0;
}
