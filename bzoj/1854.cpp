#include <cstdio>
inline int gi() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define M 10000
#define N 1000000
int vis[N],link[N],_vis;
struct edge{int to;edge*nt;}medge[N<<1],*hd[M],*cedge=medge;
inline void adde(int a,int b){cedge->to=b,cedge->nt=hd[a],hd[a]=cedge++;}
bool dfs(int u) {
	int v;
	for(edge*it=hd[u];it;it=it->nt)
		if(vis[v=it->to]^_vis) {
			vis[v]=_vis;
			if(!(~link[v])||dfs(link[v]))
				return link[v]=u,true;
		}return false;
}
int main() {
	register int n=gi();
	while(n--) adde(gi()-1,n),adde(gi()-1,n),link[n]=-1;
	for(n=0;n<M;++n) if(++_vis,!dfs(n))break;
	printf("%d\n",n);
	return 0;
}
