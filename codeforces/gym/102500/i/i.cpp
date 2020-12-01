# include <bits/stdc++.h>
# define R register
# define N 1000010
# define LL long long

using namespace std;

int n,a[N],b[N];

int main(){
	scanf("%d",&n);
	for (int i=1; i<=n; ++i) scanf("%d",&a[i]),b[i] = a[i];
	sort(a+1,a+n+1); 
	int s = 1,t = n;
	while (s < n && a[s] == b[s]) s++;
	while (t > s && a[t] == b[t]) t--;
	for (int i=s,j=t; i<=t; ++i,--j)
		if (a[i] != b[j]) printf("impossible\n"),exit(0);
	printf("%d %d\n",s,t); 
}

