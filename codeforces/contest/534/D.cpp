#include <bits/stdc++.h>
using namespace std;
stack<int>st[200005];
int ans[200005];
int main() {
	int n,a,i,j;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%d",&a),st[a].push(i);
	i=0,j=0;
	while(true) {
		if(!st[i].empty()) ans[++j]=st[i++].top();
		else {
			if(i<3) break;
			for(a=0;a<3;++a) st[--i].pop();
		}
	}
	if(j==n) for(i=1,puts("Possible");i<=n;++i) printf("%d ",ans[i]);
	else puts("Impossible");
	return 0;
}
