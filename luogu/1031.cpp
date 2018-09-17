#include <vector>
#include <map>
#include <iostream>

int a[100];

int main() {
	int n, sum = 0;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		sum += a[i];
	}
	int pre_heap = sum / n;
	for (int i = 0; i < n; i++) {
		a[i] -= pre_heap;
	}
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0) continue;
		a[i + 1] += a[i];
		count++;
	}
	std::cout << count << std::endl;
	return 0;
}