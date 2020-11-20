#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<long long> vll;

// const int MOD = 1e9 + 7;
mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

bool Query(int a, int b, int c) {
  static map<tiii, bool> store;
  auto t = tiii(a, b, c);
  if (store.find(t) != store.end()) {
    return store[t];
  } else {
    cout << "? " << a << " " << b << " " << c << endl;
    cout.flush();
    string s;
    cin >> s;
    store[t] = s == "Yes";
    store[tiii(c, b, a)] = store[t];
    return store[t];
  }
}

void Answer(int root) { cout << "! " << root << endl; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, k;
  cin >> n >> k;
  if (n == 1) {
    Answer(1);
  } else {
    int cur = k;
    int nodes = 1;
    int dep = 0;
    while (nodes + cur <= n) {
      nodes += cur;
      cur *= k;
      dep++;
    }
    // cerr << dep << endl;
    int a[n];
    for (int i = 0; i < n; i++) {
      a[i] = i + 1;
    }

    int leaf1, leaf2;

    // Find leaf1;
    while (true) {
      shuffle(a, a + n, rdm);
      int leaf = a[0];
      int random = a[1];
      bool flag = true;
      for (int i = 2; i < n; i++) {
        flag &= !Query(a[i], leaf, random);
        if (!flag)
          break;
      }
      if (flag) {
        leaf1 = leaf;
        break;
      }
    }

    // cerr << "#";
    // Find leaf2;
    vi v;
    while (true) {
      shuffle(a, a + n, rdm);
      if (a[0] == leaf1)
        continue;
      int leaf = a[0];
      // cerr << leaf;
      int cnt = 0;
      int rqd = 2 * (dep - 1) + 1;
      v.clear();
      for (int i = 1; i < n; i++) {
        if (a[i] == leaf1)
          continue;
        bool sign = Query(leaf1, a[i], leaf);
        if (sign) {
          cnt++;
          v.push_back(a[i]);
        }
      }
      if (cnt == rqd) {
        leaf2 = leaf;
        break;
      }
    }

    // cerr << "#";
    // Find root;
    vi path({leaf1, v[0], leaf2});
    for (int i = 1; i < int(v.size()); i++) {
      vi newpath;
      newpath.push_back(path[0]);
      for (int j = 1; j < int(path.size()); j++) {
        if (Query(path[j - 1], v[i], path[j])) {
          newpath.push_back(v[i]);
          for (int k = j; k < int(path.size()); k++) {
            newpath.push_back(path[k]);
          }
          break;
        } else {
          newpath.push_back(path[j]);
        }
      }
      path = newpath;
    }
    Answer(path[dep]);
  }
  return 0;
}
