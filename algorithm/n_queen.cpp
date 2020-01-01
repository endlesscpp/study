#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

int s_cnt;
void solve(int n, int i, int a[], vector<vector<string> >& ans)
{
    if ( i == n ) {
        // s_cnt++;
        // return;

        //ctor the ans
        vector<string> v;
        for (int j = 0; j<n; j++) {
            assert( a[j] != -1 );
            string str(n, '.');
            str[ a[j] ] = 'Q';
            v.push_back(str);
        }
        ans.push_back(v);
        return;
    }

    bool occupied[n];
    fill_n(occupied, n, false);

    for (int j = 0; j<i; j++) { //the j th row
        occupied[ a[j] ] = true;

        int k = a[j] - (i - j);
        if (k >= 0)
            occupied[k] = true;

        k = a[j] + (i - j);
        if (k < n)
            occupied[k] = true;
    }

    for (int j = 0; j<n; j++) { //find the cell that can be used
        if (occupied[j] == false) {
            a[i] = j;
            solve(n, i+1, a, ans);
            a[i] = -1;
        }
    }
}

vector<vector<string> > solveNQueens(int n)
{
    int a[n];
    fill_n(a, n, -1);
    vector<vector<string> > ans;
    
    solve(n, 0, a, ans);
    return ans;
}

int main()
{
    vector<vector<string> > ans;
    ans = solveNQueens(14);

    /*
    for (auto v : ans) {
        cout<<"------------------------"<<endl;
        for (auto str : v)
            cout<<str<<endl;
    }
    */
    cout<<"size = "<<s_cnt<<endl;

    return 0;
}

