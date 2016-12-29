#include <cstdio>
#include <algorithm>
using namespace std;
inline long long geti() {
	register long long a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define pr pair<int,long long>
pr a[1005];
long long ins[66];
int main() {
	int n=geti(),ans=0;
	for(register int i=0;i<n;++i)a[i].second=geti(),a[i].first=geti();
	sort(a,a+n);
	for(register int i=n-1,j;~i;--i) {
		for(j=65;~j;--j)
			if((a[i].second>>j)&1) {
				if(!ins[j]){ins[j]=a[i].second;break;}
				else a[i].second^=ins[j];
			}
		if(a[i].second)ans+=a[i].first;
	}
	printf("%d",ans);
	return 0;
}
