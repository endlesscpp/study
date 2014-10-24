#include <stdio.h>
#include <iostream>
using namespace std;

bool isMatch(const char* s, const char* p)
{
    if (*p == '*') {
        while (*p == '*')
            p++;
        p--;
    }

    if (*p == '*' && *(p+1) == '\0')
        return true;

    if (*s == '\0' || *p == '\0')
        return *s == *p;

    if (*p == '*') {
        while (true) {
            if (isMatch(s, p+1))
                return true;
            if (*s++ == '\0')
                break;
        }
    } else if (*p == '?') {
        return isMatch(++s, ++p);
    } else if (*p == *s) {
        return isMatch(++s, ++p);
    } else {
        return false;
    }
    return false;
}

bool isMatch2(const char* s, const char* p) {

    const char* savedP = NULL;
    const char* savedS = NULL;
    int eatten = 0;

    while (*s != '\0') {
        if (*s == *p || *p == '?') {
            s++;
            p++;
            continue;
        }

        if (*p == '*') {
            savedP = p;
            savedS = s;
            eatten = 0;
            p++; // to match the next.
            continue;
        }

        // previous match failed, if have savedS, roll back to it and eat one more.
        if (savedS) {
            eatten++;
            s = savedS + eatten;
            p = savedP + 1;
            continue;
        }

        //still not matched
        return false;
    }

    while (*p == '*')
        p++;

    return *p == '\0';
}


int main()
{
    // cout<<isMatch2("aab", "c*a*b")<<endl;
    cout<<isMatch2("aa", "a")<<endl;
    return 0;
}
