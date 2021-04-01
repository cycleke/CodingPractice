#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 400002
struct E{int to;E*nxt;}CD[N],*cd=CD,*head[N];
int fa[N],blo,d[N],an[N];
bool mark[N],able[N];
inline void adde(int a,int b) {
	cd->to=b,cd->nxt=head[a];
	head[a]=cd++;
}
int gf(int a) {return (fa[a]^a)?fa[a]=gf(fa[a]):a;}
inline void ins(int a) {
	register E*it; register int v;
	for(it=head[a];it;it=it->nxt)
		if(able[it->to]&&(gf(a)^(v=gf(it->to))))
			--blo,fa[v]=gf(a);
}
int main() {
	register int n=geti(),m=geti(),i,a,b;
	for(i=0;i<n;++i) fa[i]=i;
	while(m--) adde(a=geti(),b=geti()),adde(b,a);
	for(i=0,m=geti();i<m;++i) able[d[i]=geti()]=0,mark[d[i]]=1;
	for(i=0;i<n;++i)
		if(!mark[i])
			++blo,able[i]=1,ins(i);
	an[m]=blo;
	for(i=m-1;~i;--i) {
		able[a=d[i]]=1;
		++blo; ins(a);
		an[i]=blo;
	}
	for(i=0;i<=m;++i) printf("%d\n",an[i]);
	return 0;
}
