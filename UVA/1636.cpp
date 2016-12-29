#include <cstdio>
#include <cstring>
#define N 105
char s[N];
int main() {
	int len,cnt0,cnt00,a,b,i;
	while(scanf("%s",s)^EOF) {
		len=strlen(s);
		s[len]=s[0],s[len+1]=s[1];
		cnt0=cnt00=0;
		for(i=0;i<len;++i) 
		  (s[i]=='0')?(++cnt0,cnt00+=s[i+1]=='0',1):1;
		if(cnt00*len<cnt0*cnt0) puts("ROTATE");
		else if(cnt00*len>cnt0*cnt0) puts("SHOOT");
		else puts("EQUAL");
	}
	return 0;
}
