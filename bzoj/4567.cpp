#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 510002
int ch[26][N],tn; bool d[N];
inline void insert(char *s) {
	int u=0,i=strlen(s)-1;
	for(;~i;u=ch[s[i--]-'a'][u])if(!ch[s[i]-'a'][u])ch[s[i]-'a'][u]=++tn;
	d[u]=true;
}
int sz[N],id[N]; long long ans;
inline bool cmp(const int&a,const int&b){return sz[a]<sz[b];}
vector<int>g[N];
void build(int u,int fa) {
	int t=0;
	if(d[u])g[fa].push_back(t=++tn),fa=t;
	for(int i=0;i<26;++i)if(ch[i][u])build(ch[i][u],fa);
	if(t) {
		sz[t]=1;
		for(int i=0;i<g[t].size();++i)sz[t]+=sz[g[t][i]];
	}
}
void cal(int u) {
	id[u]=++tn;
	sort(g[u].begin(),g[u].end(),cmp);
	for(int i=0;i<g[u].size();++i) {
		ans+=tn+1-id[u];
		cal(g[u][i]);
	}
}
char ts[N];
int main() {
	int n;
	scanf("%d",&n);
	while(n--) {
		scanf("%s",ts);
		insert(ts);
	}
	tn=0; build(0,0);
	tn=0; cal(0);
	printf("%lld\n",ans);
	return 0;
}
