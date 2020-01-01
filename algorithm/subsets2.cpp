#include <vector>
#include <iostream>
#include <map>
using namespace std;

// @begin - the begin index [begin, ...]
void dfs(vector<int>& s, int begin, vector<int>& prev, vector<vector<int> >& ans)
{
    map<int, bool> flag;

    for (int i = begin; i<s.size(); i++) {
        if (flag[ s[i] ])
            continue;

        prev.push_back(s[i]);
        flag[ s[i] ] = true;
        ans.push_back(prev);
        dfs(s, i+1, prev, ans);
        prev.pop_back();
    }
}

vector<vector<int> > subsetsWithDup(vector<int> &S) 
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
    vector<int> s = {1, 2, 2};
    vector<vector<int> > ans = subsetsWithDup(s);

    for (auto v : ans) {
        cout<<"[";
        for (auto i : v)
            cout<<i<<",";
        cout<<"],"<<endl;
    }

    return 0;
}

