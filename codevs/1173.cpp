#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1 << 30;
const int maxn = 100000 + 10;
int n,m;
struct edge{
	int to;
	edge* next;
};
edge* head[maxn];
edge* fan[maxn];
int p[maxn],minp[maxn],maxp[maxn];
bool inq[maxn];

void SPFA1()
{
	memset(minp,127,sizeof(minp));
	queue<int>q;
	q.push(1);
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		minp[u] = min(minp[u],p[u]);
		for(edge* i = head[u];i != NULL;i = i->next)
		{
			int v = i->to;
			if(minp[v]>minp[u])
			{
				minp[v] = minp[u];
				if(!inq[v])
				{
					inq[v] = true;
					q.push(v);
				}
			}
		}
	}
}

void SPFA2()
{
    queue<int>q;
	q.push(n);
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		maxp[u] = max(maxp[u],p[u]);
		for(edge* i = fan[u];i != NULL;i = i->next)
		{
			int v = i->to;
			if(maxp[v]<maxp[u])
			{
				maxp[v] = maxp[u];
				if(!inq[v])
				{
					inq[v] = true;
					q.push(v);
				}
			}
		}
	}
}

void adde(int a,int b)
{
	edge* n1 = new edge;
	edge* n2 = new edge;
	n1->to = b,n2->to = a;
	n1->next = head[a],n2->next = fan[b];
	head[a] = n1,fan[b] = n2;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i)scanf("%d",&p[i]);
	int a,b,c;
	for(int i = 1;i <= m;++i)
	{
		scanf("%d%d%d",&a,&b,&c);
		adde(a,b);
		if(c == 2) adde(b,a);
	}
	SPFA1();
	SPFA2();
	int ans = 0;
	for(int i = 1;i <= n;++i)
	{
        ans = max(ans,maxp[i] - minp[i]);
        //printf("%5d %5d\n",maxp[i],minp[i]);
	}

	cout << ans;
	return 0;
}
