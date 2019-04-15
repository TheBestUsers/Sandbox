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
typedef void*(*_memcpy)(void *,const void *, size_t);
typedef int (*_open)(const char *,int , mode_t);
typedef int (*_socks)(int domain, int type, int protocol);
typedef int (*_strncmp)(const char *, const char *,size_t );
typedef int (*_openat)(int ,const char *, int,mode_t );
typedef int (*_memcmp)(const void *s1, const void *s2, size_t n);




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



void *memcpy(void *dest, const void *src, size_t n)
{
	if(sizeof(dest)<n) return NULL;

	_memcpy custommem = (_memcpy) dlsym(RTLD_NEXT,"memcpy");

	return custommem(dest,src,n);


}

int open(const char* pathname,int flags, mode_t t)
{
	

	_strncmp mystrncmp = (_strncmp)dlsym(RTLD_NEXT,"strncmp");
		
	if ( mystrncmp("/",pathname,1) == 0 || mystrncmp("..",pathname,2)== 0) {
		printf("The program tries to open %s\n Do you agree?(yes/no): ",pathname);
		char ans[5];
		scanf("%s",ans);
	
		if (mystrncmp("yes",ans,3)!=0){
			printf("Aborted \n");	
			return -1;
		}	
	}
	_open myopen = (_open)dlsym(RTLD_NEXT,"open");	
	return myopen(pathname,flags,t);
}

int openat(int dirfd,const char * pathname, int flags,mode_t mode)
{
	_strncmp mystrncmp = (_strncmp)dlsym(RTLD_NEXT,"strncmp");
	
	if (mystrncmp("pathname","..",2) == 2 || mystrncmp("/",pathname,1) == 0){
		printf("The Program tries to open %s\n Do you agree?(yes/no): ", pathname);
		char ans[5];
		scanf("%s",ans);
		if ( mystrncmp(ans,"yes",3)!=0){
			printf("Aborted \n");
			return -1;
		}
	
	}
	
	
	_openat myopenat = (_openat)dlsym(RTLD_NEXT,"openat");
	return myopenat(dirfd,pathname,flags,mode);
}


int socket(int domain, int type, int protocol)
{
	printf("The Program tries to open up a socket for network connection\n");
	printf("Do you let it run ?(yes/no)\n");
	char ans[5];
	scanf("%s",ans);
	_strncmp mystrncmp = (_strncmp)dlsym(RTLD_NEXT,"strncmp");
	
	
	if(mystrncmp(ans,"yes",3)==0)
	
	{
			_socks mysocket = (_socks) dlsym(RTLD_NEXT,"socket");
			return mysocket(domain,type,protocol);  
		}
	else {
		printf("Aborted\n");	
		return 0;
	}
	
}
