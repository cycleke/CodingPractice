#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 50005
struct D{int a,b,id;}p[N],sta[N];
bool ans[N];
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb,insign;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
#define noti(a) (a<'0'||'9'<a)
inline int geti() {
	for(insign=0;inc=getc(),noti(inc);insign|=inc=='-');
	for(ina=inc-'0';inc=getc(),!noti(inc);)ina=(ina<<3)+(ina<<1)+inc-'0';
	return insign?-ina:ina;
}
bool operator < (const D&x,const D&y) {
	return (x.a^y.a)?x.a<y.a:x.b<y.b;
}
int main() {
  	int i,top=0,n; D x;
	scanf("%d",&n);
	for(i=1;i<=n;++i) p[i]=(D){geti(),geti(),i};
	std::sort(p+1,p+n+1);
	sta[top=0].a=0x7f7f7f7f;
	for(i=1;i<=n;++i) {
		for(x=p[i];top;) {
			if(sta[top].a==x.a) --top;
			if(1<top&&(sta[top-1].b-x.b+0LL)*(sta[top].a-sta[top-1].a+0LL)<=(sta[top-1].b-sta[top].b+0LL)*(x.a-sta[top-1].a+0LL))				--top;
			else break;
		}
		sta[++top]=x;
	}
	for(i=1;i<=top;++i) ans[sta[i].id]=true;
	for(i=1;i<=n;++i) if(ans[i]) printf("%d ",i);
	return 0;
}
