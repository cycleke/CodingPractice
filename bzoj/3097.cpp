#include <cstdio>
char s[100001],*T=s;
#define ad(c) (*T++=c)
int main() {
	register int i,j,l,n=1;
	ad('a');
	for(i=0;i<12;++i) {
		for(j=0;j<n;++j)
			s[j]=='a'?ad('b'):ad('a');
		n<<=1;
	}
	l=n>>1;
	ad('a');++n;
	for(i=0;i<l;++i)ad('a'),++n;
	ad('b');++n;
	for(i=0;i<l;++i)ad('a'),++n;
	printf("%d %d\n",n,l);
	puts(s);
	return 0;
}
