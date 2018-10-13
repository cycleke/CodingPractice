#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  bool findTarget(TreeNode* root, int k) {
    queue<TreeNode*> nodes;
    set<int> value_had;
    nodes.push(root);
    while (!nodes.empty()) {
      TreeNode* node = nodes.front();
      nodes.pop();
      if (node == NULL) continue;
      if (value_had.find(k - node->val) != value_had.end())
        return true;
      value_had.insert(node->val);
      nodes.push(node->left);
      nodes.push(node->right);
    }
    return false;
  }
};

#define LOCAL_TEST
#ifdef LOCAL_TEST

int main() {

  TreeNode* root = NULL;
  int k = 0;
  bool answer = Solution().findTarget(root, k);
  cout << answer << endl;
  return 0;
}

#endif
