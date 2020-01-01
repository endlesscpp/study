#include <stdio.h>

int divide(int dividend, int divisor) {
    int ans = 0; // will overflow if dividend == INT_MAX and vidisor == -1
    bool negative = (dividend > 0 && divisor < 0)
        || (dividend < 0 && divisor > 0);

    unsigned int a = dividend >= 0 ? dividend : -dividend;
    unsigned int b = divisor >= 0 ? divisor : -divisor;

    while (a >= b) {
        int multi = 1;
        unsigned bb = b;

        while (a >= bb) {
            a -= bb;
            ans += multi;

            if (bb < (INT_MAX >> 1)) {
                bb += bb;
                multi += multi;
            }
        }
    }

    if (negative)
        return -ans;
    else
        return ans;
}


