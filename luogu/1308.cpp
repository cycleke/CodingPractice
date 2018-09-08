#include <iostream>
#include <string>
using namespace std;

int main() {
  string a, b;
  getline(cin, a);
  getline(cin, b);
  for (auto &ch : a) ch = tolower(ch);
  for (auto &ch : b) ch = tolower(ch);
  a = ' ' + a + ' ';
  b = ' ' + b + ' ';
  if (b.find(a) == string::npos) {
    cout << -1 << endl;
  } else {
    int count = 0, p;
    auto it = b.find(a);
    p = it;
    while (it != string::npos) {
      count++;
      it = b.find(a, it + 1);
    }
    cout << count << " " << p << endl;
  }
  return 0;
}
