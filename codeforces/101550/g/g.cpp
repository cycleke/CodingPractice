#include "bits/stdc++.h"
#define N 1000000
using namespace std;
int st[N + 5], Rank, Star, ls = 0;
char s[N + 5];
void ps() {
	if (!Rank) return ;
	Star++;
	if (st[Rank] < Star) Rank--, Star = 1;
}
void ds() {
	if (Rank >= 21 || !Rank) return ;
	Star--;
	if (Star < 0) {
		if (Rank < 20) Rank++, Star = st[Rank] - 1; 
		else Star = 0;
	}
}
int main(int argc, char const *argv[]) {
	scanf("%s", s);
	for (int i = 1; i <= 10; i++) st[i] = 5;
	for (int i = 11; i <= 15; i++) st[i] = 4;
	for (int i = 16; i <= 20; i++) st[i] = 3;
	for (int i = 21; i <= 25; i++) st[i] = 2;
	Rank = 25, Star = 0;
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == 'W') {
			ls++;
			if (ls >= 3 && Rank >= 6 && Rank <= 25) ps();
			ps();
		} else ls = 0, ds();
	if (Rank) printf("%d\n", Rank); else puts("Legend");
	return 0;
}
