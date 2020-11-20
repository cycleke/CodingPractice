#include <map>
#include <cstdio>
using namespace std;
char str[1000005];
map<int,int>mp;
#define IMP return puts("Impossible"),0
int main() {
	int a,b,c,d,ma,md,i,j,k;
	for(i=1,j=0,a=1e9+10;j<a;j+=i++) mp[j]=i;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(!(a|b|c|d)) return puts("0"),0;
	ma=mp[a],md=mp[d];
	if(!(a|b|c)&&md) for(i=0;i<md;++i) str[i]='1';
	else if(!(b|c|d)&&ma) for(i=0;i<ma;++i) str[i]='0';
	else if(!ma||!md) IMP;
	else if((b+c)^(ma*md)) IMP;
	else {
		for(i=0,j=ma+md;i<j;++i) str[i]='0';
		for(i=b/md,j=i+md;i<j;++i) str[i]='1';
		str[j]='1',str[j-b%md]='0',str[ma+md]=0;
	}
	return puts(str),0;
}
