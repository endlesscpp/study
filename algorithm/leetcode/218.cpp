#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    public:
        vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
            vector<pair<int, int>> ans;
            if (buildings.empty()) {
                return ans;
            }

            int x[10001 * 3] = {0};
            int h[10001 * 3] = {0};

            int count = buildings.size();
            for (int i = 0; i < count; i++) {
                vector<int>& item = buildings[i];
                x[3*i] = item[0];
                x[3*i+1] = item[1] - 1;
                x[3*i+2] = item[1];
            }

            std::sort(x, x + count*3);
            // remove duplicated
            int jj = 1;
            for (int i = 1; i < count * 3; i++) {
                if (x[jj-1] != x[i]) {
                    x[jj++] = x[i];
                }
            }
            count = jj;
            cout << "----x:----" << endl;
            for (int i = 0; i < count; i++) {
                printf("%2d, ", x[i]);
            }
            printf("\n");

            unordered_map<int, int> idxmap;
            for (int i = 0; i < count; i++) {
                idxmap[x[i]] = i;
            }

            for (vector<int>& item : buildings) {
                int l = idxmap[item[0]];
                int r = idxmap[item[1]-1];
                for (int i = l; i <= r; i++) {
                    h[i] = std::max(h[i], item[2]);
                }
            }

            cout << "----h:----" << endl;
            for (int i = 0; i < count; i++) {
                printf("%2d, ", h[i]);
            }
            printf("\n");

            int prev = 0;
            for (int i = 0; i < count; i++) {
                if (h[i] != prev) {
                    ans.push_back(std::make_pair(x[i], h[i]));
                    prev = h[i];
                }
            }

            return ans;
        }
};


int main() {
    vector<vector<int>> buildings = {
        {2, 9, 10},
        {3, 7, 15},
        {5, 12, 12},
        {15, 20, 10},
        {19, 24, 8}
    };
    Solution s;
    vector<pair<int, int>> ans = s.getSkyline(buildings);
    for (auto& item : ans) {
        cout << "(" << item.first << ", " << item.second << ")" << endl;
    }
    return 0;
}



