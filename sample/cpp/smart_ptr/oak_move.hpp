#ifndef OAK_MOVE_HPP
#define OAK_MOVE_HPP

#include <stdio.h>

namespace oak
{
template<typename _Tp>
struct remove_reference {
    typedef _Tp type;
};

template<typename _Tp>
struct remove_reference<_Tp&> {
    typedef _Tp type;
};

template<typename _Tp>
struct remove_reference<_Tp&&> {
    typedef _Tp type;
};

/* forward lvalues as either lvalues or rvalues, depending on T.
    template<class T>
    void wrapper(T&& arg)
    {
        // arg is always lvalue
        foo(std::forward<T>(arg)); // Forward as lvalue or as rvalue, depending on T
    }
*/
template<typename T>
T&& forward(typename remove_reference<T>::type& t) noexcept
{
    printf("forward l-value\n");
    return static_cast<T&&>(t);
}

template<typename T>
T&& forward(typename remove_reference<T>::type&& t) noexcept
{
#if 0 // TODO: check if is lvalue reference
    static_assert(!oak::is_lvalue_reference<_Tp>::value,
                "template argument substituting _Tp is an lvalue reference type");
#endif
    printf("forward r-value\n");
    return static_cast<T&&>(t);
}

} // namespace oak

#endif // OAK_MOVE_HPP
