#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

static unsigned char virus_signature[] = {0xb8, 0xff, 0xff, 0xff, 0xff, 0xc3};

int main(int argc, const char **args, char **envp) {
	// args[1] path to executable
	// args[2] ... arguments

	char arguments[2048];
	strcpy(arguments,"LD_PRELOAD=./libdetour.so ./");
	if (argc < 2) {
		printf("Please specify executable!\n");
		return 0;
	}

	// Launch args[1] and arguments in sandbox mode.
	for (int i=1;i<argc;i++)
	{
		strcat(arguments,args[i]);
		if(i!=argc-1)
			strcat(arguments," ");
	}

	system(arguments);

	
	(void) virus_signature;
	
	return 0;
}
