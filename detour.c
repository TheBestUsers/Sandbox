#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>


static void __attribute__((constructor)) init()
{
	fprintf(stderr, "Library loaded!\n");
}

static void __attribute__((destructor)) uninit()
{
	fprintf(stderr, "Library closed\n");
}

typedef size_t (*strlen_fn)(const char *);
typedef int (*_strcmp)(const char *,const char*);
typedef  void*(*_mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset);


int strcmp(const char *s1, const char *s2)
{
	_strcmp __strcmp = (_strcmp)dlsym(RTLD_NEXT,"strcmp");
	printf("I've got your function\n");
	return __strcmp(s1,s2);
}




size_t strlen(const char *s)
{
	strlen_fn __strlen = (strlen_fn)dlsym(RTLD_NEXT, "strlen");
	size_t len = __strlen(s);
	fprintf(stderr, "== Intercepted call ==> strlen(%s) = %lu\n", s, len);
	return len-1;
}

void * mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset){
	_mmap mymap = (_mmap)dlsym(RTLD_NEXT,"mmap");
	printf("This is my mmap function\n");
	return mymap(addr,length,prot,flags,fd,offset);
	
}

