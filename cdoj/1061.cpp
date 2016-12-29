#include <cstdio>
#include <cstring>
#define ls u<<1
#define rs u<<1|1
#define MID(a,b) int mid = a + b >> 1
#define N 100010
int lm[N << 2], rm[N << 2], mm[N << 2], l[N << 2], r[N << 2];
//Input
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
//Seg_Tree
void Build(int u, int L, int R) {
	l[u] = L, r[u] = R;
	lm[u] = rm[u] = mm[u] = R - L + 1;
	if (L ^ R) {
		MID(L, R);
		Build(ls, L, mid);
		Build(rs, mid+1, R);
	}
}
inline int max(const int &a, const int &b) { return a<b?b:a; }
void Update(int u, int pos, int val) {
	if (!(l[u] ^ r[u])) {
		lm[u] = rm[u] = mm[u] = val; return;
	}
	MID(l[u], r[u]);
	if (pos <= mid) Update(ls, pos, val);
	else Update(rs, pos, val);
	lm[u] = lm[ls]; rm[u] = rm[rs];
	mm[u] = max(max(mm[ls], mm[rs]), rm[ls] + lm[rs]);
	if (lm[u] == r[ls] - l[ls] + 1) lm[u] += lm[rs];
	if (rm[u] == r[rs] - l[rs] + 1) rm[u] += rm[ls];
}
int Query(int u, int pos) {
	if (!(l[u]^r[u])||!mm[u]||mm[u]>=r[u]-l[u]+1) return mm[u];
	MID(l[u], r[u]);
	if (pos <= mid) {
		if (pos >= r[ls] - rm[ls] + 1)
		  return Query(ls, pos) + Query(rs, mid+1);
		return Query(ls, pos);
	} else {
		if (pos <= l[rs] + lm[rs] - 1)
		  return Query(ls, mid) + Query(rs, pos);
		return Query(rs, pos);
	}
}
int main() {
	int n = geti(), m = geti(), op;
	Build(1, 1, n);
	while (m--) {
		if ((op = geti()) < 2) Update(1, geti(), op);
		else printf("%d\n", Query(1, geti()));
	}
	return 0;
}
