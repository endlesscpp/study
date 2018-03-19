#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
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
