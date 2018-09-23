#include <iostream>
#include <map>
#include <string>
#include <queue>
using namespace std;


int main() {

  ios::sync_with_stdio(false);
  cin.tie(0);

  map<string, int> num;
  num["one"] = 1;
  num["two"] = 2;
  num["three"] = 3;
  num["four"] = 4;
  num["five"] = 5;
  num["six"] = 6;
  num["seven"] = 7;
  num["eight"] = 8;
  num["nine"] = 9;
  num["ten"] = 10;
  num["eleven"] = 11;
  num["twelve"] = 12;
  num["thirteen"] = 13;
  num["fourteen"] = 14;
  num["fifteen"] = 15;
  num["sixteen"] = 16;
  num["seventeen"] = 17;
  num["eighteen"] = 18;
  num["nineteen"] = 19;
  num["twenty"] = 20;
  num["a"] = 1;
  num["both"] = 2;
  num["another"] = 3;
  num["first"] = 1;
  num["second"] = 2;
  num["third"] = 3;

  priority_queue<int, vector<int>, greater<int> > heap;
  for (int i = 0; i < 6; i++) {
    string s;
    cin >> s;
    if (s.back() == '.') s = s.substr(0, s.length() - 1);
    if (num.find(s) == num.end()) continue;
    heap.push(num[s] * num[s] % 100);
  }

  bool zero = true;

  cout.fill('0');
  while (!heap.empty()) {
    int a = heap.top();
    heap.pop();
    if (zero) {
      if (a != 0) {
        zero = false;
        cout << a;
      }
    } else {
      cout.width(2);
      cout << a;
    }
  }
  if (zero) cout << 0;
  return 0;
}
