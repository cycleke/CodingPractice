#include <cstdio>
#define mo 10007
#define M 6000
#define SIZE 26
class ac_dfa {
protected:
	int ch[SIZE][M],fail[M],totnode,dp[2][M];
	bool flag[M];
public:
	void insert(char *s) {
		int u=0,idx;
		while(*s) {
			idx=*s++-'A';
			if(!ch[idx][u]) ch[idx][u]=++totnode;
			u=ch[idx][u];
		}
		flag[u]=true;
	}
	void make_fail() {
		int *l=dp[0],*r=dp[0],i,f,x;
		*r++=0;
		while(l<r)
			for(flag[x=*l++]|=flag[fail[x]],i=0;i<26;++i)
				if(ch[i][x]) *r++=ch[i][x],fail[ch[i][x]]=x?ch[i][fail[x]]:0;
				else ch[i][x]=x?ch[i][fail[x]]:0;
	}
	inline void add(int&a,int b){for(a+=b;a>=mo;a-=mo);}
	int cal(int l) {
		int i,j,idx=0,p;
		for(p=1,i=0;i<l;++i)p=p*26%mo;
		for(i=1;i<=totnode;++i)dp[0][i]=0;
		dp[0][0]=1;
		for(;l;--l,idx^=1)
			for(i=0;i<=totnode;++i)
				if(!flag[i]&&dp[idx][i]) {
					for(j=0;j<26;++j)
						add(dp[idx^1][ch[j][i]],dp[idx][i]);
					dp[idx][i]=0;
				}
		int ans=0;
		for(i=0;i<=totnode;++i)
			if(!flag[i])add(ans,dp[idx][i]);
		return ((p-ans)%mo+mo)%mo;
	}
}work;
char s[105];
int main() {
	freopen("1030.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	while(n--) {scanf("%s",s);work.insert(s);}
	work.make_fail();
	printf("%d\n",work.cal(m));
	return 0;
}
