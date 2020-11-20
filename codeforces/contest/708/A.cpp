#include <cstdio>
char str[100005];
int main() {
	char *s=str,flag=0;
	for(gets(str);*s=='a';++s);
	for(;*s;++s) {
		if(*s=='a') break;
		--(*s),flag=1;
	}if(!flag) *(s-1)='z';
	return puts(str),0;
}
