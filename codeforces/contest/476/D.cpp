#include <bits/stdc++.h>
int main() {
	int n,k,a=1,b=2,c=3,d=5;
	scanf("%d%d",&n,&k);
	printf("%d\n",(6*n-1)*k);
	while(n--) {
		printf("%d %d %d %d\n",a*k,b*k,c*k,d*k);
		a+=6,b+=6,c+=6,d+=6;
	}return 0;
}
