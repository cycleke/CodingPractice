#include <cstdio>
int n,m,mo,a[25][25],b[25][25],c[25][25],nxt[25];
char s[25];
#define inc(a,b) for(a+=b;a>=mo;a-=mo)
inline void mul(int (&x)[25][25],int (&y)[25][25]) {
	register int i,j,k;
	for(i=0;i<m;++i)
		for(j=0;j<m;++j) {
			c[i][j]=0;
			for(k=0;k<m;++k)
				c[i][j]=(c[i][j]+x[i][k]*y[k][j])%mo;
		}
	for(i=0;i<m;++i)
		for(j=0;j<m;++j)
			x[i][j]=c[i][j];
}
int main() {
	register int i,j=0,t;
	for(scanf("%d%d%d%s",&n,&m,&mo,s+1),i=2;i<=m;++i) {
		while(j&&(s[j+1]^s[i]))j=nxt[j];
		nxt[i]=(s[i]==s[j+1])?(++j):j;
	}
	for(i=0;i<m;++i)
		for(j=0;j<10;++j) {
			for(t=i;t&&(s[t+1]^j+'0');t=nxt[t]);
			if(((s[t+1]==j+'0')?++t:t)^m)++b[t][i]<mo?1:b[t][i]=0;
		}
	for(i=0;i<m;++i)a[i][i]=1;
	for(;n;n>>=1,mul(b,b))if(n&1)mul(a,b);
	for(t=0,i=0;i<m;++i)inc(t,a[i][0]);
	return printf("%d\n",t),0;
}
