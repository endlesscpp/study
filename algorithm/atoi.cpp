#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

int atoi22(const char* str)
{
    if (str == NULL || strlen(str) == 0)
        return 0;

    int i = 0;
    while (isspace(str[i]))
        i++;

    bool negative = (str[i] == '-');
    if (negative)
        i++;
    else if (str[i] == '+')
        i++;

    long long ans = 0;

    for ( ; i<strlen(str); i++) {

        char ch = str[i];

        if (ch < '0' || ch > '9')
            break;

        ans = ans* 10 + (ch - '0');
    }

    if (negative)
        ans = 0 - ans;

    if (ans > INT_MAX)
        ans = INT_MAX;
    if (ans < INT_MIN)
        ans = INT_MIN;

    return ans;
}

int main()
{
    const char* str = "-356";
    int a = atoi22(str);

    printf("a = %d\n", a);
    return 0;
}

