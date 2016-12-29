#include <cstdio>

int main() {
	int n,k,a,i,j,cnt; bool flag;
	while(scanf("%d%d",&n,&k)^EOF) {
		cnt=0;
		for(i=1;i<=n;++i) {
			scanf("%d",&a);
			cnt+=a&1;
		}
		if(n==k) {puts((cnt&1)?"Stannis":"Daenerys"); continue;}
		i=(n-k)>>1,j=(n-k+1)>>1;
		flag=true;
		if(cnt<=i) flag=false;
		else if((k&1)==0&&n-cnt<=i) flag=false;
		else if(((n-k)&1)==0) flag=((k&1)&&n-cnt<=j);
		puts(flag?"Stannis":"Daenerys");
	}
	return 0;
}
