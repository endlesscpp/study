#include <vector>
using namespace std;

/**
 * let a(i) = prices(i) - price(i-1). This problem become find the max segment sum with cooldown.
 * let f(i) be max profit ends with ith item.
 *
 * f(i) = max{f(i-1) + a(i), max{f(k) + a(i)} (0 <= k <= i-3)}
 *
 * The answer is max{f(i)}, 0 <= i < prices.size().
 *
 * Under below program, we keep
 * fprev3max:   max{f(k)}, 0 <= k <= i-3.
 * fprev2:      f(i-2)
 * fprev1:      f(i-1)
 * fcurr:       f(i)
 */
class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int fprev3max = 0;
            int fprev2 = 0;
            int fprev1 = 0;
            int fcurr = 0;

            for (int i = 1; i < (int)prices.size(); i++) {
                fprev3max = max(fprev3max, fprev2);
                fprev2 = fprev1;
                fprev1 = fcurr;

                int v = prices.at(i) - prices.at(i-1);
                fcurr = max(fprev1+v, fprev3max+v);
            }

            return max(max(max(fprev3max, fprev2), fprev1), fcurr);
        }


};


