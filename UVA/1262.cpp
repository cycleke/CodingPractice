#include <cstdio>
#include <cstring>
int mul[6],cnt[5];
char vis[2][26],s[2][6][5],ans[6],choice[6][5];
int main() {
	int T,i,j,a,b,k;
	for(scanf("%d",&T);T;--T) {
		scanf("%d",&k); --k;
		memset(cnt,0,sizeof cnt);
		for(i=0;i<2;++i)
		  for(j=0;j<6;++j)
			scanf("%s",s[i][j]);
		for(i=0;i<5;++i) {
			memset(vis,0,sizeof vis);
			for(j=0;j<2;++j)
				for(a=0;a<6;++a)
				  vis[j][s[j][a][i]-'A']=1;
			for(j=0;j<26;++j)
			  if(vis[0][j]&&vis[1][j])
				choice[i][cnt[i]++]='A'+j;
		}
		for(i=4,mul[5]=1;~i;--i)
		  mul[i]=mul[i+1]*cnt[i];
		if(k>=mul[0]) {puts("NO");continue;}
		for(i=0;i<5;++i) {
			a=k/mul[i+1];
			ans[i]=choice[i][a];
			k%=mul[i+1];
		}
		ans[5]=0;
		puts(ans);
	}
}
