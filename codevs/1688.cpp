#include<cstdio>
#include<iostream>
using namespace std;

int cnt[100010];
int C[100010];

void update(int a){
	while(a<=100000){
		++C[a];
		a+=a&-a;
	}
}

long long sum(int a){
	long long ans(0);
	while(a>0){
		ans+=C[a];
		a-=a&-a;
	}
	return ans;
}

int main(){
	int n;
	scanf("%d",&n);
	int a;
	long long ans(0);
	for(int i = 0;i < n;++i){
		scanf("%d",&a);
		ans+=i-sum(a);
		update(a);
	}
	printf("%lld",ans);
	return 0;
}
