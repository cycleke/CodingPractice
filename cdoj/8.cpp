#include <cstdio>
#include <cstring>
const int MLS=1e6+10,MLv=1e5+10,SIZ=26;
char S[MLS], virus[MLv];
int ch[MLv][SIZ], dep[MLv], len[MLv], totNode, fail[MLv];
bool is_virus[MLv];

//AC
#define init(u) (memset(ch[u],0,SIZ<<2),is_virus[u]=false)

void Insert(char *s) {
	int u = 0, idx;
	while (*s) {
		idx = (*s++) - 'a';
		if (!ch[u][idx]) {
			ch[u][idx] = ++totNode;
			init(totNode);
			dep[totNode] = dep[u] + 1;
		}
		u = ch[u][idx];
	}
	is_virus[u] = true;
}

int que[MLv], tail, top;

void Build() {
	top = tail = 0;
	fail[0] = 0; len[0] = -1;
	for (int i = 0; i < SIZ; ++i)
	  if (ch[0][i]) fail[ch[0][i]]=0,que[tail++]=ch[0][i];
	while (top < tail) {
		int u = que[top++];
		if (len[fail[u]]==-1&&is_virus[u]) len[u] = dep[u];
		else len[u]=len[fail[u]];
		for (int i = 0; i < SIZ; ++i) 
		if (ch[u][i]){
			fail[ch[u][i]] = ch[fail[u]][i];
			que[tail++] = ch[u][i];
		} else ch[u][i] = ch[fail[u]][i];
	}
}

inline void cmax(int &a, const int &b) {a<b?a=b:1;}

long long Work() {
	scanf("%s",S);
	int n; scanf("%d", &n);
	totNode = 0; init(0);
	while (n--) {
		scanf("%s", virus);
		Insert(virus);
	}
	Build(); n = strlen(S);
	int u = 0, la = 0; long long ans = (n+1LL)*n>>1;
	for (int i = 0; i < n; ++i) {
		u = ch[u][S[i]-'a'];
		if (~len[u]) cmax(la, i-len[u] + 2);
		ans -= la;
	}
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= T; ++i) printf("Case #%d: %lld\n", i, Work());
	return 0;
}
