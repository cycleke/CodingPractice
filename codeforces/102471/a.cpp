#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
  int n,m;
  scanf("%d%d",&n,&m);
  ll A=1LL*(m-m/2)*(m/2);
  ll B=1LL*(n-n/2)*(n/2);
  ll ans=2LL*A*B+A*(n+1)+B*(m+1);
  printf("%lld\n",ans);
  return 0;
}

