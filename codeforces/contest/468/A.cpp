#include <cstdio>
int main() {
	int n,i;
	scanf("%d",&n);
	if(n<4) return puts("NO"),0;
	puts("YES");
	if(n&1) puts("3 + 4 = 7\n7 + 5 = 12\n 12 * 2 = 24\n24 * 1 = 24");
	else puts("1 * 2 = 2\n2 * 3 = 6\n6 * 4 = 24");
	for(i=n;5<i;i-=2) printf("%d - %d = 1\n24 * 1 = 24\n",i,i-1);
	return 0;
}
