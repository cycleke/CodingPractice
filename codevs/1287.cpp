#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
struct Mart{
	LL map[205][205];
	int h,l;
	Mart() {memset(map,0,sizeof(map));h = l = 0;}
	Mart operator  * (const Mart& B)const{
		Mart C;
		C.h = h;C.l = B.l;
		for(int i = 1;i <= h;++i)
			for(int j = 1;j <= B.l;++j)
				for(int k = 1;k <= l;++k)
				C.map[i][j] += map[i][k] * B.map[k][j];
		return C;
	}
	void Write()const{
		for(int i = 1;i <= h;++i){
			for(int j = 1;j <= l;++j)
			printf("%lld ",map[i][j]);
			puts("");
		}
	}
	void Read(){
		scanf("%d%d",&h,&l);
		memset(map,0,sizeof(map));
		for(int i = 1;i <= h;++i){
			for(int j = 1;j <= l;++j)
			scanf("%lld",&map[i][j]);
		}
	}
};

int main(){
	Mart A,B;
	A.Read();B.Read();
	(A * B).Write();
}
