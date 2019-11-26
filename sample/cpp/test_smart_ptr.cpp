#include <stdio.h>
#include <stdlib.h>
#include <memory>
using namespace std;

struct free_deleter {
	void operator()(void* x) {
		free(x);
		printf("free 0x%p\n", x);
	}
};

static void func_free(void* p) {
	free(p);
	printf("free2 0x%p\n", p);
}

int main(int argc, char** argv) {
	unique_ptr<char, free_deleter> sp((char*)malloc(1000));
	unique_ptr<char, std::function<void(void*)>> sp2((char*)malloc(1000), free);
	return 0;
}

