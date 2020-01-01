#include <string.h>
#define EXIT_SUCCESS 0

char names[] = "book cat dog building vegetable curry";

void func(void){
	char buf[5];
	strcpy(buf, names);
}

int main(void) {
	func();
	return EXIT_SUCCESS;
}
