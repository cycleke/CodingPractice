#include <cstdio>
#include <cstring>
inline int rd() {
	register char c;
	while(c=getchar(),c<'0');
	return c-'0';
}
char mp[22][22];
#define M 100000
int to[M],nt[M],C[M],hd[810],te;
#define adde(a,b,c) (to[te]=b,nt[te]=hd[a],C[te]=c,hd[a]=te++)
int d[810],dt[810],la[810],S,T,r,c,d2,hx[810],hy[810];
inline bool rid(int dx,int dy){return dx*dx+dy*dy<=d2;}
int dfs(int u,int flow) {
	if(u==T||!flow) return flow;
	int r=0,t;
	for(int&i=la[u];~i;i=nt[i])
		if(d[u]==d[to[i]]+1&&C[i]>0) {
			t=dfs(to[i],flow<C[i]?flow:C[i]);
			r+=t,flow-=t;
			C[i]-=t,C[i^1]+=t;
			if(!flow||d[S]>T+1)return r;
		}
	la[u]=hd[u];
	if(!(--dt[d[u]])) d[S]=T+2;
	++dt[++d[u]]; return r;
}
inline int SAP() {
	register int *l=dt,*r=dt,i;
	*r++=T; d[T]=1;
	while(l<r) {
		for(i=hd[*l];~i;i=nt[i])
			if(!d[to[i]]) d[*r++=to[i]]=d[*l]+1;
		++l;
	}
	memset(dt,0,sizeof dt);
	for(i=S;i<=T;++i)++dt[d[i]],la[i]=hd[i];
	i=0;
	while(d[S]<T+2)i+=dfs(S,0x7f7f7f7f);
	return i;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1066.in","r",stdin);
#endif
	int d;
	scanf("%d%d%d",&r,&c,&d);
	d2=d*d;
	memset(hd,-1,sizeof hd);
	register int i,j,k,cnt=0,tp=0;
	for(i=0;i<r;++i)
		for(j=0;j<c;++j)
			if(k=rd()) {
				++tp; hx[tp]=i,hy[tp]=j;
				adde(tp,tp+1,k);adde(tp+1,tp,0);
				++tp;
			}
	for(i=0;i<r;++i) {
		scanf("%s",mp[i]);
		for(j=0;j<c;++j)cnt+=mp[i][j]=='L';
	}
	S=0,T=tp+1;
	for(i=1;i<tp;i+=2) {
		for(j=i+2;j<tp;j+=2)
			if(rid(hx[i]-hx[j],hy[i]-hy[j])) {
				adde(i+1,j,cnt),adde(j,i+1,0);
				adde(j+1,i,cnt),adde(i,j+1,0);
			}
		if(mp[hx[i]][hy[i]]=='L')adde(S,i,1),adde(i,S,0);
		if(hx[i]<d||hy[i]<d||r-hx[i]<=d||c-hy[i]<=d)adde(i+1,T,cnt),adde(T,i+1,0);
	}
	printf("%d\n",cnt-SAP());
	return 0;
}
