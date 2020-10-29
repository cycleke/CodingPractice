# include <bits/stdc++.h>
# define LL long long
# define N 100010

using namespace std;

int n,a[N],b[N],cnt,num[N];
bool v[N],it[N];
LL ans,nowans;

void dfs(int id){
	if (id == cnt+1)
	{
		LL now = 0;
		for (int i=1; i<=cnt; ++i) if (it[i]) now += a[num[i]];
		for (int i=1; i<=cnt; ++i)
		{
			if (!it[i]) continue;
			for (int j=i+1; j<=cnt; ++j)
			{
				if (!it[j]) continue;
				if (j%i) continue;
				now -= b[num[j]];
			}
		}
		nowans = max(nowans,now);
		return;
	}
	it[id] = 1;
	dfs(id+1);
	it[id] = 0;
	dfs(id+1);
}

int main()
{
//	freopen("data.txt","r",stdin);
	scanf("%d",&n);
	for (int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for (int i=1; i<=n; ++i) scanf("%d",&b[i]);
	ans += a[1];
	for (int i=2; i<=n; ++i)
	{
		if (v[i]) continue;
//		printf("%d ",i);
		LL now = i;
		cnt = 0;
		while (now <= 1LL*n)
		{
			num[++cnt] = now;
			v[now] = 1;
			now *= i;
		}
		nowans = 0;
		dfs(1);
//		printf("%d -- ",nowans);
		ans += nowans;
	}
	printf("%lld",ans);
}

