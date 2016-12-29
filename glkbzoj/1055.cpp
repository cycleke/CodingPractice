#include <cstdio>
#include <cstring>

int Pos[255], t[4];
int f[205][205][4];
char Replace[4][20][2];
const char p[] = {'W', 'I', 'N', 'G'};
char S[205];

bool dp(const int &l, const int &r, const int &k) {
	if (!(l ^ r)) return S[l] == p[k];
	int &tmp = f[l][r][k];
	if (~tmp) return tmp;
	for (int i = 0; i < t[k]; ++i) //枚举各种压缩方案 
	for (int j = l; j < r; ++j) //枚举位置 
	if (dp(l, j, Pos[Replace[k][i][0]]) && dp(j + 1, r, Pos[Replace[k][i][1]]))
	return tmp = 1;
	return tmp = 0; 
}

int main() {
	
	for (int i = 0; i < 4; ++i) scanf("%d", t + i);
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < t[i]; ++j)
	scanf("%s", Replace[i][j]);
	scanf("%s", S);
	
	int len = strlen(S);
	bool ok = false;
	memset(f, -1, sizeof f);
	Pos['W'] = 0; Pos['I'] = 1; Pos['N'] = 2; Pos['G'] = 3;
	
	for (int i = 0; i < 4; ++i) {
		if (dp(0, len - 1, i)) {
			ok = true; putchar(p[i]);
		}
	}
	if (!ok) puts("The name is wrong!");
	
	
	return 0;
}
