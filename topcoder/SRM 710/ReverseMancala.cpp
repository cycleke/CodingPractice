#include <string>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector <int> vii;

class ReverseMancala {

protected:

	vii to_zero(vii &x, bool tag) {
		vii ans;
		const int n = x.size();
		int sum = accumulate(x.begin(), x.end(), 0);
		while (x[0] != sum) {
			int p = 1;
			while (!x[p]) ++p;
			if (tag) ans.push_back((p + x[p]) % n + n);
			else ans.push_back(p);

			int cur = x[p];
			x[p] = 0;
			p = (p + 1) % n;

			while (cur--) ++x[p], p = (p + 1) % n;
		}
		return ans;
	}

public:
	vii findMoves(vii start, vii target) {
		vii a = to_zero(start, 0);
		vii b = to_zero(target, 1);
		reverse(b.begin(), b.end());
		a.insert(a.end(), b.begin(), b.end());
		return a;
	}
};

// BEGIN CUT HERE

int main() {

	vector <int> start({6, 3, 4, 0}), target({1, 5, 6, 1});

	vector <int> ANS = ReverseMancala().findMoves(start, target);

	for (int x : ANS) cout << x << ' ';
	cout << endl;

	return 0;
}

// END CUT HERE
