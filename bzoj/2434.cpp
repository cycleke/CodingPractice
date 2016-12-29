#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define SIZE 26
#define N 100005
int ch[SIZE][N],fail[N],fa[N],totnode;
int print_rank[N],print_array[N],print_id,que[N];
struct E{int to;E*nt;}CD[N],*cd=CD,*hd[N];
inline void adde(int a,int b){cd->to=b,cd->nt=hd[a],hd[a]=cd++;}
inline void build_fail() {
	int *l=que,*r=que,x,y,i,f;
	*r++=1;
	while(l<r) {
		x=*l++;
		adde(fail[x],x);
		for(i=0;i<SIZE;++i)
			if(y=ch[i][x]) {
				for(f=fail[x];f&&!ch[i][f];f=fail[f]);
				fail[y]=f?ch[i][f]:1;
				*r++=y;
			}
	}
}
//ac auto
int C[N];
inline int sum(int x){int r=0;for(;x;x-=x&-x)r+=C[x];return r;}
inline void add(int x,int v){for(;x<=totnode;x+=x&-x)C[x]+=v;}
//BIT
struct Q{int x,id;Q*nt;}CQ[N],*cq=CQ,*hq[N];
inline void addq(int a,int b,int c) {
	cq->x=b,cq->id=c;
	cq->nt=hq[a],hq[a]=cq++;
}
int ANS[N];
//query
int in[N],out[N],dfs_clock;
void dfs(int u) {
	in[u]=++dfs_clock;
	for(E*it=hd[u];it;it=it->nt)
		dfs(it->to);
	out[u]=dfs_clock;
}
//dfs_number
char operatorstring[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("2434.in","r",stdin);
#endif
	scanf("%s",operatorstring);
	int u=++totnode,i,j,k;
	for(char *s=operatorstring;*s;++s)
		if(*s=='P') print_array[print_rank[u]=++print_id]=u;
		else if(*s=='B') u=fa[u];
		else {
			i=*s-'a';
			if(!ch[i][u])fa[ch[i][u]=++totnode]=u;
			u=ch[i][u];
		}
	build_fail();
	dfs(1);
	int m=geti();
	for(i=0;i<m;++i) {
		j=geti(),k=geti();
		addq(k,j,i);
	}
	u=1;
	for(char *s=operatorstring;*s;++s)
		if(*s=='P') for(Q*it=hq[print_rank[u]];it;it=it->nt)
						ANS[it->id]=sum(out[print_array[it->x]])-sum(in[print_array[it->x]]-1);
		else if(*s=='B') add(in[u],-1),u=fa[u];
		else add(in[u=ch[*s-'a'][u]],1);
	for(i=0;i<m;++i)printf("%d\n",ANS[i]);
	return 0;
}
