#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    //
    // use the priority queue
    //
    int findKthLargest2(vector<int>& nums, int k) {
        priority_queue<int, std::vector<int>, std::greater<int>> q;
        for (auto i : nums) {
            q.push(i);
            if ((int)q.size() > k) {
                q.pop();
            }
        } 
        return q.top();
    }

    //
    // use the quick-sort concept
    //
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, std::vector<int>, std::greater<int>> q;
        for (auto i : nums) {
            q.push(i);
            if ((int)q.size() > k) {
                q.pop();
            }
        } 
        return q.top();
    }
};

int main() {
    vector<int> v = {3, 2, 1, 5, 6, 4};
    Solution s;
    int ans = s.findKthLargest(v, 2);
    cout<<"ans = "<<ans<<endl;
    return ans;
}
