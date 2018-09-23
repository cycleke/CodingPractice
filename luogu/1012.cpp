#include <algorithm>
#include <iostream>
#include <string>

std::string num[20];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> num[i];
  }
  std::sort(num, num + n,
            [&](const std::string &a, const std::string &b) {
              return a + b > b + a;
            });
  for (int i = 0; i < n; i++) {
    std::cout << num[i];
  }
  return 0;
}
