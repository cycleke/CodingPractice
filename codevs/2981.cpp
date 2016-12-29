#include<cstdio>
#include<iostream>
#define swap(a,b) {a = a^b; b = a^b; a = a^b;}
#define cint const int&
#define maxn 1000005
#define lowbit(a) ((a)&(-(a)))

int a[maxn];
int c[maxn];
int n,m;

int sum(int u){
	int ans(0);
	while(u > 0){
		ans+=c[u];
		u-=lowbit(u);
	}
	return ans;
}

void update(int u,cint add){
	while(u <= 1000000){
		c[u]+=add;
		u +=lowbit(u);
	}
}

int main(){
	
	scanf("%d",&n);
	int x;
	char s[55];
	for(int i = 0;i < n;++i){
		scanf("%d%s",&x,s);
		a[x] = 1;
	}
	for(int i=1;i<=1000000;i++)
	{
		for(int j=i;j>=i-(i&(-i))+1;j--)
		c[i]+=a[j];
	}
	scanf("%d",&m);
	int y,z;
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		if(x > y) swap(x,y);
		if(z>0){
			for(int j=y+z;j>=x+z;j--){
				update(j,a[j-z]-a[j]);
				a[j]=a[j-z];
			}
			for(int j=x;j<x+z;j++){
				update(j,0-a[j]);
				a[j]=0;
			}
		}
		else if(z<0){
			z=-z;
			for(int j=x-z;j<=y-z;j++){
				update(j,a[j+z]-a[j]);
				a[j]=a[j+z];
			}
			for(int j=y+z;j>y;j--){
				update(j,0-a[j]);
				a[j]=0;
			}
		}
	}

	int k;
	scanf("%d",&k);
	while(k--){
		scanf("%d%d",&x,&y);
		printf("%d\n",sum(y) - sum(x-1));
	}

	return 0;
}

