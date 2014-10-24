#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
using namespace std;

vector<int> findSubstring(string S, vector<string> &L) {
    vector<int> ans;
    if (S.empty() || L.size() == 0)
        return ans;

    unordered_map<string, int> expected;
    // calc expected
    for (const auto& str : L)
        expected[str]++;

    int seed_len = L[0].length();
    // cout<<"map.size() = "<<unused.size()<<endl;
    // traverse S, if curr_str is not expected, check if all expeced are occurred
    // record it if yes.
    int cat_len = L.size() * seed_len;
    int max_len = S.length() - L.size() * seed_len;

    for (int i = 0; i <= max_len; i++) {
        unordered_map<string, int> unused(expected);
        for (int j = i; j < i + cat_len; j += seed_len) {
            auto it = unused.find(S.substr(j, seed_len));
            if (it == unused.end())
                break;

            it->second--;
            if (it->second == 0)
                unused.erase(it);
        }

        if (unused.empty())
            ans.push_back(i);
    }

    return ans;
}


int main()
{
    string s = "barfoothefoobarman";
    vector<string> L = {"foo", "bar"};

    vector<int> ans = findSubstring(s, L);
    for (auto k : ans)
        cout << k <<", ";
    cout<<endl;
    return 0;
}

