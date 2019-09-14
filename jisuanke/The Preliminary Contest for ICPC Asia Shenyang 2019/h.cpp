// by OwenCreeper
#include "bits/stdc++.h"
#define N 100000
#define MOD 1000000007
using namespace std;
typedef long long ll;
inline int read() {
	int num = 0, k = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') k = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') num *= 10, num += ch - 48, ch = getchar();
	return num * k;
}
struct point {
	char nm[11];
	int s[6], sm, tp;
} p[N + 5];
int cnt[14], cc[5], num[N + 5], n;
char s[30];
int analyze(char *s, int k) {
	int len = strlen(s);
	memset(cnt, 0, sizeof(cnt));
	memset(cc, 0, sizeof(cc));
	int pc = 0;
	p[k].sm = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			if (s[i] == '1')
				cnt[10]++, p[k].s[++pc] = 10, i++;
			else
				cnt[s[i] - 48]++, p[k].s[++pc] = s[i] - 48;
		} else 
			if (s[i] == 'A')
				cnt[1]++, p[k].s[++pc] = 1;
			else
				if (s[i] == 'J')
					cnt[11]++, p[k].s[++pc] = 11;
				else
					if (s[i] == 'Q')
						cnt[12]++, p[k].s[++pc] = 12;
					else
						if (s[i] == 'K')
							cnt[13]++, p[k].s[++pc] = 13;
	}
	sort(p[k].s + 1, p[k].s + 1 + 5);
	for (int i = 1; i <= 13; i++) p[k].sm += i * cnt[i], cc[cnt[i]]++;
	if (p[k].s[1] == 1 && p[k].s[2] == 10 && p[k].s[3] == 11 && p[k].s[4] == 12 && p[k].s[5] == 13) return p[k].tp = 8, 1;
	for (int i = 13; i >= 5; i--) 
		if (cnt[i] && cnt[i - 1] && cnt[i - 2] && cnt[i - 3] && cnt[i - 4])
			return p[k].tp = 7, 1;
	if (cc[4]) return p[k].tp = 6, 1;
	if (cc[3] && cc[2]) return p[k].tp = 5, 1;
	if (cc[3]) return p[k].tp = 4, 1;
	if (cc[2] == 2) return p[k].tp = 3, 1;
	if (cc[2]) return p[k].tp = 2, 1;
	return p[k].tp = 1, 1;
}
bool cp(char *s1, char *s2) {
	for (int i = 0; i < strlen(s1); i++)
		if (s1[i] != s2[i])
			return s1[i] < s2[i];
	return 1;
}
bool cmp(int x, int y) {
	if (p[x].tp != p[y].tp) return p[x].tp > p[y].tp;
	if (p[x].tp == 8) return cp(p[x].nm, p[y].nm);
	if (p[x].tp == 1) {
		if (p[x].sm != p[y].sm) return p[x].sm > p[y].sm;
		return cp(p[x].nm, p[y].nm);
	}
	int bx = 0, by = 0, bx0, by0;
	if (p[x].tp == 2) {
		for (int i = 2; i <= 5; i++)
			if (p[x].s[i] == p[x].s[i - 1])
				bx = p[x].s[i];
		for (int i = 2; i <= 5; i++)
			if (p[y].s[i] == p[y].s[i - 1])
				by = p[y].s[i];
		if (bx != by) return bx > by; 
		if (p[x].sm - bx * 2 != p[y].sm - by * 2) return p[x].sm - bx * 2 > p[y].sm - by * 2;
		return cp(p[x].nm, p[y].nm);
	}
	if (p[x].tp == 3) {
		for (int i = 5; i >= 2; i--)
			if (p[x].s[i] == p[x].s[i - 1]) 
				if (!bx) bx = p[x].s[i]; else bx0 = p[x].s[i];
		for (int i = 5; i >= 2; i--)
			if (p[y].s[i] == p[y].s[i - 1]) 
				if (!by) by = p[y].s[i]; else by0 = p[y].s[i];
		if (bx != by) return bx > by;
		if (bx0 != by0) return bx0 > by0;
		if (p[x].sm - bx * 2 - bx0 * 2 != p[y].sm - by * 2 - by0 * 2) return p[x].sm - bx * 2 - bx0 * 2 > p[y].sm - by * 2 - by0 * 2;
		return cp(p[x].nm, p[y].nm);
	}
	if (p[x].tp == 4) {
		for (int i = 5; i >= 3; i--)
			if (p[x].s[i] == p[x].s[i - 1] && p[x].s[i - 1] == p[x].s[i - 2])
				bx = p[x].s[i];
		for (int i = 5; i >= 3; i--)
			if (p[y].s[i] == p[y].s[i - 1] && p[y].s[i - 1] == p[y].s[i - 2])
				by = p[y].s[i];
		if (bx != by) return bx > by;
		if (p[x].sm - bx * 3 != p[y].sm - by * 3) return p[x].sm - bx * 3 > p[y].sm - by * 3;
		return cp(p[x].nm, p[y].nm);
	}
	if (p[x].tp == 5) {
		for (int i = 5; i >= 3; i--)
			if (p[x].s[i] == p[x].s[i - 1] && p[x].s[i - 1] == p[x].s[i - 2])
				bx = p[x].s[i];
		for (int i = 5; i >= 3; i--)
			if (p[y].s[i] == p[y].s[i - 1] && p[y].s[i - 1] == p[y].s[i - 2])
				by = p[y].s[i];
		if (bx != by) return bx > by;
		for (int i = 5; i >= 2; i--)
			if (p[x].s[i] == p[x].s[i - 1] && p[x].s[i] != bx) 
				bx0 = p[x].s[i];
		for (int i = 5; i >= 2; i--)
			if (p[y].s[i] == p[y].s[i - 1] && p[y].s[i] != by) 
				by0 = p[y].s[i];
		if (bx0 != by0) return bx0 > by0;
		if (p[x].sm - bx * 3 - bx0 * 2 != p[y].sm - by * 3 - by0 * 2) 
			return p[x].sm - bx * 3 - bx0 * 2 > p[y].sm - by * 3 - by0 * 2;
		return cp(p[x].nm, p[y].nm);
	}
	if (p[x].tp == 6) {
		if (p[x].s[1] == p[x].s[2]) bx = p[x].s[1]; else bx = p[x].s[2];
		if (p[y].s[1] == p[y].s[2]) by = p[y].s[1]; else by = p[y].s[2];
		if (bx != by) return bx > by;
		if (p[x].sm - bx * 4 != p[y].sm - by * 4) return p[x].sm - bx * 4 > p[y].sm - by * 4;
		return cp(p[x].nm, p[y].nm);
	}
	if (p[x].tp == 7) {
		if (p[x].sm != p[y].sm) return p[x].sm > p[y].sm;
		return cp(p[x].nm, p[y].nm);
	}
	return 1;
}
void work() {
	for (int i = 1; i <= n; i++) {
		scanf("%s", p[i].nm);
		scanf("%s", s);
		analyze(s, i);
		num[i] = i;
	}
	sort(num + 1, num + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
		printf("%s\n", p[num[i]].nm);
}
int main(int argc, char const *argv[]) {
	while (scanf("%d", &n) != EOF) work();
	return 0;
}
