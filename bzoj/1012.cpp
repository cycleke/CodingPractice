#include <cstdio>
#include <algorithm>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int q[200001],v[200001];
int main() {
	register int m=geti(),d=geti(),t=0,x,len=0,tp=0;
	register char c;
	while(m--) {
		while(c=getchar(),c<'A'); x=geti();
		if(c^'A')printf("%d\n",t=v[*std::lower_bound(q+1,q+tp+1,len-x+1)]);
		else {
			x=(x+t)%d; v[++len]=x;
			while(tp&&v[q[tp]]<=x)--tp;
			q[++tp]=len;
		}
	}
	return 0;
}
