// 二叉树的遍历

// 1.深搜（DFS）——中序，前序，后序都是深搜
// 前序
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";   // 访问根
    preorder(root->left);
    preorder(root->right);
}
// 2.广搜（BFS）——层序遍历
// 基础模版
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";   // 访问根
    preorder(root->left);
    preorder(root->right);
}
// 按层分组
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();        // 当前层的节点数
        vector<int> level;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}
