#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char B[1<<16],*S,*E;
#define gc() (S==E?(E=(S=B)+fread(B,1,1<<16,stdin),*S++):*S++)
inline int gi() {
	static int a; static char c;
	while(c=gc(),c<'0');a=c-'0';
	while(c=gc(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct D{int v,i,j;}a[62505];
bool operator < (const D&a,const D&b) {return a.v<b.v;}
int Link[255],vis[255],_vis,cnt,n,m,k;
struct edge{int to;edge*nt;}ME[62505],*ce,*he[255];
inline void adde(int a,int b) {ce->to=b,ce->nt=he[a],he[a]=ce++;}
bool dfs(int u) {
	for(edge*it=he[u];it;it=it->nt)
		if(vis[it->to]^_vis) {
			vis[it->to]=_vis;
			if(!Link[it->to]||dfs(Link[it->to]))
				return Link[it->to]=u;
		}
	return false;
}
inline bool check(int md) {
	ce=ME;
	int i,count=0,val=a[md].v;
	for(i=1;i<=n;++i)he[i]=NULL;
	for(i=1;i<=m;++i)Link[i]=0;
	for(i=0;i<cnt;++i)
		if(a[i].v<=val)adde(a[i].i,a[i].j);
		else break;
	for(i=1;i<=n;++i)
		if((++_vis,count+=dfs(i))>n-k) return true;
	return false;
}
int main() {
	int i,j,l,r,md,ans;
	n=gi(),m=gi(),k=gi();
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			a[cnt++]=(D){gi(),i,j};
	sort(a,a+cnt);
	for(l=0,r=ans=cnt-1;l<=r;)
		if(check(md=l+r>>1))r=(ans=md)-1;
		else l=md+1;
	printf("%d\n",a[ans].v);
	return 0;
}
