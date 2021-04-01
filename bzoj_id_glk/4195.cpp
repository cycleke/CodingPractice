#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	for(;(inc=getc())<'0'||inc>'9';);
	for(ina=inc-'0';(inc=getc())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return ina;
}
#define N 1000005
int fa[N<<1],mp[N<<1],cnt;
int find(int a) {return (fa[a]^a)?fa[a]=find(fa[a]):a;}
inline bool Union(int a,int b) {
	a=find(a),b=find(b);
	return (a^b)?fa[a]=b:0;
}
#define find_pos(a) (lower_bound(mp,mp+cnt,a)-mp)
int X[N],Y[N],E[N];
int main() {
	int i,n; bool flag;
	for(int T=geti();T;--T) {
		n=geti(),cnt=0;
		for(i=0;i<n;++i) {
			mp[cnt++]=X[i]=geti();
			mp[cnt++]=Y[i]=geti();
			E[i]=geti();
		}sort(mp,mp+cnt);
		cnt=unique(mp,mp+cnt)-mp;
		for(i=0;i<cnt;++i) fa[i]=i;
		flag=1;
		for(i=0;i<n;++i)
			if(E[i]) Union(find_pos(X[i]),find_pos(Y[i]));
		for(i=0;i<n;++i)
			if(!E[i]) flag&=find(find_pos(X[i]))!=find(find_pos(Y[i]));
		puts(flag?"YES":"NO");
	}return 0;
}
