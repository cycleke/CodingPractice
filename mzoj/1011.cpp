#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
typedef map<string, int>::iterator mpt;
typedef pair<int, int>pii;
bool vis[N];
int to[N << 1], nxt[N << 1], totE;
map<string, int>G[2];
vector<pii>Ans;
string Sch[N], Car[N];
mpt addit;

#define mk make_pair
#define pb push_back

void Adde(const string &S, const int &u, const bool &type) {
	addit = G[type].find(S);
	if (addit == G[type].end()) { G[type][S] = -1; addit = G[type].find(S); }
	to[totE] = u; nxt[totE] = addit->second; addit->second = totE++;
}

int dfs(int &u, bool fa) {
	vis[u] = true;
	int lss = 0, rss = 0, ls, rs;
	for (int &i = G[0][Sch[u]]; ~i; i = nxt[i])
	if (!vis[to[i]]) {
		ls = to[i];
		lss = dfs(ls, 0); break;
	}
	for (int &i = G[1][Car[u]]; ~i; i = nxt[i])
	if (!vis[to[i]]) {
		rs = to[i];
		rss = dfs(rs, 1); break;
	}
	if (lss ^ rss) {
		if (lss) Ans.pb(mk(u, ls));
		else Ans.pb(mk(u, rs));
		return 0;
	}
	if (lss & rss) {
		if (fa) { Ans.pb(mk(u, ls)); u = rs; }
		else { Ans.pb(mk(u, rs)); u = ls; }
	}
	return 1;
}

int main() {
	int n, i, re, t;
	cin >> n;
	G[0].clear(); G[1].clear(); Ans.clear();
	for (i = 1; i <= n; ++i) {
		cin >> Sch[i] >> Car[i];
		Adde(Sch[i], i, 0); Adde(Car[i], i, 1);
	}
	for (i = 1; i <= n; ++i) if (!vis[i]) {
		t = i; re = dfs(t, 1);
		if (re) Ans.pb(mk(t, 0));
	}
	cout << Ans.size() << endl;
	for (i = 0; i < Ans.size(); ++i) cout << Ans[i].first << ' ' << Ans[i].second << endl;
	return 0;
}

