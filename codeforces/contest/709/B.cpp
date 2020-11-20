#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int p[100005];
int main() {
	int n,a;
	scanf("%d%d",&n,&a);
	for(int i=0;i<n;++i) scanf("%d",p+i);
	sort(p,p+n);
	if(n==1) puts("0");
	else if(a<=*p) printf("%d\n",p[n-2]-a);
	else if(a>=p[n-1]) printf("%d\n",a-p[1]);
	else {
		int t1,t2;
		if(a<p[1]) t1=p[n-1]-a;
		else t1=min(a-p[1],p[n-1]-a)*2+max(a-p[1],p[n-1]-a);
		if(a>p[n-2]) t2=a-p[0];
		else t2=min(a-p[0],p[n-2]-a)*2+max(a-p[0],p[n-2]-a);
		printf("%d\n",min(t1,t2));
	}return 0;
}
