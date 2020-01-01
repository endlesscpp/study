#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Solution1 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> counts(nums.size(), 0); 
        map<int, int> f;

        for (int v: nums) {
            f[v] = f[v] + 1;
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            int v = nums[i];
            for (auto& p : f) {
                if (p.first < v) {
                    counts[i] += p.second;
                } else {
                    break;
                }
            }
            f[v] = f[v] - 1;
        }

        return counts;
    }
};

/**
 * 使用自定义的Binary Search Tree
 * 每个节点保存其左子树中的节点个数leftsum，以及该节点数值的重复次数dup
 * 查询时，如果向右走，说明当前节点的值小，ans += (leftsum+dup)，如果找到
 * 的节点存在，再加上该节点的leftsum.
 */
class Solution {
private:
    struct Node {
        Node(int v) {
            left = nullptr;
            right = nullptr;
            val = v;
            leftsum = 0;
            dup = 1;
        }
        struct Node* left;
        struct Node* right;
        int val;
        int leftsum;
        int dup;
    };

public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);

        Node* root = nullptr;
        for (int i = nums.size()-1; i >= 0; i--) {
            int val = nums[i];
            if (root == nullptr) {
                root = new Node(val);
                ans[i] = 0;
                continue;
            }

            int leftsum = 0;
            Node* p = root;
            while (p != nullptr) {
                if (val < p->val) {
                    p->leftsum++;
                    if (p->left != nullptr) {
                        p = p->left;
                    } else {
                        p->left = new Node(val);
                        break;
                    }
                } else if (val > p->val) {
                    leftsum += (p->leftsum + p->dup);
                    if (p->right != nullptr) {
                        p = p->right;
                    } else {
                        p->right = new Node(val);
                        break;
                    }
                } else {
                    p->dup++;
                    leftsum += p->leftsum; 
                    break;
                }
            }

            ans[i] = leftsum;
        }

        return ans;
    }
};

int main() {
    vector<int> v  = {5, 2, 6, 1};
    Solution s;
    vector<int> ans = s.countSmaller(v);
    for (auto i : ans) {
        cout << i << ", ";
    }
    cout << endl;
    return 0;
}
