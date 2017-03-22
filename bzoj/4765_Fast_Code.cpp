#include<bits/stdc++.h>
#define K 317
#define N 100005
#define M 200005
using namespace std;
typedef unsigned long long ll;
struct graph{
	int nxt,to;
}e[M];
int g[N],f[N],n,m,cnt;
ll a[N];bool v[N];
ll tot[N][K],s_d[K<<1],s_n[K],key[N<<1];
int fro[N],beh[N],r_d,t_d=1,r_n,t_n;
int n_n[N],n_f[N],n_b[N];
struct FastInput {
    char b[5<<20], *s;
    FastInput() : s(b) {
        b[fread(b, 1, 5 << 20, stdin)] = 0;
    }
	template<class T>
    inline void gi(T &a) {
        while (*s < 48) ++s;
        a = *s++ - 48;
        while (47 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
    }
} io;
inline void addedge(int x,int y){
	e[++cnt].nxt=g[x];g[x]=cnt;e[cnt].to=y;
}
inline void dfs(int u){
	int sta[N],top=0;
	cnt=0;v[u]=true;
	for(int i=g[u];i;i=e[i].nxt){
		v[e[i].to]=true;
		sta[++top]=e[i].to;
		++tot[e[i].to][n_n[e[i].to]];
	}
	while(top){
		u=sta[top];fro[u]=++cnt;
		if(v[e[g[u]].to]){
			beh[u]=++cnt;--top;
			while(f[u]){
				u=sta[top--];beh[u]=++cnt;
			}
		}
		else f[e[g[u]].to]=u;
		for(int i=g[u];i;i=e[i].nxt)
		  if(!v[e[i].to]){
			  v[e[i].to]=true;
			  sta[++top]=e[i].to;
			  for(int j=1;j<=t_n;++j)
				tot[e[i].to][j]=tot[u][j];
			  ++tot[e[i].to][n_n[e[i].to]];
		  }
	}
}
inline void change(int u,ll k){
	a[u]+=k;
	for(int i=1;i<=t_n;++i)
	  s_n[i]+=tot[u][i]*k;
	for(int i=1;i<n_f[u];++i)
	  s_d[i]+=k;
	if(n_f[u]*r_d==fro[u])
	  s_d[n_f[u]]+=k;
	else for(int i=(n_f[u]-1)*r_d+1;i<=fro[u];++i)
	  key[i]+=k;
}
inline void init(){
	//n=read();m=read();
	io.gi(n), io.gi(m);
	for(int i=1;i<=n;++i)
	  //a[i]=read_ll();
	  io.gi(a[i]);
	for(int i=1,j,k;i<=n;++i){
		//j=read();k=read();
		io.gi(j), io.gi(k);
		addedge(j,k);addedge(k,j);
	}
	r_n=sqrt(n);
	for(int i=1;i<=n;i+=r_n){
		++t_n;
		for(int j=0;j<r_n&&i+j<=n;++j)
		  n_n[i+j]=t_n;
	}
	dfs(0);
	r_d=sqrt(n<<1);t_d=((n<<1)+r_d-1)/r_d;
	for(int i=1;i<=n;++i){
		n_f[i]=(fro[i]+r_d-1)/r_d;
		n_b[i]=(beh[i]+r_d-1)/r_d;
	}
	for(int i=1;i<=n;++i){
		a[0]=a[i];a[i]=0;change(i,a[0]);
	}
	int op,l,r,u;ll v,ans;
	while(m--){
		//op=read();
		io.gi(op);
		if(op==1){
			//u=read();v=read_ll();
			io.gi(u), io.gi(v);
			change(u,v-a[u]);
		}
		else{
			//l=read();r=read();ans=0;
			io.gi(l), io.gi(r);ans=0;
			if(n_n[l]!=n_n[r]){
				for(int i=n_n[l]+1;i<n_n[r];++i)
				  ans+=s_n[i];
				if(l==(n_n[l]-1)*r_n+1) ans+=s_n[n_n[l]];
				else for(int i=n_n[l]*r_n;i>=l;--i)
				  ans+=(s_d[n_f[i]]+key[fro[i]])-(s_d[n_b[i]]+key[beh[i]]);
				if(r==n_n[r]*r_n) ans+=s_n[n_n[r]];
				else for(int i=(n_n[r]-1)*r_n+1;i<=r;++i)
				  ans+=(s_d[n_f[i]]+key[fro[i]])-(s_d[n_b[i]]+key[beh[i]]);
			}
			else{
				if(l==(n_n[l]-1)*r_n+1&&r==n_n[r]*r_n){
					ans=s_n[n_n[l]];
				}
				else for(int i=l;i<=r;++i)
				  ans+=(s_d[n_f[i]]+key[fro[i]])-(s_d[n_b[i]]+key[beh[i]]);
			}
			printf("%llu\n",ans);
		}
	}
}
int main(){
	init();
	return 0;
}
