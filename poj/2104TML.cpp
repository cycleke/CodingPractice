#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;

struct node{
	int sum;
	node* son[2];
};
node* nil;
node* C[100010];
int A[100010],mp[100010],r[100010],n,m,id;
bool cmp(const int& a,const int& b){
	return A[a] < A[b];
}
int Hash(){
	memset(mp,0,sizeof(mp));
	for(int i = 1;i <= n;++i)r[i]=i;
	sort(r+1,r+n+1,cmp);
	id = 1;
	mp[id] = A[r[id]];
	for(int i = 1;i <= n;++i){
		if(A[r[i]]!=mp[id])mp[++id] = A[r[i]];
		A[r[i]] = id;
	}
	return id;
}

void add(node* r1,node* &r2,const int& a){
	r2 = new node;
	node *s1 = r1,*s2 = r2;
	int s,e,mid;
	s = 1,e = id;
	while(s<e){
		mid = (s+e)>>1;
		s2->sum = s1->sum + 1;
		if(a<=mid){
			e = mid;
			s2->son[1] = s1->son[1];
			s2->son[0] = new node;
			s2 = s2->son[0];
			s1 = s1->son[0];
		}else{
			s = mid+1;
			s2->son[0] = s1->son[0];
			s2->son[1] = new node;
			s2 = s2->son[1];
			s1 = s1->son[1];
		}
	}
	s2->sum = 1;
	s2->son[0] = s2->son[1] = nil;
}

void work(const int& a,const int& b,const int& k){
	node *r1 = C[a-1],*r2 = C[b];
	int rk = k,s = 1,e = id,size,mid;
	while(s<e){
		mid = (s+e)>>1;
		size = r2->son[0]->sum - r1->son[0]->sum;
		if(size < rk){
			s = mid + 1;
			rk-=size;
			r1 = r1->son[1],r2 = r2->son[1];
		}else{
			e = mid;
			r1 = r1->son[0],r2 = r2->son[0];
		}
	}
	printf("%d\n",mp[s]);
}

int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int a,b,k;
	double t1 = clock() / CLOCKS_PER_SEC;
	nil = new node;
	nil->sum = 0;nil->son[0] =nil->son[1] = nil;
	while(scanf("%d%d",&n,&m)!=EOF){
		*C = nil;
		for(int i = 1;i <= n;++i)scanf("%d",A+i);
		Hash();
		for(int i = 1;i <= n;++i)add(C[i-1],C[i],A[i]);
		for(int i = 1;i <= m;++i){
			scanf("%d%d%d",&a,&b,&k);
			work(a,b,k);
		}
	}
	return 0;
}
