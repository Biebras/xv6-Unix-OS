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

    printf("\n", foo1, foo2, foo3, foo4, foo5, foo6, foo7, foo8, foo9);

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

    exit(0);
}
