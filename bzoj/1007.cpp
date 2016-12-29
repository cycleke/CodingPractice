#include <cstdio>
#include <algorithm>
char inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins>=ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins>=ine))?EOF:*ins++)
inline int geti() {
	register int a; register char c,f=0;
	while(c=getc(),c<'0')f|=c=='-';a=c-'0';
	while(c=getc(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 50005
struct D{int a,b,id;}p[N],sta[N];
inline bool operator < (const D&x,const D&y){return (x.a^y.a)?x.a<y.a:x.b<y.b;}
bool ans[N]; char oub[N<<3],ous[10],*oue=oub;
inline void outi(int x) {
	register char tp=0;
	while(x)ous[++tp]=x%10,x/=10;
	for(;tp;--tp)*oue++=ous[tp]+'0';
	*oue++=' ';
}
int main() {
	register int n=geti(),i,tp;
	register D x;
	for(i=1;i<=n;++i){
		p[i].a=geti();
		p[i].b=geti();
		p[i].id=i;
	}
	std::sort(p+1,p+n+1);
	sta[tp=0].a=0x7f7f7f7f;
	for(i=1;i<=n;++i) {
		for(x=p[i];tp;) {
			if(sta[tp].a==x.a) --tp;
			if(1<tp&&(sta[tp-1].b-x.b+0LL)*(sta[tp].a-sta[tp-1].a+0LL)<=(sta[tp-1].b-sta[tp].b+0LL)*(x.a-sta[tp-1].a+0LL))--tp;
			else break;
		}
		sta[++tp]=x;
	}
	for(i=1;i<=tp;++i)ans[sta[i].id]=1;
	for(i=1;i<=n;++i)if(ans[i])outi(i);
	fwrite(oub,1,oue-oub,stdout);
	return 0;
}
