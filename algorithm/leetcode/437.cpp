//
// 437 - path sum III
//

#include <unordered_map>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> mpSumCnt;
        int cnt = 0;
        int base = 0;
        traverse(root, sum, base, mpSumCnt, cnt);       
        return cnt;
    }

    //
    // @base - the base of mpSumCnt's key. it->first really means (base + it->first)
    //
    void traverse(TreeNode* root, int sum, int base, unordered_map<int, int>& mpSumCnt, int& cnt) {
        if (root == nullptr) {
            return;
        }
        
        base = base + root->val;
        mpSumCnt[root->val - base] += 1;

        cnt += mpSumCnt[sum - base];

        traverse(root->left, sum, base, mpSumCnt, cnt);
        traverse(root->right, sum, base, mpSumCnt, cnt);

        mpSumCnt[root->val - base] -= 1;
    }
};

//
// Below is a more intuitive one
//

/*
The idea is simple: along the path, record all prefix sums in a hash table. For current prefix sum x, check if (x - target) appears in the hash table.

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> m;
        m[0]++;
        
        int total = 0;
        helper(root, 0, sum, total, m);
        return total;
    }
    
    void helper(TreeNode *p, int cur, int sum, int &total, unordered_map<int, int> &m) {
        if (!p) return;
        
        cur += p->val;
        if (m.find(cur - sum) != m.end()) total += m[cur - sum];
        m[cur]++;
        
        helper(p->left, cur, sum, total, m);
        helper(p->right, cur, sum, total, m);
        
        m[cur]--;
    }
};
*/
