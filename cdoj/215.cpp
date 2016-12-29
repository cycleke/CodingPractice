#include <cstdio>
#include <cstring>
#include <algorithm>
int n, stick[100];
bool vis[100];

bool cmp(const int &a, const int &b) {return a>b;}

bool check(int resstick, int getlen, int pre,const int &tmp) {
	if (resstick==0) return true;
	for (int i = pre+1; i < n; ++i) {
		if (vis[i]) continue;
		if (getlen+stick[i]==tmp) {
			vis[i] = true;
			if (check(resstick-1,0,-1,tmp))
			  return true;
			vis[i] = false;
			return false;
		} else if (getlen+stick[i]<tmp) {
			vis[i] = true;
			if (check(resstick,getlen+stick[i],i,tmp))
			  return true;
			vis[i] = false;
			if (getlen==0)
			  return false;
			while(stick[i]==stick[i+1])
			  ++i;
		}
	}
	return false;
}


int main() {
	int sum, i;
	while (scanf("%d", &n) != EOF) {
		if (n==0) break; sum = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", stick + i);
			sum += stick[i];
		}
		std::sort(stick,stick+n,cmp);
		for (i = *stick; i <= sum; ++i) {
			if (sum % i) continue;
			memset(vis, 0, sizeof vis);
			if (check(sum/i,0,-1,i)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
