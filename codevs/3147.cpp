#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define Swap(a,b) {a = a^b;b = a^b; a = a^b;}
int A[805][805],B[805][805];
#define LL long long
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i)
	for(int j = 1;j <= n;++j){
		scanf("%d",&A[i][j]);
		A[i][j]+=A[i-1][j];
	}
	for(int i = 1;i <= n;++i)
	for(int j = 1;j <= n;++j){
		scanf("%d",&B[i][j]);
		B[i][j]+=B[i][j-1];
	}
	int a,b,c,d;
	LL sum;
	while(m--){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(a>c)Swap(a,c)
		if(b>d)Swap(b,d)
		sum = 0;
		for(int i = 1;i <= n;++i)
		sum+=((LL)A[c][i]-A[a-1][i])*((LL)B[i][d] - B[i][b-1]);
		printf("%lld\n",sum);
	}
	return 0;
}
