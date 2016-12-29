#include<cstdio>
#include<cstring>

int s;
int C[1010][1010];

void update(const int& x,const int& y){
	for(int i = x;i<=s;i+=i&-i)
		for(int j = y;j<=s;j+=j&-j)
		++C[i][j];
}

int sum(const int& x,const int& y){
	int ans(0);
	for(int i = x;i;i-=i&-i)
		for(int j = y;j;j-=j&-j)
		ans+=C[i][j];
	return ans;
}

int main(){
	freopen("A.in","r",stdin);
	int T;
	scanf("%d",&T);
	int k;
	int x,y,a,b;
	char ss[3];
	while(T--){
		scanf("%d%d",&s,&k);
		memset(C,0,sizeof(C));
		while(k--){
			scanf("%s",ss);
			if(ss[0]=='C'){
				scanf("%d%d%d%d",&x,&y,&a,&b);
				++a,++b;
				update(x,y);update(x,b);update(a,y);update(a,b);
			}else{
				scanf("%d%d",&x,&y);
				printf("%d\n",sum(x,y)%2);
			}
		}
		puts("");
	}
	
	return 0;
}
