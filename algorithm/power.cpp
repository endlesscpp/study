#include <stdio.h>

int step = 0;

    double power(double x, long long n) {
        if (n == 0)
            return 1;

        if (n < 0)
            return power(x, -n);
        
        double f = power(x, n/2);
        if (n % 2 == 0)
            return f * f;
        else
            return f * f * x;
    }

    double pow(double x, int n) {
        return power(x, (long long)n);
    }




int main()
{
    double ans = pow(1.00000, -2147483648);

    printf("ans = %.7f\n", ans);
    return 0;
}


