/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  int countNodes(TreeNode* root) {
    if (root == NULL) return 0;
    int h = getHeight(root);
    int l = 0, r = (1 << (h - 1)) - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (isEnough(root, m, h - 1)) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    return (1 << (h - 1)) + r;
  }
private:
  int getHeight(TreeNode* u) {
    if (u == NULL) return 0;
    return 1 + getHeight(u->left);
  }
  bool isEnough(TreeNode* root, int size, int depth) {
    TreeNode* u = root;
    for (int i = depth; i > 0; i--) {
      if (u == NULL) return false;
      if (size >> (i - 1) & 1) {
        u = u->right;
      } else {
        u = u->left;
      }
    }
    return u == NULL ? false : true;
  }
};
