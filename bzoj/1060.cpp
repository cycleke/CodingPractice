#include <cstdio>
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while(inc=getc(),inc<'0');ina=inc-'0';
	while(inc=getc(),'-'<inc)ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
#define N 500002
struct E{int to,w; E*nxt;}CD[N<<1],*cd=CD,*head[N];
#define adde(a,b,c){							\
		cd->to=b,cd->w=c,cd->nxt=head[a];		\
		head[a]=cd++;							\
	}
long long d[N],__t,ans;
#define cmax(a,b) (a<(__t=(b))?a=__t:1)
void cal(const int&u,const int&f) {
	E *it;
	for(it=head[u];it;it=it->nxt)
		if(it->to^f) {cal(it->to,u);cmax(d[u],d[it->to]+it->w);}
	for(it=head[u];it;it=it->nxt)
		if(it->to^f) ans+=d[u]-d[it->to]-it->w;
}
int main() {
	int n,i,s,a,b,c;
	n=geti(),s=geti();
	for(i=1;i<n;++i) {
		a=geti(),b=geti(),c=geti();
		adde(a,b,c);adde(b,a,c);
	}cal(s,0);
	return printf("%lld\n",ans),0;
}
