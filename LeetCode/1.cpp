#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++) {
        if (nums[i] + nums[j] == target) {
          return vector<int>({i, j});
        }
      }
    return vector<int>();
  }
};

//Local Test

int main() {
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;
  vector<int> answer = Solution().twoSum(nums, target);
  for (int x : answer) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
