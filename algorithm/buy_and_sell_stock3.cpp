#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int ans = 0;
        int size = prices.size();
        if (size < 2)
            return 0;
        
        vector<int> f(size, 0);
        vector<int> g(size, 0);

        int valley = prices[0];
        for (int i = 1; i < size; i++) {
            if (prices[i] < valley)
                valley = prices[i];
            f[i] = max(f[i-1], prices[i] - valley);
        }

        int peak = prices[size-1];
        for (int i = size-2; i >= 0; i--) {
            if (peak < prices[i])
                peak = prices[i];
            g[i] = max(g[i+1], peak - prices[i]);
        }

        for (int i = 0; i<size; i++) {
            if (ans < f[i] + g[i])
                ans = f[i] + g[i];
        }
        
        return ans;
    }
};

int main()
{
    vector<int> prices = {2, 1, 2, 0, 1};

    Solution s;
    int ans = s.maxProfit(prices);

    cout<<ans<<endl;

    return 0;
}
