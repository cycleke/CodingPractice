#include <cstdio>
#include <cstring>
char s[52];
int f[2][52][52];
inline void cmin(int&a,int b){if(b<a)a=b;}
inline int min(const int&a,const int&b){return a<b?a:b;}
inline bool IsSame(const int&l,const int&r) {
	if((l&1)^(r&1)) {
		for(int i=l,j=(l+r>>1)+1;j<=r;++i,++j)
			if(s[i]^s[j]) return false;
		return true;
	}else return false;
}
int dp(const bool&k,const int&l,const int&r) {
	if(f[k][l][r]) return f[k][l][r];
	int&t=f[k][l][r];
	if(l>=r) return k?t=100:1;
	t=100;
	if(k) for(int i=l;i<r;++i) {
			cmin(t,dp(0,l,i)+dp(0,i+1,r)+1);
			cmin(t,dp(0,l,i)+dp(1,i+1,r)+1);
			cmin(t,dp(1,l,i)+dp(0,i+1,r)+1);
			cmin(t,dp(1,l,i)+dp(1,i+1,r)+1);
		}
	if(IsSame(l,r)) cmin(t,dp(0,l,(l+r)>>1)+1);
	for(int i=l;i<r;++i) cmin(t,dp(0,l,i)+r-i);
	return t;
}
int main() {
	scanf("%s",s);
	int l=strlen(s)-1;
	printf("%d\n",min(dp(0,0,l),dp(1,0,l)));
	return 0;
}
