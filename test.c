#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>

int main()
{
	printf("This is the text function\n");
	int x = strlen("Ceva");
	strcmp("ceva","atlceva");
	char q[20];
	char *p=mmap(0,2500,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if (p == MAP_FAILED)
	{
		printf("Error");
			}
			strcpy(p,"something");
	printf("%s\n",p);

	int *number = mmap(0,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	*number =4;
	printf("%d\n",*number);
	return 0;
}