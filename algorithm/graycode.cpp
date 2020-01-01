#include <vector>
#include <iostream>
using namespace std;

/*
 * 000
 * 001
 * ---
 * 011
 * 010
 * -------
 * 110
 * 111
 * 101
 * 100
 */
vector<int> grayCode(int n)
{
    vector<int> ans;
    if (n == 0) {
        ans.push_back(0);
        return ans;
    }

    for (int i = 0; i<2; i++)
        ans.push_back(i);

    if (n == 1)
        return ans;

    int factor = 1;

    for (int i = 1; i<n; i++) {
        factor *= 2;
        int cnt = ans.size();
        for (int j = cnt-1; j>=0; j--) {
            ans.push_back(factor + ans[j]);
        }
    }

    return ans;
}


int main()
{
    vector<int> v = grayCode(3);
    for (int k : v)
        cout<<k<<endl;

    return 0;
}
