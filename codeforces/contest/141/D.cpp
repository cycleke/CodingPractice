#include <bits/stdc++.h>
using namespace std;
typedef pair<long long,long long>pii;
priority_queue< pii, vector< pii >, greater < pii > >heap;
const int N=400000+10;
int to[N<<1],nxt[N<<1],w[N<<1],tote,head[N],id[N<<1];
int from[N],fid[N],ST[N<<1],dis[N];
int X[N],D[N],T[N],P[N],mp[N<<1];
int main() {
	int n,i,j,L,cnt=0;
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&L);
	mp[cnt++]=0,mp[cnt++]=L;
	for(i=1;i<=n;++i) {
		scanf("%d%d%d%d",X+i,D+i,T+i,P+i);
		if(X[i]>=P[i])mp[cnt++]=(X[i]-P[i]);
		mp[cnt++]=X[i]+D[i],mp[cnt++]=X[i];
	}sort(mp,mp+cnt);
	cnt=unique(mp,mp+cnt)-mp;
	for(i=1;i<=n;++i) {
		if(X[i]<P[i]||D[i]<=T[i]) continue;
		int f=lower_bound(mp,mp+cnt,X[i]-P[i])-mp,e=lower_bound(mp,mp+cnt,X[i]+D[i])-mp;
		to[tote]=e,nxt[tote]=head[f],w[tote]=T[i]+P[i],id[tote]=i,head[f]=tote++;
	}
	for(i=0,j=cnt-1;i<j;++i) {
		to[tote]=i+1;nxt[tote]=head[i];
		w[tote]=mp[i+1]-mp[i],id[tote]=0;
		head[i]=tote++;
		to[tote]=i;nxt[tote]=head[i+1];
		w[tote]=mp[i+1]-mp[i],id[tote]=0;
		head[i+1]=tote++;
		dis[i]=L;
	}dis[j]=L;
	heap.push(make_pair(dis[0]=0,0));
	while(!heap.empty()) {
		int u=heap.top().second,d=heap.top().first,v; heap.pop();
		if(dis[u]^d) continue;
		for(int it=head[u];~it;it=nxt[it])
		  if(dis[v=to[it]]>d+w[it]) {
			  from[v]=u; fid[v]=id[it];
			  heap.push(make_pair(dis[v]=d+w[it],v));
		  }
	}
	printf("%d\n",dis[j]);
	int usp=0;
	for(i=j;i;i=from[i]) if(fid[i]) ST[usp++]=fid[i];
	printf("%d\n",usp);
	for(i=usp-1;~i;--i) printf("%d ",ST[i]);
	return 0;
}
