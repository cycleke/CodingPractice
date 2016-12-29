#include<cstdio>
#include<queue>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
#define maxe 2000000

struct edge{
    int to,weight;
    edge* next;
};

int S(0),T,n,m;
edge* head[maxe];
bool inq[maxe];
int d[maxe];
int f[maxe];

void adde(const int& a,const int& b,const int& c)
{
    edge* n1 = new edge;
    n1->to = b,n1->weight = c;
    n1->next = head[a];
    head[a] = n1;
}

void input()
{
    int e = 1,f = 2;
    for(int i = 0,a,b,c;i < n;++i)
    for(int j = 1;j < m;++j){
        scanf("%d",&c);
        if(!i){
            a = T;
            b = f;
            f+= 2;
        }else if(i == n - 1){
            a = e;
            b = 0;
            e+= 2;
        }else{
            a = e; b = f;
            e+=2; f+=2;
        }
        adde(a,b,c);
        adde(b,a,c);
    }
	e = 1,f = 2;
	for(int i = 1,a,b,c;i < n;++i)
	for(int j = 0;j < m;++j)
	{
		scanf("%d",&c);
		if(!j){
			a = 0;b = e;e+=2;
		}else if(j == m -1){
			a = f;b = T;f+=2;
		}else{
			a = e; b = f;
            e+=2; f+=2;
		}
		adde(a,b,c);adde(b,a,c);
	}
	e = 1,f = 2;
	for(int i = 1,c;i < n;++i)
	for(int j = 1;j < m;++j)
	{
		scanf("%d",&c);
		adde(e,f,c);
		adde(f,e,c);
		e+=2,f+=2;
	}
}

void pp(const int& a){
	if(a == 0) return;
	pp(f[a]);
	printf("%d ",a);
}

void work()
{
	memset(d,127,sizeof(d));
	d[0] = 0;
	queue<int>q;
	q.push(0);
	while(!q.empty())
	{
		int s = q.front();q.pop();
		inq[s] = false;
		for(edge* i = head[s];i != NULL;i = i->next){
			if(d[i->to] > d[s] + i->weight){
				d[i->to] = d[s] + i->weight;
				f[i->to] = s;
				if(!inq[i->to]){
					q.push(i->to);
					inq[i->to] = true;
				}
			}
		}
	}
	printf("%d",d[T]);
}

int main()
{
    scanf("%d%d",&n,&m);
    T = (n - 1)*(m - 1)*2 + 1;
    if(n == 1 || m == 1){
    	int ans = 1 << 30;
    	int a;
    	while(scanf("%d",&a) == 1) ans = min(a,ans);
    	cout << ans;
    	return 0;
    }
    input();
    work();
    return 0;
}
