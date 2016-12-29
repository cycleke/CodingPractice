#include <cstdio>
#include <algorithm>
using namespace std;

struct data {
	int l, r;
	bool operator < (const data &a) const {
		if (l == a.l) return r > a.r;
		return l < a.l;
	}
	void Read() {
		scanf("%d%d", &l, &r);
	}
	data(int a = 0, int b = 0) : l(a), r(b) {}
};

data Cow[25010];

int main() {
	int N, T, ans = 0, head = 1,tail = -1;
	scanf("%d%d", &N, &T);
	for (int i = 1; i <= N; ++i) Cow[i].Read();
	sort(Cow + 1, Cow + N + 1);
	for (int i = 1; i <= N; ++i) {
		if (Cow[i].l > head) {
			if (!~tail) {
				puts("-1"); return 0;
			}
			head = tail + 1; ++ans; tail = -1;
			if (head > T) {
				printf("%d\n", ans); return 0;
			}
			--i; continue;
		}	
		if (Cow[i].r > tail) tail = Cow[i].r;
	}
	
	if (!~tail) {
		puts("-1"); 
	} else {
		head = tail + 1; ++ans; 
		
		if (head > T) {
			printf("%d\n", ans); 
		} else {
			puts("-1");
		}
	}
	
	return 0;
}
