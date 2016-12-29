#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long

int n,p = 1000000007;
struct Mart{
	int map[5][5];
	int h,l;
	Mart() {memset(map,0,sizeof(map));h = l = 0;}
	Mart operator  * (const Mart& B)const{
		Mart C;
		int tmp;
		C.h = h;C.l = B.l;
		for(int i = 1;i <= h;++i)
			for(int j = 1;j <= B.l;++j){
				tmp = 0;
				for(int k = 1;k <= l;++k)
				tmp = (tmp + (LL)map[i][k] * B.map[k][j] % p)%p;
				C.map[i][j] = tmp;
			}
		return C;
	}
}A,E,B;

Mart Pow(Mart Base,int x){
	Mart ans = E;
	while(x){
		if(x&1) ans = ans * Base;
		Base = Base * Base;
		x>>=1;
	}
	return ans;
}

int main(){
	int T;
	E.map[1][1] = E.map[2][2] = 1;
	B.map[2][1] = 1;
	A.map[1][2] = A.map[2][1] = A.map[2][2] = 1;
	E.h = E.l = 2;
	B.h = 2;B.l = 1;
	A.h = A.l = 2;
	Mart ans;
	while(scanf("%d",&n)!=EOF){
		if(n==1||n==2){
			puts("1");continue;
		}
		ans = Pow(A,n-1) * B;
		printf("%d\n",ans.map[2][1]);
	}
	return 0;
}
