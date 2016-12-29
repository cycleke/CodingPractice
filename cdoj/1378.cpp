#include <cstdio>
#include <cstring>

bool lie[20], he[30], cha[30];
int a[15];

void dfs(int u) {
	if (9 < u) {
		for (int i = 1; i <= 9; ++i)
		  printf("%d ", a[i]);
		puts("");
	} else {
		for (int i = 1; i <= 9; ++i) 
		if (!lie[i] && !he[i+u] && !cha[u-i+10]) {
			lie[i] = he[i+u] = cha[u-i+10] = true;
			a[u] = i; dfs(u+1);
			lie[i] = he[i+u] = cha[u-i+10] = false;
		}
	}
}

int main() {
	puts("352");
	dfs(1);	
	return 0;
}
