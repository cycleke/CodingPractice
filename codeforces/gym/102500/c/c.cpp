# include <bits/stdc++.h>
# define R register
# define N 10010
# define LL long long
# define db double
using namespace std;

int n,m,l[N],r[N],a[N],ans[N],cnt,p[N];

int main(){
	scanf("%d",&n);
	for (int i=1; i<=n; ++i) scanf("%d%d",&l[i],&r[i]);
	l[1]--,r[n]++;
	scanf("%d",&m);
	for (int i=1; i<=m; ++i) scanf("%d",&a[i]);
	for (int i=1,t=1; i<=n; ++i)
	{
		int sum = 0;
		while (t<=m && a[t]<l[i]) t++;
		while (t<=m && a[t]<r[i])
		{
			sum++;
			t++;
		}
		if (t <= m && a[t] == r[i]) sum++;
		if (sum > 2) printf("impossible"),exit(0);
		else p[i] = sum;
	}
	
	for (int i=1,t=1; i<=n; ++i)
	{
		if (p[i] == 2) continue;
		while (t+1<=m && a[t+1]<=r[i]) t++;
		if (i < n && a[t] != r[i] && p[i+1] != 2 && r[i]==l[i+1]) p[i+1]++,p[i]++,ans[++cnt] = r[i];
	}
	for (int i=1; i<=cnt; ++i) a[++m] = ans[i];
	sort(a+1,a+m+1);
	for (int i=1,t=1; i<=n; ++i)
	{
		if (p[i] == 2) continue;
		while (t<=m && a[t]<l[i]) t++;
		if (t > m)
		{
			for (int j=l[i]+1; j<r[i]; ++j)
			{
				ans[++cnt] = j;
				p[i]++;
				if (p[i] == 2) break;
			}
			continue;
		}
//		printf("%d - %d\n",i,t);
		for (int j=l[i]+1; j<a[t]; ++j)
		{
			ans[++cnt] = j;
			p[i]++;
			if (p[i] == 2) break;
		}
		if (p[i] == 2) continue;
		while (t+1<=m && a[t+1]<=r[i] && p[i]<2)
		{
			for (int j=a[t]+1; j<a[t+1]; ++j)
			{
				ans[++cnt] = j;
				p[i]++;
				if (p[i] == 2) break;
			}
			t++;
		}
		if (p[i] == 2) continue;
		for (int j=a[t]+1; j<r[i]; ++j)
		{
			ans[++cnt] = j;
			p[i]++;
			if (p[i] == 2) break;
		}
	}
	sort(ans+1,ans+cnt+1);
	printf("%d\n",cnt);
	for (int i=1; i<=cnt; ++i) printf("%d ",ans[i]);
	return 0;
}
/*
4
0 18
18 28
28 40
49 60
3
6 12 35

*/
