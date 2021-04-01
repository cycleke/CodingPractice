#include <cstdio>
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
#define N 1000010
int a[N],cnt[N],ans[N];
int main() {
	int i,j,n=geti(),mx=0;
	for(i=0;i<n;++i) ++cnt[a[i]=j=geti()],(mx<j)?mx=j:1;
	for(i=1,++mx;i<mx;++i)
		if(cnt[i]) for(j=i;j<mx;j+=i)
					   ans[j]+=cnt[i];
	for(i=0;i<n;++i) printf("%d\n",ans[a[i]]-1);
	return 0;
}
