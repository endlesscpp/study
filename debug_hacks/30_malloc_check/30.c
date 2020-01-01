#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* p = (char*)malloc(30);
	strcpy(p, "test MALLOC_CHECK_ macro");
//	printf("%s\n", p);
//	printf("use env MALLOC_CHECK_=1 ./a.out to debug it\n");
	free(p);
	free(p);
	return 0;
}
