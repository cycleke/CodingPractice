#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 400005
int f[N],blo,d[N],ANS[N];
bool mark[N],can[N];
inline int gf(int u){
	register int en;
	for(en=u;f[en]^en;en=f[en]);
	for(register int t;u^en;t=f[u],f[u]=en,u=t);
	return en;
}

struct E{int to;E*nt;}CD[N],*cd=CD,*hd[N];
#define adde(a,b) (cd->to=b,cd->nt=hd[a],hd[a]=cd++)
inline void ins(int u) {
	register int v;
	for(register E*it=hd[u];it;it=it->nt)
		if(can[it->to]&&(gf(u)^(v=gf(it->to))))
			--blo,f[v]=gf(u);
}
int main() {
	register int n=geti(),m=geti(),i,a,b;
	for(i=0;i<n;++i)f[i]=i;
	while(m--){a=geti(),b=geti();adde(a,b),adde(b,a);}
	register int*ans,*t=d;
	for(i=0,m=geti();i<m;++i)mark[*t++=geti()]=1;
	for(i=0;i<n;++i)
		if(!mark[i])++blo,can[i]=1,ins(i);
	ans=ANS+m;
	*ans--=blo;
	for(i=m;i;--i) {
		can[a=*--t]=1;
		++blo;ins(a);
		*ans--=blo;
	}
	for(i=0;i<=m;++i)printf("%d\n",*++ans);
	return 0;
}
