#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define lowbit(u) (u&-u)
#define maxn 1000010
#define LL long long

struct data{
	int v,w;
}A[maxn];

LL C[maxn];
int a[maxn];
int n;
int id(1);

LL sum(int x){
	LL ans(0);
	while(x>0){
		ans+=C[x];
		x-=lowbit(x);
	}
	return ans;
}

void update(int x){
	while(x<=id){
		++C[x];
		x+=lowbit(x);
	}
}

bool cmp(const data& a,const data& b){
	return a.w > b.w;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;++i){
		scanf("%d",&A[i].w);
		A[i].v = i;
	}
	sort(A+1,A+n+1,cmp);
	
	a[A[1].v]=1;
	for(int i = 2;i<=n;++i){
		a[A[i].v]=(A[i-1].w==A[i].w)?id:(++id);
	}
	LL ans(0);
	for(int i = 1;i<=n;++i){
		ans+=sum(a[i]-1);
		update(a[i]);
	}
	cout<<ans;
	
	return 0;
}
