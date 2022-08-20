#include <string.h>
#include "file_methods.h"
#define BUFFER_SIZE 80


char * extractPathWitoutPostfix(char *path)
{
	char *token;
	token=strtok(path,".");
	return token;	
}
