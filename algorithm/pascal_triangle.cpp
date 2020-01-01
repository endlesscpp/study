#include <vector>
#include <iostream>
using namespace std;

    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > ans;
        for (int i = 1; i<= numRows; i++) {
            
            vector<int> curr;
            curr.reserve(i);
            for (int j = 0; j<i; j++) {
                if (j == 0 || j == i-1)
                    curr.push_back(1);
                else {
                    vector<int> v = ans.back();
                    cout<<"sizeof(back) = "<<v.size()<<endl;
                    curr.push_back(ans.back()[j-1] + ans.back()[j]);
                }
            }
            ans.push_back(curr);
        }
        
        return ans;
    }


int main()
{
    vector<vector<int> > ans = generate(3);
    for (auto& v : ans) {
        for (auto& val : v) {
            cout<<val<<", ";
        }
        cout<<endl;
    }

    return 0;
}

