#include "catch.hpp"
#include "oak_memory.hpp"

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

TEST_CASE("->", "[unique_ptr]")
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
