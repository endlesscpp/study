#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


    void dfs(vector<int>& candidates, vector<int>& prev, int prev_ans, int target, int begin, vector<vector<int> >& ans) {
        if (prev_ans == target) {
            ans.push_back(prev);
            return;
        }
        
        if (prev_ans > target)
            return;
        
        for (int i = begin; i<candidates.size(); i++)
        {
            int k = candidates[i];
            prev.push_back(k);
            prev_ans += k;
            
            dfs(candidates, prev, prev_ans, target, i, ans);
            
            prev_ans -= k;
            prev.pop_back();
        }
    }
    
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        
        vector<vector<int> > ans;
        vector<int> prev;
        int prev_ans = 0;
        
        dfs(candidates, prev, prev_ans, target, 0, ans);
        
        return ans;
    }

int main()
{
    vector<int> candidates = {2, 3, 6, 7};
    vector<vector<int> > ans = combinationSum( candidates, 7 );

    for (auto v : ans) {
        cout<<"[";
        for (auto k : v)
            cout<<k<<",";
        cout<<"]"<<endl;
    }

    return 0;
}
