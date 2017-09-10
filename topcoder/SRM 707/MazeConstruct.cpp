#include <bits/stdc++.h>
using namespace std;
class MazeConstruct {
	public:
	vector <string> construct(int k) {
		if (k < 50) {
			vector<string> ret;
			ret.push_back(string(k + 1, '.'));
			return ret;
		} else if (k < 99) {
			vector<string> ret;
			string S(50, '.');
			k -= 48;
			for (int i = 0; i < k; ++i)
				ret.push_back(S);
			return ret;
		} else {
			vector<string> ret;
			string S(50, '.');
			for (int i = 0; i < 50 - (k & 1); ++i)
				ret.push_back(S);
			k = (k - 48 - 50 + (k & 1)) >> 1;
			for (int i = 1; k; i += 2) {
				if ((i & 3) == 1) {
					for (int j = 0; j < 49; ++j)
						ret[i][j] = '#';
				} else {
					for (int j = 49; j && k; --j, --k)
						ret[i][j] = '#';
				}
			}
			return ret;
		}
	}
};
