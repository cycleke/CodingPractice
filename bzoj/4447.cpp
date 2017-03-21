#include <set>
#include <cstdio>
#include <algorithm>

const int MaxN = 1e5 + 7, inf = -0x3f3f3f3f;

struct Range {
	int l, r;
	Range(int l = 0, int r = 0) :
		l(l), r(r) {}
};

inline bool operator < (const Range &a, const Range &b) {
	return a.l < b.l;
}

inline bool operator < (const int &x, const Range &a) {
	return x < a.l;
}

int A[MaxN], a[MaxN << 1], n, m;
char C[MaxN];

std::set<Range> s;

inline void modify(const int &pos, const int &val) {
	if (val == 0 && a[pos] != 0) {
		for (register int x = pos; x < (n << 1); x += n) {
			static std::set<Range>::iterator pre, nxt;
			pre = nxt = s.lower_bound(x);
			--pre;
			if (nxt->l == x + 1 && pre->r == x - 1) {
				Range newRange(pre->l, nxt->r);
				s.erase(pre);
				s.erase(nxt);
				s.insert(newRange);
			} else if (nxt->l == x + 1) {
				Range newRange(x, nxt->r);
				s.erase(nxt);
				s.insert(newRange);
			} else if (pre->r == x - 1) {
				Range newRange(pre->l, x);
				s.erase(pre);
				s.insert(newRange);
			} else s.insert(Range(x, x));
		}
	} else if (val != 0 && a[pos] == 0) {
		for (register int x = pos; x < (n << 1); x += n) {
			static std::set<Range>::iterator it;
			it = --s.upper_bound(x);
			if (x != it->l && x != it->r) {
				Range newRange1(it->l, x - 1), newRange2(x + 1, it->r);
				s.erase(it);
				s.insert(newRange1);
				s.insert(newRange2);
			} else if (x != it->l) {
				Range newRange(it->l, x - 1);
				s.erase(it);
				s.insert(newRange);
			} else if (x != it->r) {
				Range newRange(x + 1, it->r);
				s.erase(it);
				s.insert(newRange);
			} else s.erase(it);
		}
	}
	a[pos] = a[pos + n] = val;
}

inline int calc(const int &a, const int &b, const char &opt) {
	return (opt == '+') ? ((a + b) % 10) : (a * b % 10);
}

inline void modify(const int &pos, const int &num, const char &opt) {
	A[pos] = num;
	C[pos] = opt;
	modify(pos, calc(A[pos], A[(pos - 1) < 0 ? (pos - 1 + n) : (pos - 1)], C[pos]));
	modify((pos + 1) < n ? (pos + 1) : (pos + 1 - n), calc(A[(pos + 1) < n ? (pos + 1) : (pos + 1 - n)], A[pos], C[(pos + 1) < n ? (pos + 1) : (pos + 1 - n)]));
}

inline int disc(int x, int y) {
	if (x > y)
		std::swap(x, y);
	return std::min(y - x, n + x - y);
}

inline int dist(int pos, const Range &range) {
	if (range.l == -inf || range.l == inf)
		return -1;
	int _pos = pos < n ? pos : (pos - n);
	if (range.l < n && range.r >= n) {
		if (_pos >= range.l && _pos <= range.r)
			return 0;
		if (_pos + n >= range.l && _pos + n <= range.r)
			return 0;
	}
	if (_pos >= range.l % n && _pos <= range.r % n)
		return 0;
	return std::min(disc(_pos, range.l % n), disc(_pos, range.r % n));
}

inline int query(int pos) {
	static int ans, back;
	back = a[pos];
	modify(pos, A[pos]);
	if (s.size() == 2)
		ans = -1;
	else if (s.size() == 3)
		ans = dist(pos, *++s.begin());
	else {
		static bool flag;
		ans = -1;
		flag = (++s.begin())->l == ((--(--s.end()))->r + 1) % n;
		static int opp;
		opp = ((pos - (n >> 1)) + n) % n;
		static std::set<Range>::iterator oppit;
		oppit = --s.upper_bound(opp);
		if (oppit == s.begin())
			oppit = --s.upper_bound(opp + n);
		else if (flag && (oppit == ++s.begin()))
			oppit = --s.upper_bound(opp + n);
		if (oppit != s.begin() && !(flag && (oppit == ++s.begin() || oppit == --(--s.end()))))
			ans = std::max(ans, dist(pos, *oppit));
		if (oppit != ++s.begin()) {
			static std::set<Range>::iterator pre;
			--(pre = oppit);
			if (!(flag && pre == ++s.begin()))
				ans = std::max(ans, dist(pos, *pre));
		}
		if (oppit != --s.end()) {
			static std::set<Range>::iterator nxt;
			++(nxt = oppit);
			if (!(flag && nxt == --(--s.begin())))
				ans = std::max(ans, dist(pos, *nxt));
		}
	}
	modify(pos, back);
	return ans;
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &::n, &::m);
	for (register int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		do C[i] = getchar_unlocked(); while (C[i] != '+' && C[i] != '*');
	}
	for (register int i = 0; i < n; ++i)
		a[i] = a[i + n] = calc(A[i], A[(i - 1 + n) % n], C[i]);
	for (register int i = 0; i < (n << 1);)
		if (a[i]) ++i;
		else {
			register int j;
			j = i;
			while (j + 1 < (n << 1) && !a[j + 1]) ++j;
			s.insert(Range(i, j));
			i = j + 1;
		}
	s.insert(Range(inf, inf));
	s.insert(Range(-inf, -inf));
	for (int type, pos, num; m; --m) {
		scanf("%d%d", &type, &pos);
		if (type == 1) {
			register char c;
			scanf("%d", &num);
			do c = getchar_unlocked(); while (c != '+' && c != '*');
			modify(pos, num, c);
		} else printf("%d\n", query(pos));
	}
	return 0;
}
