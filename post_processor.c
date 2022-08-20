#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "post_processor.h"
#include "base32.h"
#include "commands_words.h" /*includes assemblerArrays.h, errors.h*/
#define DOT_OB_POSTFIX_LEN 3
#define SIZE_OF_FINAL_FILE_LINE() (strlen("\t")+ 4) /*we have 4 32 base chars per line*/
#define OB_FILE_POSTFIX ".ob"


/*-------------------------------internal methods decleration-------------------------------*/
void createObFile(char *path);
void createDotObPath (char *path);
/*------------------------------------------------------------------------------------------*/


void createOutputFiles(char *path)
{
	createObFile(path);
	createExternEntryFiles(path);
}

void createObFile(char *path)
/*Recived path and create in the path the object file*/
{
	char *obPath, baseChars[MAX_32_NUMBER_LEN];
	FILE *obPtr;
	int i;

	obPath=(char *)malloc(strlen(path)+DOT_OB_POSTFIX_LEN*sizeof(char));
	strcpy(obPath,path); 
	createDotObPath(obPath);
	obPtr=fopen(obPath,"w");
	if (obPtr == NULL) /* Unable to open file hence exit */
	{
		print_code(UNKNOWN_ERROR);
		exit(EXIT_SUCCESS);
	}
	/*putting header line to file*/
	getBaseCharsByDecimal(getInstructionCounterValue(),baseChars);
	fputs(baseChars, obPtr);
	fputc(TAB_CHAR,obPtr);
	getBaseCharsByDecimal(getDataCounterValue(),baseChars);
	fputs(baseChars, obPtr);
	fputc(END_OF_LINE_CHAR,obPtr);
	/*parsing & putting all instructions to file*/
	for(i=0;i<(getInstructionCounterValue());i++)
	{
		/*creating line number for the file*/
		getBaseCharsByDecimal(FIRST_INDEX+i,baseChars);
		fputs(baseChars,obPtr);
		fputc(TAB_CHAR,obPtr);
		/*creating base chars of the word*/
		getBaseCharsBy10Binary(instructions[i], baseChars);
		fputs(baseChars,obPtr);
		fputc(END_OF_LINE_CHAR,obPtr);
	}
	/*parsing & putting all data to file*/
	for(i=0;i<(getDataCounterValue());i++)
	{
		/*creating line number for the file*/
		getBaseCharsByDecimal(FIRST_INDEX+getInstructionCounterValue()+i,baseChars);
		fputs(baseChars,obPtr);
		fputc(TAB_CHAR,obPtr);
		/*creating base chars of the word*/
		getBaseCharsBy10Binary(data[i], baseChars);
		fputs(baseChars,obPtr);
		fputc(END_OF_LINE_CHAR,obPtr);
	}

	fclose(obPtr);
	free(obPath);
}

void createDotObPath (char *path)
/*Recived path and saves in the path the postfix of object file*/
{
	char *pDot=strchr(path,'.');
	if(pDot==NULL) /*meaning that there isn't format for the file*/
		strcat(path,OB_FILE_POSTFIX);
	else
	{
		*(pDot+1)='o';
		*(pDot+2)='b';
		*(pDot+3)='\0';
	}
}
