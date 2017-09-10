#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

class RepeatedStrings {
private:
	bool issubstring(const string &a, const string &b) {
		int it = 0;
		for (int i = 0; i < (int)b.size(); ++i)
			if (a[it] == b[i] && ++it >= a.size())
				return true;
		return false;
	}
public:
	string findKth(string s, int k) {
		vector<string> G;
		G.push_back("()");
		for (int i = 0; i < (int)G.size(); ++i) {
			for (string t = G[i]; t.size() <= s.size(); t += G[i])
				G.push_back("(" + t + ")");
		}
		sort(G.begin(), G.end());
		G.erase(unique(G.begin(), G.end()), G.end());
		for (int i = 0; i < (int)G.size(); ++i)
			if (issubstring(G[i], s) && --k == 0)
				return G[i];
		return "";
	}
};
