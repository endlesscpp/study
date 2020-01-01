#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * each input element has 2 points: the begin point and the end point.
 * we sort all of those points, and scan from left to right；and main a map(RB-TREE), key 
 * the height, value is the count of height.
 * If point is enter point, add the height to map, and increase the count;
 * Else if point is leave point, decrease the count or remove it from map.
 *
 * If point is leave point, get the max height of map, if not equal to the previous height, add 
 * it to answer vector.
 */
class Solution {
    private:
        struct Point {
            int x;
            int h;
            int type; // 0 - enter, 1 - leave
        };
        
        static bool cmp(const Point& lhs, const Point& rhs) {
            return lhs.x < rhs.x;
        }
    public:
        vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
            vector<pair<int, int>> ans;
            if (buildings.empty()) {
                return ans;
            }

            vector<Point> pts;
            for (auto& item : buildings) {
                Point pt;
                pt.x = item.at(0);
                pt.h = item.at(2);
                pt.type = 0;
                pts.push_back(pt);

                pt.x = item.at(1);
                pt.type = 1;
                pts.push_back(pt);
            }
            std::sort(pts.begin(), pts.end(), cmp);

            int nextx = 0;
            int prevh = 0;
            map<int, int> mp;
            mp[0] = 1;
            for (int i = 0; i < (int)pts.size(); i++) {
                Point& pt = pts[i];
                auto it = mp.find(pt.h);
                if (pt.type == 0) {
                    if (it != mp.end()) {
                        it->second = it->second + 1;
                    } else {
                        mp.insert(std::make_pair(pt.h, 1));
                    }
                } else {
                    // pop the h.
                    if (it->second > 1) {
                        it->second = it->second - 1;
                    } else {
                        mp.erase(it);
                    }
                }
                nextx = (i == (int)pts.size() - 1) ? -1 : pts[i+1].x;
                if (pts[i].x == nextx) {
                    continue;
                }

                // get the current max height
                int h = (--mp.end())->first;
                if (h != prevh) {
                    ans.push_back(std::make_pair(pt.x, h));
                    prevh = h;
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



