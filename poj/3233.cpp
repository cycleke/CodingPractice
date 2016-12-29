#include<cstdio>
#include<cstring>
#define LL long long

int n,m;

struct Mat{
	int A[32][32];
	void clean(){memset(A,0,sizeof(A));}
	void clear(){
		for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
		A[i][j] = (i==j);
	}
	Mat operator *(const Mat& B)const{
		Mat ans;
		ans.clean();
		for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
		for(int k = 1;k <= n;++k)
		ans.A[i][j] = (ans.A[i][j] + (LL)A[i][k] * B.A[k][j] % m)%m;
		return ans;
	}
	Mat operator +(const Mat& B)const{
		Mat ans;
		ans.clean();
		for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
		ans.A[i][j] = (A[i][j] + B.A[i][j])%m;
		return ans;
	}
	void Read(){
		for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
		scanf("%d",&A[i][j]);
	}
	void Write()const{
		for(int i = 1;i <= n;++i){
			for(int j = 1;j <= n;++j)
			printf("%d ",A[i][j]);
			puts("");
		}
	}
	Mat Pow(int x)const{
		Mat ans,b = *this;
		ans.clear();
		while(x){
			if(x&1) ans = ans * b;
			b = b * b;
			x>>=1;
		}
		return ans;
	}
}base,E;

Mat work(int x){
	if(x==1) return base;
	if(!x) return E;
	int i;
	for (i=0;(1<<i)<=x;i++);
	Mat ans,b;
	ans = b = base;
    for (i-=2;~i;i--)
    {
        ans = ans + ans * b;
        b=b*b;
        if ((1<<i)&x) b=b*base,ans=ans+b;       
    }
	return ans;
}
int main(){
	int k;
	scanf("%d%d%d",&n,&k,&m);
	base.Read();
	E.clear();
	work(k).Write();
	return 0;
}
