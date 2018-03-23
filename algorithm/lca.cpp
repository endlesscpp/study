#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
    public:
        /**
         * 如果p, q都是root的字节点，那么返回p, q的最近公共祖先
         * 如果只有单个p或者q是root的字节点，那么返回p或者q
         */
        TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == nullptr) {
                return root;
            }

            if (root == p || root == q) {
                return root;
            }

            TreeNode* l = lowestCommonAncestor1(root->left, p, q);
            TreeNode* r = lowestCommonAncestor1(root->right, p, q);
            if (l != nullptr && r != nullptr) {
                return root;
            } else if (l != nullptr) {
                return l;
            } else if (r != nullptr) {
                return r;
            } else {
                return nullptr;
            }
        }

        struct UFS {
            unordered_map<TreeNode*, TreeNode*> parent;
            TreeNode* find(TreeNode* p) {
                if (p == parent[p]) {
                    return p;
                }
                parent[p] = find(parent[p]);
                return parent[p];
            }

            void add(TreeNode* node, TreeNode* p) {
                parent[node] = p;
            }

            void clear() {
                parent.clear();
            }
        } ufs;

        unordered_set<TreeNode*> visited;


        TreeNode* dfs(TreeNode* root, TreeNode* rp, TreeNode* p, TreeNode* q) {
            if (root == nullptr) {
                return nullptr;
            }

            ufs.add(root, root);

            TreeNode* lca;
            lca = dfs(root->left, root, p, q);
            if (lca != nullptr) {
                return lca;
            }
            lca = dfs(root->right, root, p, q);
            if (lca != nullptr) {
                return lca;
            }

            if (root == p) {
                if (visited.find(q) != visited.end()) {
                    return ufs.find(q);;
                }
            } 

            if (root == q) {
                if (visited.find(p) != visited.end()) {
                    return ufs.find(p);
                }
            }
            
            visited.insert(root);
            ufs.add(root, rp);
            return nullptr;
        }

       TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == nullptr) {
                return nullptr;
            }

            ufs.add(root, root);

            TreeNode* lca;
            lca = dfs(root->left, p, q);
            if (lca != nullptr) {
                return lca;
            }
            if (root->left != nullptr) {
                ufs.add(root->left, root);
            }

            lca = dfs(root->right, p, q);
            if (lca != nullptr) {
                return lca;
            }
            if (root->right != nullptr) {
                ufs.add(root->right, root);
            }

            if (root == p) {
                if (visited.find(q) != visited.end()) {
                    return ufs.find(q);;
                }
            } 

            if (root == q) {
                if (visited.find(p) != visited.end()) {
                    return ufs.find(p);
                }
            }
            
            visited.insert(root);
            return nullptr;
        }

        /**
         * dfs + union-set
         */
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            ufs.clear();
            visited.clear();
            return dfs(root, p, q);
        }
};


int main() {
    TreeNode* p = new TreeNode(0);
    TreeNode* root = p;
    TreeNode* a;
    TreeNode* b;

    for (int i = 1; i < 10000; i++) {
        p->right = new TreeNode(i);
        p = p->right;
        if (i == 9999) {
            a = p;
        } else if (i == 9998) {
            b = p;
        }
    }

    Solution s;
    TreeNode* lca = s.lowestCommonAncestor(root, a, b);
    if (lca != nullptr) {
        cout << "found lca, val = " << lca->val << endl;
    }

    return 0;
}
