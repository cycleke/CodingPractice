#include <cstdio>
#include <cstring>
const int mo=20110520,N=102,P=54321,M=200000;
int n,m,mp[N][N],now,pre,f[2][M],hash[2][M],tot[2],hd[P],nt[M],bin[N];
inline void init() {
	int i,j; char ch;
	scanf("%d%d",&n,&m);
	if(n<m) {
		for(i=1;i<=n;++i)
			for(j=1;j<=m;mp[j++][i]=ch=='_')
				while(ch=getchar(),(ch^'_')&&(ch^'*'));
		n^=m^=n^=m;
	} else for(i=1;i<=n;++i)
			   for(j=1;j<=m;mp[i][j++]=ch=='_')
				   while(ch=getchar(),(ch^'_')&&(ch^'*'));
}
inline void add(int s,int value) {
	static int i,x;
	for(i=hd[x=s%P];i;i=nt[i])
		if(!(hash[now][i]^s)) {
			f[now][i]=(f[now][i]+value)%mo;
			return;
		}
	f[now][++tot[now]]=value;
	hash[now][tot[now]]=s;
	nt[tot[now]]=hd[x];
	hd[x]=tot[now];
}
inline void work() {
	register int i,j,k,p,q,s,value;
	tot[now]=1; hash[now][1]=0;
	f[now][1]=1;
	for(i=0;i<N;++i)bin[i]=i<<1;
	for(i=1;i<=n;++i) {
		for(j=1;j<=tot[now];++j)hash[now][j]=(hash[now][j]<<2)&((1<<bin[m+1])-1);
		for(j=1;j<=m;++j) {
			pre=now; now^=1;
			memset(hd,0,sizeof hd);
			memset(f[now],0,sizeof f[now]);
			tot[now]=0;
			for(k=1;k<=tot[pre];++k)
				if(f[pre][k]) {
					s=hash[pre][k];
					value=f[pre][k];
					p=(s>>bin[j-1])&3;
					q=(s>>bin[j])&3;
					if(!mp[i][j]) (!p&&!q)?add(s,value),0:0;
					else if(!p&&!q) {
						if(mp[i+1][j]) add(s|(1<<bin[j-1]),value);
						if(mp[i][j+1]) add(s|(1<<bin[j]),value);
						if(mp[i+1][j]&&mp[i][j+1]) add(s|(2<<bin[j-1])|(2<<bin[j]),value);
					} else if(!p) {
						s^=(1<<bin[j])*q;
						if(q&1) {
							if(mp[i+1][j]) add(s|(1<<bin[j-1]),value);
							if(mp[i][j+1]) add(s|(2<<bin[j]),value);
						} else {
							add(s,value);
							if(mp[i+1][j]) add(s|(2<<bin[j-1]),value);
						}
					} else if(!q) {
						s^=(1<<bin[j-1])*p;
						if(p&1) {
							if(mp[i+1][j]) add(s|(2<<bin[j-1]),value);
							if(mp[i][j+1]) add(s|(1<<bin[j]),value);
						} else {
							add(s,value);
							if(mp[i][j+1]) add(s|(2<<bin[j]),value);
						}
					} else if((p&1)&&(q&1)) add(s^((1<<bin[j-1])|(1<<bin[j])),value);
				}
		}
	}
}
int main() {
	init(); work();
	printf("%d\n",f[now][1]);
	return 0;
}
