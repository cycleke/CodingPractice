#include <bits/stdc++.h>
using namespace std;
#define N 100003
#define base 1000003
set<int> PX[N], PY[N];
int mpx[base<<1|1], mpy[base<<1|1];
pair<int, int> a[N];
bool cmpy(const pair<int, int> &a, const pair<int, int> &b) {
	return a.second < b.second;
}

#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline void gi(int &ina) {
	static char inc,inb[1<<16],*ine=inb,*ins=inb, flag;
	flag = 0;
    while((inc=getc())<'0')flag|=inc=='-'; ina=inc-'0';
    while((inc=getc())>'-') ina=(ina<<3)+(ina<<1)+inc-'0';
	if(flag)ina=-ina;
}
int main() {
	int n, i, x, y, m, _x, _y, tx, ty;
	set<int>::iterator r, d;
	//scanf("%d", &n);
	gi(n);
	for (i = 0; i < n; ++i) {
		//scanf("%d%d", &x, &y);
		gi(x); gi(y);
		a[i] = pair<int, int>(x, y);
	}
	sort(a, a + n, cmpy);
	m = 0;
	PY[m].insert(a->first);
	mpy[a->second + base] = 0;
	for (i = 1; i < n; ++i) {
		if (a[i].second ^ a[i - 1].second)
			mpy[a[i].second + base] = ++m;
		PY[m].insert(a[i].first);
	}
	sort(a, a + n);
	m = 0;
	PX[m].insert(a->second);
	mpx[a->first + base] = 0;
	for (i = 1; i < n; ++i) {
		if (a[i].first ^ a[i - 1].first)
			mpx[a[i].first + base] = ++m;
		PX[m].insert(a[i].second);
	}
	m = 0;
	for (i = 0; i < n; ++i) {
		x = a[i].first, y = a[i].second;
		_x = mpx[x + base], _y = mpy[y + base];
		r = PX[_x].upper_bound(y);
		d = PY[_y].upper_bound(x);
		while (r != PX[_x].end() && d != PY[_y].end()) {
			tx = *d, ty = *r;
			while (r != PX[_x].end() && *r - y < *d - x)
				++r;
			while (d != PY[_y].end() && *d - x < *r - y)
				++d;
			if ((r == PX[_x].end()) || (d == PY[_y].end()) || ((*r - y) ^ (*d - x))) continue;
			if (PX[mpx[*d + base]].find(*r) != PX[mpx[*d + base]].end()) ++m;
			++d, ++r;
		}
		
	}
	printf("%d\n", m);
	return 0;
}
