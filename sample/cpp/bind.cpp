#include <functional>
#include <iostream>
#include <memory>
using namespace std;

static void hello() {
    cout << "hello world" << endl;
}

struct Foo {
    Foo(int num) {
        mNum = num;
        printf("Foo::constructor, this = 0x%p\n", this);
    }

    Foo(const Foo& rhs) {
        printf("Foo::copy constructor, this = 0x%p, rhs = 0x%p\n", this, &rhs);
        this->mNum = rhs.mNum;
    }

    ~Foo() {
        printf("Foo::destructor, this = 0x%p\n", this);
        mNum = 0;
    }

    void hello() {
        printf("this = 0x%p, hello %d\n", this, mNum);
    }

    int mNum;
};

int main() {
    std::function<void()> f;
    f = hello;
    f();

#ifdef TEST_BIND_OBJ
    Foo foo(777);
    // Attention we can bind reference, or bind the object directly.
    // When bind with object directly, there will has copy-constructor
    //f = std::bind(&Foo::hello, &foo);
    f = std::bind(&Foo::hello, foo);
    f();
#endif

    shared_ptr<Foo> pFoo = make_shared<Foo>(888);
    f = std::bind(&Foo::hello, pFoo);
    //pFoo.reset();
    //f();
    printf("the end...\n");

    return 0;
}