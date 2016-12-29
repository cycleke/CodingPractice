#include <cstdio>
#include <cstring>
const int N = 1e6 + 10;
int n, nxt[N];
char s[N];

void get_nxt() {
	for(int i=1,j=nxt[1]=0;i<=n;) 
	  if(!j||s[i]==s[j]) {++i;++j;nxt[i]=j;}
	  else j=nxt[j];
}

int main() {
	int ca = 0;
	while(scanf("%d",&n)^EOF) {
		if (!n) break;
		scanf("%s", s+1);
		get_nxt();
		printf("Test case #%d\n",++ca);
		for (int i=2,k;i<=n;++i) {
			k=i-nxt[i+1]+1;
			if((k^i)&&i%k==0) printf("%d %d\n",i,i/k);
		}
		puts("");
	}
	return 0;
}
