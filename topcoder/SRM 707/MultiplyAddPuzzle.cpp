#include <bits/stdc++.h>
using namespace std;
class MultiplyAddPuzzle {
	public:
	long long minimalSteps(long long s, long long t, long long a, long long b) {
		if (s == t)
			return 0;
		if (a == 0) {
			for (int i = 0; i < 100; ++i) {
				if (s == t)
					return i;
				s *= b;
			}
			return -1LL;
		}
		if (b <= 1) {
			if (t == 0 && b == 0)
				return 1LL;
			if (s < t && (t - s) % a == 0)
					return (t - s) / a;
			if (b == 0 && t % a == 0)
				return 1LL + t / a;
			return -1LL;
		}
		long long ret = 1LL << 60, pre, sum, tmp;
		int Multime = 0, i;
		while (s <= t) {
			if ((t - s) % a == 0) {
				pre = (t - s) / a;
				sum = pre;
				for (i = 1; i <= Multime; ++i) {
					tmp = pre / b;
					sum -= pre;
					sum += pre - tmp * b + tmp;
					pre = tmp;
				}
				sum += Multime;
				if (sum < ret)
					ret = sum;
			}
			if (++Multime > 100)
				break;
			s *= b;
		}
		if (ret >> 60)
			ret = -1;
		return ret;
	}
};
