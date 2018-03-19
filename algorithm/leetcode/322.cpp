#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
private:
    unordered_map<int, int> mCache;        
public:
    int coinChange(vector<int>& coins, int amount) {
        mCache.clear();
        return calc(coins, amount); 
    }

    int calc(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        if (amount < 0) {
            return -1;
        }

        if (mCache.find(amount) != mCache.end()) {
            return mCache[amount];
        }

        int ans = -1;
        for (int coin : coins) {
            int k = calc(coins, amount - coin);
            if (k != -1) {
                if (ans == -1) {
                    ans = k+1;
                } else {
                    ans = min(ans, k+1);
                }
            }
        }

        mCache[amount] = ans;

        return ans;
    }
};

int main() {
    vector<int> v = {1, 2, 5};
    Solution s;
    int ans = s.coinChange(v, 16);
    cout << "the count is: " << ans << endl;
    return ans;
}
