#include <string>
#include <limits>
#include <iostream>
using namespace std;

string minWindow(string s, string t)
{
    if (t.empty())
        return "";
    if (s.length() < t.length())
        return "";

    static const int MAX_CHAR = 256;
    int expected_count[MAX_CHAR] = {0};
    int appeared_count[MAX_CHAR] = {0};
    int appeared = 0;
    int min_begin = 0;
    int min_length = INT_MAX;

    // calc the expected count
    for (int i = 0; i < t.length(); i++)
        expected_count[ (unsigned char)t[i] ]++;

    // traverse the s, move the end point to find a range
    // then move the begin point to narrow the range.
    for (int i = 0, j = 0; j < s.length(); j++) {
        unsigned char ch = s[j];
        appeared_count[ch]++;

        if (expected_count[ch] > 0 && appeared_count[ch] <= expected_count[ch])
            appeared++;

        cout<<"appeared = "<<appeared<<endl;
        if (appeared >= t.length()) {
            // find one, move the begin pointer.
            while (i <= j) {
                ch = s[i];
                if (appeared_count[ch] > expected_count[ch]) {
                    i++;
                    appeared_count[ch]--;
                } else {
                    // the min one
                    if (j - i + 1 < min_length) {
                        min_begin = i;
                        min_length = j - i + 1;
                    }
                    // cout<<"i = "<<i<<", j = "<<j<<endl;
                    break;
                }
            }
        }
    } // end for

    if (min_length > s.length())
        return "";

    return s.substr(min_begin, min_length);
}

int main()
{
    string s = "A";
    string t = "A";

    string ans = minWindow(s, t);
    cout<<"ans = "<<ans<<endl;
    return 0;
}
