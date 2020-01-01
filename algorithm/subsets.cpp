#include <vector>
#include <iostream>
using namespace std;

// @begin - the begin index [begin, ...]
void dfs(vector<int>& s, int begin, vector<int>& prev, vector<vector<int> >& ans)
{
    for (int i = begin; i<s.size(); i++) {
        prev.push_back(s[i]);
        ans.push_back(prev);
        dfs(s, i+1, prev, ans);
        prev.pop_back();
    }
}

vector<vector<int> > subsets(vector<int>& s)
{
    sort(s.begin(), s.end());
    vector<vector<int> > ans;
    vector<int> prev;
    dfs(s, 0, prev, ans);
    ans.push_back(prev);
    
    return ans;
}


int main()
{
    vector<int> s = {3, 1, 2};
    vector<vector<int> > ans = subsets(s);

    for (auto v : ans) {
        cout<<"[";
        for (auto i : v)
            cout<<i<<",";
        cout<<"],"<<endl;
    }

    return 0;
}

