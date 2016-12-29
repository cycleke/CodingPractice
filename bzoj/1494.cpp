#include <cstdio>
#include <cstring>

const unsigned int mo=65521;
typedef unsigned int ui;
typedef ui mat[53][53];
inline ui qp(ui a,ui b){ui r=1;for(;b;b>>=1,a=a*a%mo)if(b&1)r=r*a%mo;return r;}
inline void cmax(int&a,const int&b){if(a<b)a=b;}

int ct,k,dig[5],cnt[5],mp[43211],st[53][5];
long long n; mat a,b;
ui f[53];
inline int mul(mat&x,mat&y) {
	static mat c;
	register int i,j,k;
	for(i=0;i<ct;++i)
		for(j=0;j<ct;++j) {
			c[i][j]=0;
			for(k=0;k<ct;++k)
				for(c[i][j]+=x[i][k]*y[k][j]%mo;c[i][j]>=mo;c[i][j]-=mo);
		}
	for(i=0;i<ct;++i)for(j=0;j<ct;++j)x[i][j]=c[i][j];
}
inline void expand(int x) {
	static int i,t;
	mp[x]=-1;
	for(i=0,t=x;i<k;++i)
		if((dig[i]=t%10)>=k) return;
		else t/=10;
	for(i=0,t=-1;i<k;++i)
		if(dig[i]>t+1) return;
		else cmax(t,dig[i]);
	memset(cnt,0,sizeof cnt);
	mp[x]=ct;
	for(i=0;i<k;++i)
		st[ct][i]=dig[i],++cnt[dig[i]];
	t=1;
	for(i=0;i<k;++i)
		if(cnt[i]>1) t=(ui)t*qp(cnt[i],cnt[i]-2)%mo;
	f[ct++]=t;
}
int col[5],ora[5];
inline void buildmat(int x) {
	int*p=st[x];
	static int i,j,t;
	bool flag=true;
	for(i=1,t=0;i<k;++i)cmax(t,p[i]),flag&=(p[i]^*p);
	int ennum=1<<t+1,mark,tmp,now;
	ui C,cc;
	for(i=0;i<ennum;++i) {
		if(flag && !(i&1))  continue;
		mark=-1;
		for(j=0;j<k;++j)col[j]=j;
		for(j=0;j<=t;++j) if(i>>j&1)(~mark)?col[j]=mark:mark=j;
		memset(ora,-1,sizeof ora);
		tmp=-1;
		for(j=1;j<k;++j)
			dig[j-1]=(~ora[col[p[j]]])?ora[col[p[j]]]:(ora[col[p[j]]]=++tmp);
		dig[k-1]=(~(mark)&&(~ora[mark]))?ora[mark]:++tmp;
		now=dig[k-1];
		for(j=k-2;~j;--j)now=(now<<3)+(now<<1)+dig[j];
		if(mp[now]<0) continue;
		C=1;
		if(~mark)for(j=0;j<k;++j)
					 if(col[j]==mark) {
						 cc=0;
						 for(tmp=0;tmp<k;++tmp)
							 cc+=p[tmp]==j;
						 C=C*cc%mo;
					 }
		b[x][mp[now]]=C;
	}
}
int main() {
	scanf("%d%lld",&k,&n);
	if(k>=n) return printf("%u\n",qp(n,n-2)),0;
	int t=0,i;
	for(i=k-1;~i;--i)t=(t<<3)+(t<<1)+i;
	for(i=0;i<=t;++i)expand(i);
	for(i=0,n-=k;i<ct;++i)buildmat(i);
	for(i=0;i<ct;++i)a[i][i]=1;
	for(;n;n>>=1,mul(b,b))if(n&1)mul(a,b);
	ui ans=0;
	for(i=0;i<ct;++i)
		for(ans+=f[i]*a[i][0]%mo;ans>=mo;ans-=mo);
	printf("%u\n",ans);
	return 0;
}
