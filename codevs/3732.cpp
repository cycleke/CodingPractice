#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define LL long long
using namespace std;
char ss[10010];
const LL P[2]={38833,(LL)998244353}; 
char *per;
int A[110][2];
int ans[1000005],first[1000005],second[1000005];

int main(){
	int n,m;
	bool sign;
	LL t;
	scanf("%d%d",&n,&m);
	for(int i = 0;i <= n;++i){
		sign = 0;
		memset(ss,0,sizeof(ss));
		scanf("%s",ss);
		per = ss;
		if(*ss=='-')sign = 1,++per;
		int &a = A[i][0],&b = A[i][1];
		while(*per<='9'&&*per>='0'){
			a = a * 10 + *per - '0';
			t = (LL)b * 10 + *per - '0';
			if(a > P[0]) a%=P[0];
			b = (t > P[1])?(t % P[1]):t;
			++per;
		}
		if(sign)a = -a,b = -b;
	}
	for(int i = 1;i < P[0];++i){
		ans[i] = A[n][0];
		for(int j = n-1;~j;--j)ans[i] = (ans[i] * i + A[j][0])%P[0];
	}
	for(int i = 1;i <= m;++i)if(!ans[i%P[0]])first[++(*first)] = i;
	for(int i = 1;i <= *first;++i){
		int x = first[i];ans[i] = A[n][1];
		for(int j = n-1;~j;--j)ans[i] = ((LL)ans[i] * x + A[j][1])%P[1];
	}
	for(int i = 1;i <= *first;++i)if(!ans[i])second[++(*second)] = first[i];
	cout << second[0] << endl;  
    for (int i = 1; i <= second[0]; ++ i) printf("%d\n", second[i]);  
    return 0;  
}
