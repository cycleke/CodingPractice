#include <cstdio>
#include <cstring>
const int Mod=1e9+7,N=405,S=3010;
int f[N][S];
bool check(int s,int l) {
	int sl=1<<l-1,sr=1;
	for (int i=1;i<=(l>>1);++i) {
		int a=s&sl,b=s&sr;
		if ((a&&(!b))||(!(a)&&b)) return false;
		sl>>=1,sr<<=1;
	}
	return true;
}

int main() {
	int T; scanf("%d",&T);
	while (T--) {
		int n, k;
		scanf("%d%d",&n,&k);
		if (k==1) {puts("0"); continue;}
		memset(f,0,sizeof f);
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i)
		  for (int j = 0, tj = 1<<k+1; j < tj; ++j)
			if (f[i-1][j]) {
				bool f1=true,f2=true;
				if(i>k&&check(j&((1<<k-1)-1),k-1)) {
					if (j&(1<<k-1)) f2 = false;
					else f1 = false;
				}
				if (i>=k&&check(j&((1<<k-2)-1),k-2)) {
					if (j&(1<<k-2)) f2 = false;
					else f1 = false;
				}
				int tmp = (j&((1<<k)-1))<<1;
				if (f1) f[i][tmp]=(f[i][tmp]+f[i-1][j])%Mod;
				tmp |= 1;
				if (f2) f[i][tmp]=(f[i][tmp]+f[i-1][j])%Mod;
			}
		int ans = 0;
		for (int i=0,ti=(1<<k+1)-1;i<=ti;++i)
		  ans=(ans+f[n][i])%Mod;
		printf("%d\n",ans);
	}
	return 0;
}
