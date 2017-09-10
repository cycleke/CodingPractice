#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
class Saleswoman {
public:
	int minMoves(vector <int> pos, vector <int> delta) {
		const int n = pos.size();
		int need = 0, own = 0, ans = pos[n - 1];
		for (int i = 0; i < n; ++i) {
			if (delta[i] > 0)
				own += delta[i];
			else if (own + delta[i] < 0)
				need -= delta[i];
			else {
				own += delta[i];
				delta[i] = 0;
			}
			if (own >= need && need) {
				for (int j = i; ~j; --j)
					if (delta[j] < 0) {
						own += delta[j];
						need += delta[j];
						delta[j] = 0;
						if (need == 0) {
							ans += (pos[i] - pos[j]) * 2;
							break;
						}
					}
			}
		}
		return ans;
	}
};

// BEGIN CUT HERE

int main() {
	cout << ANS << endl;
	return 0;
}

// END CUT HERE
