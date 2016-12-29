#include <cstdio>
#include <cstring>

const int mo=65521;
typedef int mat[55][55],sta[5];
inline int qp(int a,int b){int r=1;for(;b;b>>=1,a=a*a%mo)if(b&1)r=r*a%mo;return r;}
inline void cmin(int&a,const int&b){if(b<a)a=b;}
inline void cmax(int&a,const int&b){if(a<b)a=b;}

int ct,k; long long n;
mat a,b;
inline int mul(mat&x,mat&y) {
	static mat c;
	register int i,j,k;
	for(i=0;i<ct;++i)
		for(j=0;j<ct;++j) {
			c[i][j]=0;
			for(k=0;k<ct;++k)
				for(c[i][j]+=x[i][k]*y[k][j]%mo;c[i][j]>=mo;c[i][j]-=mo);
		}
	for(i=0;i<ct;++i)for(j=0;j<ct;++j)x[i][j]=c[i][j];
}
int main() {
	scanf("%lld%d",&n,&k);
	
	return 0;
}
