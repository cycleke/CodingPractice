#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

int n,m;
int du[30];
char ans[30];
struct edge{
	int v;
	edge* next;
};
edge* head[30];

void del(edge* e)
{
	if(e == NULL) return;
	del(e->next);
	delete e;
}

void adde(int s,int e)
{
	edge* ne = new edge();
	ne->next = head[s];
	ne->v = e;
	head[s] = ne;
	++du[e];
}

int topsort()
{
	stack<int>s;
	int d[30];
	memcpy(d,du,sizeof(du));
	bool ok = false;
	int cnt(0),t(0);
	for(int i = 0;i < n;++i)
	if(!d[i]){
		++t;
		s.push(i);
	}
	while(t)
	{
		if(t > 1) ok = true;//无唯一解
		int cs = s.top();
		s.pop();--t;
		ans[cnt++]=cs + 'A';
		for(edge* i = head[cs];i != NULL;i = i->next)
		{
			int ns = i->v;
			if(!(--d[ns]))
			{
				++t;
				s.push(ns);
			}
		}
	}
	if(cnt < n) return 1;//存在环
	if(ok) return -1;
	return 0;//排序成功 
}

void work()
{
	memset(du,0,sizeof(du));
	memset(head,0,sizeof(head));
	bool ok = false;
	char s[3];
	for(int i = 1;i <= m;++i)
	{
		memset(ans,0,sizeof(ans));
		scanf("%s",s);
		if(ok) continue;
		adde(s[0]-'A',s[2]-'A');
		int a = topsort();
		if(!a){
			ok = true;
			printf("Sorted sequence determined after %d relations: %s\n",i,ans);
		}
		else if(a == 1){
			ok = true;
			printf("Inconsistency found after %d relations.\n",i);
		}
	}
	if(!ok)
	{
		int a = topsort();
		if(a) printf("Sorted sequence cannot be determined.\n");
		else printf("Sorted sequence determined after %d relations: %s\n",n,ans);
	}
	for(int i = 0;i < n;++i)
	del(head[i]);
}

int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		if(!n) return 0;
		work();
	}
}
