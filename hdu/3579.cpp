#include <cstdio>
int exgcd(int a,int b,int &g,int&x,int&y) {
	if(!b) {g=a,x=1,y=0;}
	else {
		exgcd(b,a%b,g,y,x);
		y-=a/b*x;
	}
}
int a[55],b[55],n;
inline int cal() {
	int a1=*a,a2,b1=*b,b2;
	int delta,g,x,y,k,t;
	for(int i=1;i<n;++i) {
		a2=a[i],b2=b[i];
		delta=b2-b1;
		exgcd(a1,a2,g,x,y);
		if(delta%g) return -1;
		k=delta/g*x;
		t=a2/g;
		if(t<0) t=-t;
		k=(k%t+t)%t;
		b1=b1+a1*k;
		a1=a1/g*a2;
	}
	if(b1==0) b1=a1;
	return b1;
}
int main() {
	int T,i,ca=0;
	scanf("%d",&T);
	while(ca++<T) {
		scanf("%d",&n);
		for(i=0;i<n;scanf("%d",a+i++));
		for(i=0;i<n;scanf("%d",b+i++));
		printf("Case %d: %d\n",ca,cal());
	}
	return 0;
}
