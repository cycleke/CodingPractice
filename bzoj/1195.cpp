#include <cstdio>
#include <cstring>

typedef unsigned int uit;
const uit bs = 0xe7;
const int MaxN = 13, MaxL = 52;

bool mark[MaxN];
uit hash[MaxN][MaxL], p[MaxL];
char a[MaxN][MaxL], s[4096][MaxN][601];
int len[MaxN], f[4096][MaxN], c[MaxN][MaxN], bin[MaxN];

#define rep(i, l, r) for (i = l; i <= r; ++i)
#define inline 
inline void Pre(const char *s, const int &len, uit *f) {
	int i; rep(i, 1, len) f[i] = f[i - 1] * bs + s[i];
}

inline uit ghs(const uit *f, const int &l, const int &r) {
	return f[r] - f[l - 1] * p[r - l + 1];
}

inline uit ghs(const int &x, const int &l, const int &r) {
	return ghs(hash[x], l, r);
}

inline bool insd(const int &i, const int &j) {
	if (len[i] > len[j])
	  return false;
	static int k;
	rep(k, 1, len[j] - len[i] + 1)
		if (hash[i][len[i]] == ghs(j, k, k + len[i] - 1))
		  return true;
	return false;
}

inline int calc(const int &x, const int &y) {
	static int i;
	rep(i, (len[x] < len[y] ? 1 : (len[x] - len[y] + 1)), len[x]) {
		//printf("%u %u\n", ghs(x, i, len[x]), ghs(y, 1, len[x] - i + 1));
		if (ghs(x, i, len[x]) == ghs(y, 1, len[x] - i + 1))
		  return len[y] - (len[x] - i + 1);
	}
	return len[y];
}

int main() {
	//freopen("t.in", "r", stdin);
	bool flag;
	int i, j, k, x, n, cnt = 0, l, p;
	scanf("%d", &n);
	::p[0] = 1;
	rep(i, 1, MaxL - 1) ::p[i] = ::p[i - 1] * bs;
	rep(i, 1, n) {
		scanf("%s", a[i] + 1);
		len[i] = strlen(a[i] + 1);
		Pre(a[i], len[i], hash[i]);
		mark[i] = true;
	}
	rep(i, 1, n) rep(i, j + 1, n) {
		if (len[i] == len[j])
		  mark[i] = ! (hash[i][len[i]] == hash[j][len[j]]);
		else if (insd(i, j)) mark[i] = false;
		else if (insd(j, i)) mark[j] = false;
	}
	rep(i, 1, n) if (mark[i]) {
		memcpy(a[++cnt], a[i], sizeof a[i]);
		len[cnt] = len[i];
	}
	n = cnt;
	rep(i, 1, n) rep(j, i + 1, n) {
		c[i][j] = calc(i, j);
		c[j][i] = calc(j, i);
		//printf("%s %s %d\n", a[i] + 1, a[j] + 1, c[i][j]);
		//printf("%s %s %d\n", a[j] + 1, a[i] + 1, c[j][i]);
	}

	memset(f, 63, sizeof f);
	bin[0] = 1;
	rep(i, 1, n) {
		bin[i] = bin[i - 1] << 1;
		f[bin[i - 1]][i] = len[i];
		memcpy(s[bin[i - 1]][i], a[i], sizeof a[i]);
	}
	for (i = 1; i < bin[n]; ++i)
	  rep(j, 1, n) if (i & bin[j - 1]) {  
		  x = i ^ bin[j - 1];  
		  rep(k, 1, n) if (x & bin[k - 1]) {  
			  if (f[x][k] + c[k][j] < f[i][j]) {  
				  f[i][j] = f[x][k] + c[k][j]; 
				  memcpy(s[i][j], s[x][k], sizeof s[x][k]);  
				  l = strlen(s[i][j] + 1);
				  rep(p, len[j] - c[k][j] + 1, len[j]) 
					  s[i][j][++l] = a[j][p];  
			  } else if (f[x][k] + c[k][j] == f[i][j]){  
				  l=strlen(s[x][k] + 1); 
				  flag=false;  
				  rep(p, 1, l)
					  if (s[x][k][p] < s[i][j][p]) {
						  flag = true;
						  break;
					  } else if (s[x][k][p] > s[i][j][p]) 
						break;  
				  if (flag){  
					  memcpy(s[i][j], s[x][k], sizeof s[x][k]);  
					  rep (p, len[j]-c[k][j]+1, len[j]) 
						  s[i][j][++l]=a[j][p];  
				  }  
			  }  
		  }  
	  }  
	x=bin[n] - 1, k=1;  
	rep(i, 2, n)  
		if (f[x][i] < f[x][k]) 
		  k = i;
		else if (f[x][i] == f[x][k]) {  
			flag=0;  
			rep(j, 1, f[x][i])
			  if (s[x][i][j] < s[x][k][j]) { 
				  flag=1; 
				  break;
			  } else if (s[x][i][j] > s[x][k][j]) 
				break;  
			if (flag) k=i;  
		}  
	l = strlen(s[x][k] + 1);  
	rep(i, 1, l) putchar(s[x][k][i]); 
	puts("");  
	return 0;
}
