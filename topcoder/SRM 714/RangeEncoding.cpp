#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
class RangeEncoding {
	public:
	int minRanges(vector <int> arr) {
		//sort(arr.begin(), arr.end());

		int ans = 1;
		const int n = arr.size();
		for (int i = 1; i < n; ++i)
			ans += (arr[i] - arr[i - 1]) > 1;
		return ans;

	}
};

// BEGIN CUT HERE

int main() {
	int ANS = RangeEncoding().minRanges(vector<int>({10,11,12,13,14,15,20,21,22,23,25,27,28,29,30,31,32,33}));
	cout << ANS << endl;
	return 0;
}

// END CUT HERE
