/**
 * Burst balloons
 * 以最后一个破掉的点为分解点，把所有的点分为两部分，进行分治
 */

#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

/**
 * Solution 1: use memorized
 */
class Solution1 {
private:
public:
    int maxCoins(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        vector<int> v;
        v.reserve(nums.size());
        v.push_back(1);
        for(int val: nums) {
            if (val > 0) {
                v.push_back(val);
            }
        }
        v.push_back(1);
        int* cache = new int[v.size() * v.size()];
        memset(cache, 0, v.size()*v.size()*sizeof(int));
        int ans = calc(cache, v.size(), v, 0, (int)v.size()-1);
        delete[] cache;
        return ans;
    }
private:
    /**
     * calc the max score in (left, right)
     */
    int calc(int* cache, int cols, vector<int>& nums, int left, int right) {
        if (left + 1 == right) {
            return 0;
        }
        
        if (cache[left*cols+right] != 0) {
            return cache[left*cols+right];
        }
        
        int ans = 0;
        for (int i = left+1; i < right; i++) {
            ans = max(ans, nums[left]*nums[right]*nums[i] 
                + calc(cache, cols, nums, left, i)
                + calc(cache, cols, nums, i, right));
        }
        cache[left*cols+right] = ans;
        
        return ans;
    }
};

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        vector<int> v;
        v.reserve(nums.size());
        v.push_back(1);
        for(int val: nums) {
            if (val > 0) {
                v.push_back(val);
            }
        }
        v.push_back(1);   

        int cnt = v.size();
        vector<int> dp(cnt*cnt, 0);

        for (int len = 2; len < cnt; len++) {
            for (int i = 0; i < cnt - len; i++) {
                for (int j = i + 1; j < i + len; j++) {
                    dp[i*cnt+i+len] = max(dp[i*cnt+i+len], v[i]*v[j]*v[i+len] + dp[i*cnt+j] + dp[j*cnt+i+len]);
                }
            }
        }

        return dp[cnt-1];
    }
};

int main() {
    vector<int> nums = {3, 1, 5, 8};
    Solution s;
    int ans = s.maxCoins(nums);
    cout << "ans = " << ans << endl;
    return 0;
}


