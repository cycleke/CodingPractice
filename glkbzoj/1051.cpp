#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define N 10005
#define M 50005
int head[N],to[M],nxt[M],tote,dfs_clock,n;
int bcnt,siz[N],out[N],Stack[N],tp,bel[N],pre[N];
int tarjan(int u){
	int low=pre[u]=++dfs_clock;Stack[++tp]=u;
	for(int i=head[u];~i;i=nxt[i])
	  if(!pre[to[i]]) low=min(tarjan(to[i]),low);
	  else if(!bel[to[i]]) low=min(low,pre[to[i]]);
	if(low==pre[u]) {
		++bcnt; int v;
		while(true) {
			v=Stack[tp--];
			bel[v]=bcnt;
			++siz[bcnt];
			if(v==u) break;
		}
	}return low;
}
int cal() {
	int ret=0,i,j;
	for(i=1;i<=n;++i)
	  for(j=head[i];~j;j=nxt[j])
		if(bel[i]^bel[to[j]])
		  ++out[bel[i]];
	for(i=1;i<=bcnt;++i)
	  if(!out[i]) {
		  if(ret) return 0;
		  ret=siz[i];
	  }return ret;
}
int main() {
	int m,i,j,a,b;
	for(memset(head,-1,sizeof head),scanf("%d%d",&n,&m);m;--m){
		scanf("%d%d",&a,&b);
		to[tote]=b,nxt[tote]=head[a],head[a]=tote++;
	}for(i=1;i<=n;++i) (!pre[i])?tarjan(i):1;
	return printf("%d\n",cal()),0;
}
