#include <stdlib.h>
#include "pre_processor.h"
#include "firstPass.h"
#include "post_processor.h"
#define ASSEMBLER_FILES_POSTFIX ".as"

/*-------------------------------internal methods decleration-------------------------------*/
void createDotAsPath(char *path);
/*------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	int i, code;
	char *path;
	for(i=1;i<argc;i++)
	{
		path=(char *)malloc(strlen(argv[i])*sizeof(char *));
		strcpy(path, argv[i]);
		createDotAsPath(path);
		updateProcessedFile(path);
		if(preProcessor(path)==VALID)
		{
			createDotAmPath(path);
			if((code=firstPass(path))==VALID)
				createOutputFiles(argv[i]);
		}
		free(path);
	}
	return 1;
}

void createDotAsPath(char *path)
/*Recived a file path and add to the path the as postfix*/
{
	char *pDot=strchr(path,'.');
	if(pDot==NULL) /*meaning that there isn't format for the file*/
		strcat(path,ASSEMBLER_FILES_POSTFIX);
	else
	{
		*(pDot+1)='a';
		*(pDot+2)='s';
		*(pDot+3)='\0';
	}
}
