/**
 * f(i, l) = f(i, l-1) + a[i+l-1], 0 <= i <= len - l
 *
 */

#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;
int subarraySum2(vector<int>& nums, int k) {
    int len = nums.size();
    int cnt = 0;
    vector<int> dp(nums.size(), 0);

    for (int l = 1; l <= len; l++) {
        for (int i = 0; i <= len - l ; i++) {
            dp[i] = dp[i] + nums[i+l-1];
            if (dp[i] == k) {
                cnt++;
            }
        }
    }
    return cnt;
}

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    int cnt = 0;
    int sum = 0;
    mp[0] = 1;
    for (int i = 0; i < (int)nums.size(); i++) {
        sum += nums.at(i);
        cnt += mp[sum-k];
        mp[sum] = mp[sum] + 1;
    }
    return cnt;
}

int main() {
    vector<int> v = {1, 2, 3};
    int cnt = subarraySum(v, 3);
    return cnt;
}
