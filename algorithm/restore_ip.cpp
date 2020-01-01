#include <string>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

static const int MAX_SEG = 4;


void restore(const string& str, int lens[], int k, vector<string>& ans)
{
    int used = 0;
    for (int i = 0; i<k; i++)
        used += lens[i];

    if (k == MAX_SEG) {
        if (used != str.length())
            return;

        int begin = 0;
        string s;
        for (int i = 0; i<MAX_SEG; i++) {
            s += str.substr(begin, lens[i]);
            if (i != MAX_SEG-1)
                s += ".";

            begin += lens[i];
        }
        ans.push_back(s);
        return;
    }

    if (str.length() - used > (MAX_SEG - k) * 3)
        return;

    int left = min( (int)str.length() - used, 3);
    for (int i = 1; i<=left; i++) {
        
        string substr = str.substr(used, i);
        if (atoi(substr.c_str()) > 255)
            continue;
        
        bool invalid = false;
        for (int j = 0; j<i-1; j++) {
            if (substr[j] == '0')
                invalid = true;
            else
                break;
        }

        cout<<"str = "<<substr<<", invalid = "<<(invalid ? "true" : "false")<< endl;

        if (invalid)
            continue;

        lens[k] = i;
        restore(str, lens, k+1, ans);
        lens[k] = 0;
    }
}

vector<string> restoreIp(const string& str)
{
    int lens[MAX_SEG] = {0};
    vector<string> ans;

    restore(str, lens, 0, ans);
    return ans;
}


int main()
{
    //string str = "25525511135";
    string str = "010010";
    vector<string> ans = restoreIp(str);

    for ( auto str : ans )
        cout<<str<<endl;

    return 0;
}
