#include "kernel/types.h"
#include "user/user.h"
#include "user/memory_management.h"

int main(int argc, char *argv[])
{
   	char* foo1 = (char*)_malloc(1000);
    char* foo2 = (char*)_malloc(20000);
    char* foo3 = (char*)_malloc(1000);
    char* foo4 = (char*)_malloc(10);
    char* foo5 = (char*)_malloc(20);
    char* foo6 = (char*)_malloc(5000);
    char* foo7 = (char*)_malloc(10000);
    char* foo8 = (char*)_malloc(200);
    char* foo9 = (char*)_malloc(45);
    char* foo10 = (char*)_malloc(3024);

    PrintMemoryLinkList();

    printf("\n", foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9, foo10);

    _free(foo1);
    _free(foo2);
    _free(foo3);
    _free(foo4);
    _free(foo5);
    _free(foo6);
    _free(foo7);
    _free(foo8);
    _free(foo9);
    _free(foo10);

    PrintMemoryLinkList();
	
	char* boo1 = (char*)_malloc(40000);
	char* boo2 = (char*)_malloc(1000);
	printf("Ptr: %d\n", boo1);
	PrintMemoryLinkList();

	_free(boo1);

	PrintMemoryLinkList();

	char* boo3 = (char*)_malloc(39977);
	char* boo4 = (char*)_malloc(8000);

	PrintMemoryLinkList();
	printf("Ptr: %d\n", boo3);
	_free(boo3);

	printf("\n", boo1, boo2, boo3, boo4);

    exit(0);
}
