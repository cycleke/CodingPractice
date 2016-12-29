#include <cstdio>
int a[32][32],b[32];
inline int ibs(int a){return a<0?-a:a;}
inline void swap(int&a,int&b){int t=b;b=a,a=t;}
inline void guass() {
	register int i,j,k,id;
	for(i=0;i^30;++i) {
		for(id=i;id<30&&!a[id][i];++id);
		if(id^i)for(j=0;j^31;++j)swap(a[id][j],a[i][j]);
		for(j=0;j^30;++j)
			if((i^j)&&a[j][i])for(k=0;k^31;++k)
								  a[j][k]^=a[i][k];
	}
	for(i=0;i^30;++i)
		if(a[i][30]) {
			for(j=0;(j^30)&&!a[i][j];++j);
			if(j>=30)return;
			else b[j]=a[i][30];
		}
}
int main() {
	int __,ca=0,i,j;
	scanf("%d",&__);
	while(ca++<__) {
		for(i=0;i^30;++i)scanf("%d",a[i]+30),b[i]=0;
		for(i=0;i^30;++i) {
			int x=i/6,y=i%6;
			for(j=0;j^30;++j) {
				int _x=j/6,_y=j%6;
				a[i][j]=(ibs(x-_x)+ibs(y-_y)<=1);
			}
		}
		guass();
		printf("PUZZLE #%d\n",ca);
		for(i=0;i^30;++i)printf("%d%c",b[i]," \n"[(i+1)%6==0]);
	}return 0;
}
