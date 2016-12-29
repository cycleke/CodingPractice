#include <cstdio>
#include <algorithm>
using namespace std;
#define M 200000
int q[M],num[M];
int main() {
	int m,d,len=0,tp=0,x,t=0,o,i;
	char op[3];
	for(scanf("%d%d",&m,&d);m;--m) {
		scanf("%s%d",op,&x);
		if(*op=='A') {
			x=(x+t)%d; num[++len]=x;
			while(tp&&num[q[tp]]<=x) --tp;
			q[++tp]=len;
		} else {
			o=lower_bound(q+1,q+tp+1,len-x+1)-q;
			printf("%d\n",t=num[q[o]]);
		}
	}return 0;
}
