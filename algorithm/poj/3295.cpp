/**
 *
 * 
 *
 *
 **/
#define SELF_TEST
#include <stdio.h>
#include <string.h>

#ifdef SELF_TEST
#include <errno.h>

static const char* s_sample = "/Users/still/git/algorithm/poj/test_data/3295.txt";
#endif

static bool s_bFailed = false;
char buf[255];

static int GetIndex(char a)
{
    return a - 'p';
}

static int s_index = 0;
int eval(int* a, int n)
{
    int aa, bb;
    char ch = buf[s_index++];
    switch (ch)
    {
        case 'q':
        case 'p':
        case 'r':
        case 's':
        case 't':
            return a[GetIndex(ch)];
        case 'K':
            aa = eval(a, n);
            bb = eval(a, n);
            return aa && bb;
        case 'A':
            aa = eval(a, n);
            bb = eval(a, n);
            return aa || bb;
        case 'N':
            return !eval(a, n);
        case 'C':
            {
            aa = eval(a, n);
            bb = eval(a, n);
            return aa != 1 || bb != 0;
            }
        case 'E':
            return eval(a, n) == eval(a, n);
    }
}

static bool IsTautology(int* a, int n)
{
    s_index = 0;
    int ret = eval(a, n);
    return ret == 1;
}

static void Backtrack(int* a, int k, int n)
{
    if (s_bFailed)
        return;

    if (k == n) 
    {
        if (!IsTautology(a, n))
        {
            s_bFailed = true;
            return;
        }
    }
    else
    {
        int c[2] = {0, 1};
        for (int i = 0; i<2; i++)
        {
            a[k] = c[i];
            Backtrack(a, k+1, n);
        }
    }
}

static void ProcessItem()
{
    s_bFailed = false;
    s_index = 0;
    int a[5] = {0};
    Backtrack(a, 0, 5);
    if (!s_bFailed)
        printf("tautology\n");
    else
        printf("not\n");
}

static void func()
{
    while (true) {
        char* p = fgets(buf, 255, stdin);
        if (p == NULL) {
            return;
        }

        if (*p == '0')
            return;

        int len = strlen(buf);
        while (buf[len-1] == '\n' || buf[len - 1] == '\r')
        {
            buf[len-1] = 0;
            len--;
            if (len == 0)
                break;
        }
        ProcessItem();
    }
    return;
}

int main(int argc, char* argv[])
{
#ifdef SELF_TEST
    FILE* stream = freopen(s_sample, "r", stdin);
    if (stream == NULL) {
        printf("freopen failed, file = %s, err = %d\n", s_sample, errno);
        return -1;
    }
#endif

    func();

#ifdef SELF_TEST
    fclose(stream);
#endif

    return 0;
}

