#include <cstdio>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
int f[105],s[105];
int gf(int u) {
	if(f[u]==u) return u;
	int t=f[u];
	f[u]=gf(f[u]);
	s[u]+=s[t];
	return f[u];
}
int main() {
	register int w=geti(),m,i,j,v,fi,fj;
	register bool flag;
	while(w--) {
		flag=true;
		for(i=geti()+1,m=geti();~i;--i) f[i]=i,s[i]=0;
		while(0<m--) {
			fi=gf(i=geti()-1),fj=gf(j=geti()),v=geti();
			if(fi^fj) {
				f[fi]=fj,s[fi]=s[j]-s[i]-v;
			} else if(s[j]-s[i]!=v) {flag=false;break;}
		}
		while(0<m--) geti(),geti(),geti();
		puts(flag?"true":"false");
	}return 0;
}
