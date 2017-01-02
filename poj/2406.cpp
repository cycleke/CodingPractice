#include <cstdio>
int nxt[1000000];
char s[1000000];
int main() {
	register int i,j,len;
	while(scanf("%s",s+1)^EOF) {
		if(s[1]=='.') break;
		for(i=2,j=0,len=1;s[i];++i,++len) {
			while(j&&(s[j+1]^s[i]))j=nxt[j];
			(s[j+1]^s[i])?0:++j;
			nxt[i]=j;
		}
		if(len%(len-nxt[len]))puts("1");
		else printf("%d\n",len/(len-nxt[len]));
	}return 0;
}
