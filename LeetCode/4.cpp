#include <vector>
using namespace std;

class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    if (n == 0) {
      return (m % 2 == 0) ?
        (double(nums2[m / 2]) + double(nums2[m / 2] - 1)) / 2 :
        double(nums2[m / 2]);
    }
    if (m == 0) {
      return (n % 2 == 0) ?
        (double(nums1[n / 2]) + double(nums1[n / 2] - 1)) / 2 :
        double(nums1[n / 2]);
    }
    auto f = [&](int target) {
      int left = min(nums1[0], nums2[0]);
      int right = max(nums1.back(), nums2.back());
      int answer = left;
      while (left <= right) {
        int middle = (left + right) / 2;
        int _n = lower_bound(nums1.begin(), nums1.end(), middle) - nums1.begin();
        int _m = lower_bound(nums2.begin(), nums2.end(), middle) - nums2.begin();
        if (_n + _m <= target) {
          answer = middle;
          left = middle + 1;
        } else {
          right = middle - 1;
        }
      }
      return double(answer);
    };
    if ((n + m) % 2 == 0)
      return (f((n + m) / 2) + f((n + m) / 2 - 1)) / 2;
    else
      return f((n + m - 1) / 2);
  }
};

#define LOCAL_TEST
#ifdef LOCAL_TEST

#include <bits/stdc++.h>
using namespace std;

void trimLeftTrailingSpaces(string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
      }));
}

void trimRightTrailingSpaces(string &input) {
  input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
      }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
  vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

int main() {
  string line;
  while (getline(cin, line)) {
    vector<int> nums1 = stringToIntegerVector(line);
    getline(cin, line);
    vector<int> nums2 = stringToIntegerVector(line);

    double ret = Solution().findMedianSortedArrays(nums1, nums2);

    string out = to_string(ret);
    cout << out << endl;
  }
  return 0;
}

#endif
