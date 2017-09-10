#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

class MagicNim {
	public:
	string findWinner(vector <int> a) {
		int nim = 0, mx = -1;
		for (int x : a) nim ^= x, (mx < x) ? mx = x : 0;
		return (nim == (2 - (mx > 3))) ? "Bob" : "Alice";
	}
};

// BEGIN CUT HERE

int main() {

	cout << MagicNim().findWinner(vector<int>({4, 4, 2})) << endl;

	return 0;
}

// END CUT HERE
