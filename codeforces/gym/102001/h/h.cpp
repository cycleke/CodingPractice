// by OwenCreeper
#include "bits/stdc++.h"
#define inf 1e9
#define N 1000000
#define MAX 32768
using namespace std;
struct pq {
	priority_queue <int> A, B;
	void clear() { while (!A.empty()) A.pop(); while (!B.empty()) B.pop(); }
	void push(int x) { A.push(-x); }
	void erase(int x) { B.push(-x); }
	int top() {
		while (!A.empty() && !B.empty() && A.top() == B.top()) A.pop(), B.pop();
		if (A.empty()) return inf;
		return -A.top();
	}
	bool empty() { return top() >= inf; }
	void print() {
		priority_queue <int> tp;
		while (!tp.empty()) tp.pop();
		while (!empty()) {
			int x = top();
			tp.push(x), printf("%d ", x), erase(x);
		}
		puts("");
		while (!tp.empty()) push(tp.top()), tp.pop();
	}
} Que;
int p[N + 5], pp[N + 5], sm[N + 5], s[N + 5], a[N + 5], b[N + 5], c[N + 5], res[N + 5], n, k;
vector <int> V[N + 5], G[N + 5];
int main(int argc, char const *argv[]) {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", p + i);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d%d", a + i, b + i, c + i);
		V[a[i]].push_back(i), G[b[i] + 1].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		if (p[i] == 0)
			s[i] = 1; 
		else
			s[i] = p[i];
		sm[i] = sm[i - 1] + s[i];
	}
	Que.clear();
	for (int i = 1; i <= k; i++) {
		res[i] = sm[b[i]] - sm[a[i] - 1] - c[i];
		if (res[i] < 0) {
			puts("Impossible");
			exit(0);
		}
	}
	for (int i = 1, tot = 0; i <= n; i++) {
		for (int j = 0; j < G[i].size(); j++)
			Que.erase(pp[G[i][j]]);
		for (int j = 0; j < V[i].size(); j++)
			Que.push(pp[V[i][j]] = res[V[i][j]] + tot);
		if (p[i] == 0 && Que.top() - tot >= 2)
			tot += 2, s[i] = -1;
		// Que.print();
	}
	for (int i = 1; i <= n; i++) printf("%d ", s[i]); puts("");
	return 0;
}
