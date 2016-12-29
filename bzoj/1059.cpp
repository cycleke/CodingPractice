#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int vis[202],_clock,f[202];
struct E{int to;E*nt;}CD[40002],*cd,*hd[202];
inline void adde(int a,int b){cd->to=b,cd->nt=hd[a],hd[a]=cd++;}
bool dfs(int u) {
	for(E*it=hd[u];it;it=it->nt)
		if(_clock^vis[it->to]){
			vis[it->to]=_clock;
			if(!f[it->to]||dfs(f[it->to]))
				return f[it->to]=u;
		}
	return 0;
}
int main() {
	register int T=geti(),n,i,j;
	while(T--) {
		cd=CD; n=geti();
		for(i=1;i<=n;++i)hd[i]=NULL,f[i]=0;
		for(i=1;i<=n;++i)
			for(j=1;j<=n;++j)
				if(geti())adde(i,j);
		for(i=1;i<=n;++i)
			if(++_clock,!dfs(i))break;
		puts(i>n?"Yes":"No");
	}return 0;
}
