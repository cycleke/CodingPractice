#include<cstdio>


int n;
bool lie[20];
bool he[30],cha[50];
int ans(0);

void dfs(int cur)
{
	if(!cur) ++ans;
	else
	{
		int h = cur;
		for(int i = 1;i <= n;++i)
		if(!lie[i] && !he[i+h] && !cha[i-h+n])
		{
			lie[i] = he[i+h] = cha[i-h+n] = true;
			dfs(cur-1);
			lie[i] = he[i+h] = cha[i-h+n] = false;
		}
	}
}

int main()
{
	scanf("%d",&n);
	dfs(n);
	printf("%d",ans);
	return 0;
}
