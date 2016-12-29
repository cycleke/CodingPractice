#include <bits/stdc++.h>
using namespace std;
char ans[2000];
stack<int>st;
int n,l[700],r[700],p[700],i,ok,cnt,t;
int main() {
	for(scanf("%d",&n),i=0,ok=1;i<n&&ok;++i) {
		scanf("%d%d",l+i,r+i);
		p[i]=cnt; ans[cnt++]='('; st.push(i);
		while(!st.empty()) {
			t=st.top();
			if(p[t]+l[t]>cnt) break;
			if(p[t]+r[t]<cnt) {ok=0; break;}
			ans[cnt++]=')'; st.pop();
		}
	}ans[cnt++]=0;
	if(ok&&st.empty()) puts(ans);
	else puts("IMPOSSIBLE");
	return 0;
}
