#include <cstdio>
#include <cstring>
char str[210],ans[210],*s=ans;
int main() {
	int i=0;
	scanf("%s",str);
	while(str[i]) 
	  if(str[i]=='W'&&str[i+1]=='U'&&str[i+2]=='B')
		i+=3;
	  else break;
	while(str[i])
	  if(str[i]=='W'&&str[i+1]=='U'&&str[i+2]=='B')
		i+=3,*s++=' ';
	  else *s++=str[i++];
	*s=0;
	return puts(ans),0;
}
