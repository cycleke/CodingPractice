#include <bits/stdc++.h>
using namespace std;
struct D{
	int a; string name;
	bool operator < (const D&x) const {return a<x.a;}
}p[3005];
bool vis[3005];
int main() {
	int n,i,j,k;
	cin >> n;
	for(i=1;i<=n;++i) cin >> p[i].name >> p[i].a;
	sort(p+1,p+n+1);
	for(i=1;i<=n;++i) if(p[i].a>=i) return puts("-1"),0;
	for(i=n;i;--i) {
		k=n-p[i].a;
		while(vis[k])--k;
		vis[p[i].a=k]=true;
	}
	for(i=1;i<=n;++i)
	  cout<<p[i].name<<' '<<p[i].a<<endl;
	return 0;
}
