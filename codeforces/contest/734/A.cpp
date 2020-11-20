#include <cstdio>
int main() {
	int n,cnta=0,cntd;
	scanf("%d\n",&n);
	char ch;
	while(ch=getchar(),ch<'A');
	cnta+=ch=='A';
	while(ch=getchar(),ch>='A')cnta+=ch=='A';
	cntd=n-cnta;
	if(cnta^cntd) puts(cnta<cntd?"Danik":"Anton");
	else puts("Friendship");
	return 0;
}
