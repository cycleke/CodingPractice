#include <bits/stdc++.h>
using namespace std;

#define BinarySearch(LEFT, RIGHT, LEFT_VALUE, RIGHT_VALUE, RESULT_RETURN) {	\
		register int left = LEFT, right = RIGHT;														\
		while (left <= right) {																							\
			register int middle = (left + right) / 2;													\
			if ((LEFT_VALUE) > (RIGHT_VALUE)) {																\
				right = middle - 1;																							\
			} else {																													\
				RESULT_RETURN = middle;																					\
				left = middle + 1;																							\
			}																																	\
		}																																		\
	}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	long long r;
	cin >> n >> m >> r;
	if (n > m) swap(n, m);

	auto excl = [&](long long L, long long R) {
								if (L * R > 2e9 + 5) return r + 1ll;
								else return L * R * (L * R - 1ll) / 2 - L * (R - 1) - (L  - 1) * R;
							};

	int x = n, y = m, res = 0;
	BinarySearch(1, n, excl(middle, middle), r, x);
	BinarySearch(x, m, excl(x, middle), r, y);
	r -= excl(x, y);
	BinarySearch(1, x, excl(1, middle) + 1ll * middle * x * y - middle, r, res);
	cout <<  min(1ll * n * m ,1ll * x * y + res) << endl;
	return 0;
}
