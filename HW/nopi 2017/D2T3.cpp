#include <vector>
#include <cstdio>
#include <cstring>

const int N = 300005, M = N * 50;

struct SegNode {
	int size;
	SegNode *ls, *rs;
} *rt[N], SegMemory[M], *CurtenSegNode;

int n, m, SegN;
std::vector < long long > Array[N];

int Query(int l, int r, SegNode* (&u), const int &x) {
	if (l == r) return l;
	if (u == NULL)
		u = CurtenSegNode++;
	int mid = (l + r) >> 1;
	int t = mid - l + 1 - (u->ls != NULL ? u->ls->size : 0);
	if (x <= t) return Query(l, mid, u->ls, x);
	else return Query(mid + 1, r, u->rs, x - t);
}

void Delete(int l, int r, SegNode* (&u), const int &x) {
	if (u == NULL)
		u = CurtenSegNode++;
	++u->size;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) Delete(l, mid, u->ls, x);
	else Delete(mid + 1, r, u->rs, x);
}

inline long long DeleteRow(int x) {
	int p = Query(1, SegN, rt[n + 1], x);
	Delete(1, SegN, rt[n + 1], p);
	return p <= n ? (1ll * (p - 1) * n + m) : Array[n + 1][p - n - 1];
}

inline long long DeleteColumn(int x, int y) {
	int p = Query(1, SegN, rt[x], y);
	Delete(1, SegN, rt[x], p);
	return p < m ? (1ll * (x - 1) * n + p) : Array[x][p - m];
}

int main() {
	int q;
	CurtenSegNode = SegMemory;
	scanf("%d %d %d", &n, &m, &q);
	SegN = (n < m ? m : n) + q;
	while (q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (y == m) {
			long long t1;
			t1 = DeleteRow(x);
			Array[n + 1].push_back(t1);
			printf("%lld\n", t1);
		} else {
			long long t1, t2;
			t1 = DeleteColumn(x, y);
			Array[n + 1].push_back(t1);
			t2 = DeleteRow(x);
			Array[x].push_back(t2);
			printf("%lld\n", t1);
		}
	}
	return 0;
}
