#include <cstdio>
#include <algorithm>
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
    while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
    return ina;
}
struct E{int u,v,w;}e[10005];
int fa[305],n,m;
bool operator < (const E&a,const E&b) {return a.w<b.w;}
int find(int a) {return (a^fa[a])?fa[a]=find(fa[a]):a;}
int main() {
	int i,p,q,mx=-1,cnt=1;
	for(n=geti(),m=geti(),i=0;i<m;++i) e[i]=(E){geti(),geti(),geti()};
	std::sort(e,e+m); for(i=1;i<=n;++i) fa[i]=i;
	for(i=0;i<m&&cnt<n;++i)
		if((p=find(e[i].u))^(q=find(e[i].v))) {
			++cnt; mx=e[i].w; fa[p]=q;
		}
	return printf("%d %d",n-1,mx),0;
}
