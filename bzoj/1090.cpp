#include <cstdio>
#include <cstring>
char s[101]; int dp[101][101];
inline int len(const int&v) {if(v<10)return 1;return v<100?2:3;}
inline bool same(const int&l,const int&r,const int&x,const int&y) {
	//make [x..y] by [l..r]
	int l1=r-l+1,l2=y-x+1;
	if(l2<l1||l2%l1)return false;
	for(int i=x,j=l;i<=y;++i) {
		if(s[i]^s[j])return false;
		if(++j>r)j=l;
	}return true;
}
inline void cmin(int&a,const int&b){if(b<a)a=b;}
int cal(const int&l,const int&r) {
	if(dp[l][r])return dp[l][r];
	int &rt=dp[l][r]=r-l+1;
	for(int i=l;i<r;++i) {
		cmin(rt,cal(l,i)+cal(i+1,r));
		if(same(l,i,i+1,r)) cmin(rt,cal(l,i)+2+len((r-i)/(i-l+1)+1));
	}return rt;
}
int main() {
	gets(s);
	printf("%d\n",cal(0,strlen(s)-1));
	return 0;
}
