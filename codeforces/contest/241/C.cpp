#include <bits/stdc++.h>
using namespace std;

int idx[2][100000];
int v[100];
bool vis[100];

int main() {
	int hl, hr, n, l, r;
	char ts[2];
	scanf("%d %d %d",&hl,&hr,&n);

	memset(idx,-1,sizeof idx);

	for (int i = 0; i < n; ++i) {
		scanf("%d %s %d %d",v+i,ts,&l,&r);
		int id = (*ts=='T')?0:1;
		for (int j = l; j < r; ++j)
		  idx[id][j] = i;
	}

	int y1 = hl,y2;
	int ans = 0;

	for(int i = 1; i <= 100; ++i){

		if (i&1) y2 = -100*(i-1)-hr;
		else y2 = -100*i+hr;	

		bool ok = true;
		int tmp = 0;

		memset(vis, 0, sizeof vis);

		for(int j = 0,id = 1; j < i; ++j, id ^= 1) {

			int y = -100 * j;

			int x = (int)floor((y - hl) * 100000.0 / (y2 - y1));

			if(idx[id][x]==-1) ok = false;
			else if(vis[idx[id][x]]) ok = false;
			else{
				vis[idx[id][x]] = true;
				tmp += v[idx[id][x]];
			}
		}

		if(ok) ans = max(ans,tmp);
	}


	for (int i = 1; i <= 100; ++i) {

		if (i&1) y2 = 100*(i+1)-hr;
		else y2 = 100*i+hr;

		bool ok = true;
		int tmp = 0;

		memset(vis, 0, sizeof vis);

		for (int j = 0, id = 0; j < i; ++j, id ^= 1) {

			int y = 100 * (j+1);

			int x = (int)floor((y - hl) * 100000.0 / (y2 - y1));

			if(idx[id][x]==-1) ok = false;
			else if (vis[idx[id][x]]) ok = false;
			else {
				vis[idx[id][x]] = true;
				tmp += v[idx[id][x]];
			}
		}
		if (ok) ans = max(ans, tmp);

	}

	printf("%d\n", ans);

	return 0;
}
