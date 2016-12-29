#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int a[32][32],n;
#define swap(a,b) a^=b^=a^=b
inline int guass() {
	register int i,j,k,id;
	for(i=j=0;i<n&&j<n;++j) {
		for(id=i;id<n&&!a[id][j];++id);
		if(a[id][j]) {
			if(id^i)for(k=0;k<=n;++k)swap(a[i][k],a[id][k]);
			for(id=0;id<n;++id)
				if((id^i)&&a[id][j])for(k=i;k<=n;++k)a[id][k]^=a[i][k];
			++i;
		}
	}
	for(j=i;j<n;++j)if(a[j][n])return -1;
	return 1<<(n-i);
}
int main() {
	register int K=geti(),i,j;
	while(K--) {
		n=geti();
		memset(a,0,sizeof a);
		for(i=0;i<=n;++i)a[i][i]=1;
		for(i=0;i<n;++i)a[i][n]=geti();
		for(i=0;i<n;++i)a[i][n]^=geti();
		while(true){
			i=geti(),j=geti();
			if(!i&&!j)break;
			a[j-1][i-1]=1;
		}
		i=guass();
		if(~i) printf("%d\n",i);
		else puts("Oh,it's impossible~!!");
	}
}
