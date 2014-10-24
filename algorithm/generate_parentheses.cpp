#include <string>
#include <vector>
#include <iostream>
using namespace std;

static char s_paths[] = {'(', ')'};

void generate(int* flags, int pending, string str, int begin, int max, vector<string>& ans)
{
    if (begin == max) {
        ans.push_back(str);
        return;
    }

    for (int i = 0; i<2; i++) {
        if (pending == 0 && i == 1)
            continue;

        if (flags[i] < max/2) {
            flags[i]++;
            pending = (i == 0) ? pending+1 : pending-1;
            generate(flags, pending, str+s_paths[i], begin+1, max, ans);
            pending = (i == 0) ? pending-1 : pending+1;
            flags[i]--;
        }
    }
}

vector<string> generateParenthesis(int n)
{
    int flags[2] = {0};
    vector<string> ans;

    generate(flags, 0, "", 0, n*2, ans);
    return ans;
}

int main()
{
    vector<string> ans = generateParenthesis(4);
    for (auto s : ans) {
        cout<<s<<endl;
    }

    return 0;
}

