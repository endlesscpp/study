#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

/**
 * f(0)(k) = 0
 * f(i+1)(k) = f(i)(k+nums[i+1]) + f(i)(k-nums[i+1])
 */
class Solutin {
    static const int M = 1000;
    public:
        int findTargetSumWays(vector<int>& nums, int S) {
            int sum = 0;
            for (int i : nums) {
                sum += i;
            }
            if (S > sum || S < -sum) {
                return 0;
            }

            int a[M*2+1] = {0};
            int b[M*2+1] = {0};

            int* prev = a;
            int* curr = b;
            curr[M] = 1;
            for (int i = 0; i < (int)nums.size(); i++) {
                int* t = prev;
                prev = curr;
                curr = t;
                memset(curr, 0, (2*M+1)*sizeof(int));

                for (int j = 0; j < M*2+1; j++) {
                    if (prev[j] != 0) {
                        curr[j+nums[i]] += prev[j];
                        curr[j-nums[i]] += prev[j];
                    }
                }
            }

            return curr[M+S];
        }
};


int main() {
    vector<int> v(5, 1);
    Solutin s;
    int n = s.findTargetSumWays(v, 3);
    printf("cnt = %d, n = %d\n", (int)v.size(), n);
}
