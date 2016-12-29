#include<cstdio>
#include<cstring>
#define lowbit(u) ((u)&-(u))
#define maxs 1025

int C[maxs][maxs];
int s,k;

void update(const int& x,const int& y,const int& add){
	for(int i = x;i <= s;i+=lowbit(i))
		for(int j = y;j <= s;j+=lowbit(j))
		C[i][j]+=add;
}

int query(const int& x,const int& y){
	int sum(0);
	for(int i = x;i;i-=lowbit(i))
		for(int j = y;j;j-=lowbit(j))
		sum+=C[i][j];
	return sum;
}

int main(){
	
	scanf("%d%d",&k,&s);
	int x,y,a,b;
	while(scanf("%d",&k)&&k<3){
		if(k==1){
			scanf("%d%d%d",&x,&y,&a);
			++x,++y;
			update(x,y,a);
		}else{
			scanf("%d%d%d%d",&x,&y,&a,&b);
			++a,++b;
			printf("%d\n",query(a,b)-query(x,b)-query(a,y)+query(x,y));
		}
	}
	
	
	return 0;
}
