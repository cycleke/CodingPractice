#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int dp[102],c[102][102],vis[102],d[21];
struct E{int to,v;E*nxt;}CD[100*100+2],*cd=CD,*head[102];
inline void cmin(int&a,int b){b<a?a=b:1;}
#define pr pair<int,int>
priority_queue< pr, vector< pr >,greater < pr > >heap;
inline int dijstra(int sta,int t) {
	memset(d,127,sizeof d);
	while(!heap.empty()) heap.pop();
	heap.push(make_pair(*d=0,0));
	register int s,dis; E*it;
	while(!heap.empty()) {
		s=heap.top().second,dis=heap.top().first; heap.pop();
		if(dis^d[s]) continue;
		for(it=head[s];it;it=it->nxt)
			if(!((sta>>it->to)&1)&&dis+it->v<d[it->to])
				heap.push(make_pair(d[it->to]=dis+it->v,it->to));
	}
	return (d[t]^0x7f7f7f7f)?d[t]:-1;
}
int main() {
	register int n=geti(),m=geti(),k=geti(),e=geti(),i,j,x;
	while(e--) {
		i=geti()-1,j=geti()-1,x=geti();
		cd->v=x,cd->to=j,cd->nxt=head[i],head[i]=cd++;
		cd->v=x,cd->to=i,cd->nxt=head[j],head[j]=cd++;
	}
	for(e=geti();e;--e) {
		x=geti()-1,i=geti(),j=geti();
		for(;i<=j;++i)vis[i]|=1<<x;
	}
	memset(c,-1,sizeof c);
	for(i=1;i<=n;++i) {
		x=vis[i];
		c[i][i]=dijstra(x,m-1);
		for(j=i+1;j<=n;++j) {
			if((x|vis[j])<=x){c[i][j]=c[i][j-1];continue;}
			if((c[i][j]=dijstra(x|=vis[j],m-1))<0) break;
		}
	}
	dp[0]=0,dp[1]=c[1][1];
	for(i=2;i<=n;++i) {
		dp[i]=(~c[1][i])?(c[1][i]*i):0x7f7f7f7f;
		for(j=i;j;--j)
			if(~c[j][i])cmin(dp[i],dp[j-1]+k+(i-j+1)*c[j][i]);
			else break;
	}
	printf("%d\n",dp[n]);
	return 0;
}
