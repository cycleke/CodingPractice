#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define N 1010

int dp[N][10][10];
char s1[N],s2[N];

void SelfMin(int &a, int b) {if (a>b) a=b;}

int main() {
	while (scanf("%s%s",s1,s2)^EOF) {
		memset(dp, 63, sizeof dp);
		int n = strlen(s1);
		dp[0][0][0] = 0;
		for (int i = 0; i <  n; ++i) 
		  for (int j = 0; j < 10; ++j)
			for (int k = 0; k < 10; ++k) {
				int a = (s2[i]-s1[i]-j+20)%10;
				for (int b = 0; b <= a; ++b)
				  for (int c = 0; c <= b; ++c)
					SelfMin(dp[i+1][(k+b)%10][c],dp[i][j][k]+a);
				a = (10-a)%10;
				for (int b = 0; b <= a; ++b)
				  for (int c = 0; c <= b; ++c)
					SelfMin(dp[i+1][(k-b+10)%10][(10-c)%10],dp[i][j][k]+a);
			}
		printf("%d\n",dp[n][0][0]);
	}
	return 0;
}
