#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN(100005);
typedef unsigned long long ull;
struct FastInput {
	char b[5<<20], *s;
	FastInput() : s(b) {
		b[fread(b, 1, 5 << 20, stdin)] = 0;
	}
	inline void gi(int &a) {
		while (*s < 48) ++s;
		a = *s++ - 48;
		while (47 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
	}
} io;
struct FastOutput {
	char bufout[3<<19], outtmp[50], *pout;
	FastOutput() : pout(bufout) {}
	inline void write() {
		*pout = 0;
		fwrite(bufout, sizeof(char), pout - bufout, stdout);
	}
#define out_char(c) *(pout++) = c
	inline void out_int(ull x) {
		if(!x) {
			out_char('0');
			return;
		}
		register int len = 0;
		while(x) {
			outtmp[len++] = x % 10 + 48;
			x /= 10;
		}
		for(--len; ~len; --len) out_char(outtmp[len]);
		out_char('\n');
	}
} op;
struct edge {int to;edge *nxt;} edge_mset[MaxN << 1], *cedge = edge_mset, *g[MaxN];
inline void add_edge(int u, int v) {*cedge = (edge) {v, g[u]};g[u] = cedge++;}
ull s1[320], s2[320], s3[MaxN];
int a[MaxN], in[MaxN], ou[MaxN], d[320][MaxN], bel[MaxN], dq[MaxN];
inline ull sum(int l, int r) {return (s3[r] - ((bel[l - 1] ^ bel[l]) ? 0 : s3[l - 1]) + s2[bel[r] - 1] - s2[bel[l] - 1]);}
inline void dfs(int u) {
	static int dfn = 0;
	dq[in[u] = ++dfn] = u;
	for (edge *it = g[u]; it; it = it->nxt)
		if (!in[it->to]) dfs(it->to);
	ou[u] = dfn;
}
int main() {
	int n, m, a, b, type, blo, root;
	io.gi(n), io.gi(m);
	for (blo = 1; blo * blo <= n; ++blo);
	for (register int i = 1; i <= n; ++i) {
		io.gi(::a[i]);
		bel[i] = (i - 1) / blo + 1;
	}
	for (register int i = 0; i < n; ++i) {
		io.gi(a), io.gi(b);
		if (a) {
			add_edge(a, b);
			add_edge(b, a);
		} else
			root = b;
	}
	dfs(root);
	a = bel[n] + 1;
	for (register int i = 1, j = 1; i < a; ++i) {
		s2[i] += s2[i - 1];
		for (b = min(i * blo, n) + 1; j < b; ++j) {
			++d[i][in[j]], --d[i][ou[j] + 1];
			s2[i] += (s3[j] = ::a[dq[j]]);
			s3[j] += (bel[j] ^ bel[j - 1]) ? 0 : s3[j - 1];
		}
		for (b = 1; b <= n; ++b) s1[i] += (ull)(d[i][b] += d[i][b - 1]) * ::a[dq[b]];
	}
	while (m--) {
		io.gi(type), io.gi(a), io.gi(b);
		if (type & 1) {
			static int delta;
			delta = b - ::a[a];
			::a[a] = b;
			for (register int i = 1; i <= bel[n]; ++i) s1[i] += (ull)(d[i][in[a]]) * delta;
			for (register int i = bel[in[a]]; i <= bel[n]; ++i) s2[i] += delta;
			for (register int i = in[a]; bel[i] == bel[in[a]]; ++i) s3[i] += delta;
		} else {
			static ull ans;
			ans = 0;
			if (bel[b] - bel[a] <= 1)
				for (register int i = a; i <= b; ++i)
					ans += sum(in[i], ou[i]);
			else {
				for (register int i = bel[a] + 1; i < bel[b]; ++i)
					ans += s1[i];
				for (register int i = a; bel[i] == bel[a]; ++i)
					ans += sum(in[i], ou[i]);
				for (register int i = b; bel[i] == bel[b]; --i)
					ans += sum(in[i], ou[i]);
			}
			op.out_int(ans);
		}
	}
	op.write();
	return 0;
}
