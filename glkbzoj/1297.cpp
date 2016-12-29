#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int mod = 2009;
#define LL long long
struct Mat{
	int A[100][100];
	int h,l;
	Mat() {memset(A,0,sizeof(A));h = l = 0;}
	Mat operator * (const Mat& B)const{
		Mat C;
		C.h = h;C.l = B.l;
		for(int i = 1;i <= h;++i)
		for(int j = 1;j <= B.l;++j){
			int tmp = 0;
			for(int k = 1;k <= l;++k)
			tmp = (tmp + ((LL)A[i][k] * B.A[k][j])%mod)%mod;
			C.A[i][j] = tmp;
		}
		return C;
	}
};

char Can[15][15];

Mat Pow(Mat B,int n){
	Mat ans = B;
	for(int i = 1;i <= B.h;++i)
	for(int j = 1;j <= B.l;++j)
	ans.A[i][j] = (i==j);
	while(n){
		if(n&1) ans = ans * B;
		B = B * B;
		n>>=1;
	}
	return ans;
}

int main(){
	int n,tot,s,f,t;
	scanf("%d%d",&n,&t);
	for(int i = 1;i <= n;++i)scanf("%s",Can[i]+1);
	Mat B;
#define CC B.A
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= n;++j){
			int tmp = Can[i][j]-'0';
			for(int k = 1;k < tmp;++k)
			CC[(k-1)*n+i][k*n+i] = 1;
			CC[(tmp-1)*n+i][j] = 1;
		}
	}
	B.h = B.l = n * 9;
	Mat ans = Pow(B,t);
	printf("%d",ans.A[1][n]);
	return 0;
}
