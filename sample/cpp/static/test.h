#ifndef OAK_TEST_INCLUDE
#define OAK_TEST_INCLUDE
#include <stdio.h>

// 1)if defined as normal function, then duplicated symbol error
// void commonFunc()
// 2)if defined as static function, pass link. However, both foo/bar print i
// as 1.
// 3)what happen if defined as 'static inline' ? Both print as 1 still.
extern "C" {
static void commonFunc()
{
    static int i = 0;
    i++;
    printf("in commonFunc, i = %d\n", i);
}
}

class Common
{
public:
    // NOTE: difference between static and static inline
    // Objdump -S shows no difference
    static inline void func()
    {
        static int i = 0;
        i++;
        printf("in Common:func(), i = %d\n", i);
    }
};

void foo();
void bar();


#endif // OAK_TEST_INCLUDE
