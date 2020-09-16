#include <iostream>

#include "catch.hpp"
#include "oak_memory.hpp"
#include "oak_move.hpp"

TEST_CASE("delete and delete[]", "[deleter]")
{
    int*                     p1 = new int(3);
    oak::default_delete<int> d1;
    d1(p1);

    int*                       p2 = new int[99];
    oak::default_delete<int[]> d2;
    d2(p2);

    REQUIRE(true);
}

TEST_CASE("get", "[unique_ptr]")
{
    int*                 p1 = new int(3);
    oak::unique_ptr<int> sp(p1);
    REQUIRE(sp);

    REQUIRE(p1 == sp.get());

    *sp = 4;
    REQUIRE(*sp == 4);

    sp.reset();
    REQUIRE(!sp);
}

TEST_CASE("swap", "[unique_ptr]")
{
    oak::unique_ptr<int> sp1(new int(1));
    oak::unique_ptr<int> sp2(new int(2));
    sp1.swap(sp2);
    REQUIRE(*sp1 == 2);
    REQUIRE(*sp2 == 1);
}

struct Fruit {
    int color;
    int type;
};

TEST_CASE("operator->", "[unique_ptr]")
{
    oak::unique_ptr<Fruit> sp(new Fruit());
    sp->color = 1;
    REQUIRE(sp->color == 1);
}

TEST_CASE("r-value ref", "[unique_ptr]")
{
    oak::unique_ptr<int> sp1(new int(1));
    oak::unique_ptr<int> sp2(std::move(sp1));
    REQUIRE(!sp1);
    REQUIRE(*sp2 == 1);
    oak::unique_ptr<int> sp3;
    sp3 = std::move(sp2);
    REQUIRE(!sp2);
    REQUIRE(*sp3 == 1);
}

struct A {
    A(int&& n)
    {
        printf("rvalue overload, v=%d\n", n);
        value_ = n;
    }
    A(int& n)
    {
        printf("lvalue overload, v=%d\n", n);
        value_ = n;
    }

    int value_;
};

// https://en.cppreference.com/w/cpp/utility/forward
template<class T>
void wrapper(T&& arg)
{
    // arg is always lvalue
    new A(oak::forward<T>(arg));
}

TEST_CASE("forward lvalue as lvalue or rvalue", "[forward]")
{
    int i = 1;
    wrapper(i);
    wrapper(0);
}

struct Arg {
    int i = 1;
    int get() &&
    {
        printf("arg get, r-value\n");
        return i;
    } // call to this overload is rvalue
    int& get() &
    {
        printf("arg get, l-value\n");
        return i;
    } // call to this overload is lvalue
};

#include <utility>
template<class T>
void wrapper2(T&& arg)
{
    using Type = decltype(oak::forward<T>(arg).get());
//    Type tt = (char*)2;
    new A(oak::forward<Type>(oak::forward<T>(arg).get()));
}

Arg getArg()
{
    Arg arg;
    return arg;
}

TEST_CASE("forward rvalue as rvalue", "[forward]")
{
    printf("================\n");
    Arg arg;
    wrapper2(arg);
    printf("----------------\n");
    wrapper2(getArg());
}

