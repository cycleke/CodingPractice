#include <cstdio>
int exgcd(int a,int b,int &g,int&x,int&y) {
	if(!b) {g=a,x=1,y=0;}
	else {
		exgcd(b,a%b,g,y,x);
		y-=a/b*x;
	}
}
int a[10],b[10],n,m;
inline int cal() {
	int a1=*a,a2,b1=*b,b2;
	int delta,g,x,y,k,t;
	for(int i=1;i<m;++i) {
		a2=a[i],b2=b[i];
		delta=b2-b1;
		exgcd(a1,a2,g,x,y);
		if(delta%g) return 0;
		k=delta/g*x;
		t=a2/g;
		if(t<0) t=-t;
		k=(k%t+t)%t;
		b1=b1+a1*k;
		a1=a1/g*a2;
	}
	if(b1==0) b1=a1;
	if(b1>n) return 0;
	return (n-b1)/a1+1;
}
int main() {
	int T,i;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(i=0;i<m;scanf("%d",a+i++));
		for(i=0;i<m;scanf("%d",b+i++));
		printf("%d\n",cal());
	}
	return 0;
}
