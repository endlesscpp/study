#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<vector<int> > fourSum(vector<int>& num, int target)
{
    vector<vector<int> > ans;

    if (num.size() < 4)
        return ans;

    sort(num.begin(), num.end());

    for (auto a = num.begin(); a != num.end(); ++a) {
        for (auto b = next(a); b != num.end(); ++b) {
            auto c = next(b);
            auto d = prev(num.end());

            while (c < d) {
                int sum = *a + *b + *c + *d;
                if (sum == target) {
                    ans.push_back( {*a, *b, *c, *d} );
                    ++c;
                    --d;
                } else if (sum < target) {
                    ++c;
                } else {
                    --d;
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    return ans;
}

int main()
{
    vector<int> v = {1, 0, -1, 0, -2, 2};
    vector<vector<int> > ans = fourSum(v, 0);

    for (auto vv : ans) {
        cout<<"(";
        for (auto k : vv)
            cout<<k<<", ";
        cout<<")"<<endl;
    }
    return 0;
}
