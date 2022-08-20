#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#define DEFAULT_SIZE 10


char *fileToCheck;

struct errors
{
	validation_code code;
	char *error_copy;

} errors[]={
	{VALID, "Valid!"},
	{FILE_NOT_FOUND,"File not found!"},
	{UNKNOWN_COMMAND,"Undefined command name"},
	{INVALID_PARAMS,"Your parameters has wrong format. please check them again"},
	{MISSING_PARAM, "Missing parameter, or comma between parameters"},
	{EXTRA_TEXT,"Extraneous text after end of command"},
	{PATH_NOT_FOUND,"Unable to open file. The Program will terminate now!"},
	{PATH_FOR_MACRO_NOT_FOUND,"Unable to implement all macros file. The Program will terminate now!"},
	{INVALID_MACRO_NAME,"you named macro with a saved word, which is forbidden!"},
	{DOUBLE_MACRO_DECLERATION,"you already declared a macro with that name"},
	{MISSING_LADDER,"you have to add a ladder before typing a number!"},
	{OPERAND_NOT_NUMBER,"you must type an integer!"},
	{SYMBOL_ALREADY_DECLARED, "A symbol with the same name has already been defined"},
	{DOUBLE_LABEL_DECLERATION,"you have already declared this label!"},
	{LABEL_NOT_FOUND,"you used an undeclared label"},
	{INVALID_LABEL_NAME,"you used an invalid name as label"},
	{INVALID_SYMBOL_NAME,"you used an invalid name for symbol"},
	{LABEL_NOT_VALID_ON_SENTENCE,"you can't add a label on this sentence"},
	{WRONG_STRUCT_FIELD,"we didn't allocate any field with this index on the particular struct"},
	{WRONG_USE_OF_REGISTER_NAME,"you can't use register in this sentence"},
	{WRONG_ADDRESSING_METHOD,"wrong combination of addressing method with the specific  command"},
	{STRING_WITHOUT_APOSTROPH,"you typed a string without any apostroph"},
	{BAD_OPERAND_DECLERATION,"you typed wrong operand"},
	{ALLOCATION_FAILED,"allocation failed! The Program will terminate now!"},
	{UNKNOWN_ERROR,"Unknown error!"}
};

void print_code(validation_code code)
{
	int i=VALID;
	while(i<UNKNOWN_ERROR && code!=errors[i-VALID].code)
		i++;
	printf("Found error in file:%s\n\t%s\n", fileToCheck,errors[i-VALID].error_copy);
}

void print_code_with_line(int line, validation_code code)
{
	int i=VALID;
	while(i<UNKNOWN_ERROR && code!=errors[i-VALID].code)
		i++;
	printf("Found error in file:%s\n\tin line %d: %s\n",fileToCheck,line, errors[i-VALID].error_copy);
}


void updateProcessedFile(char *path)
{
	if(fileToCheck==NULL)
		fileToCheck=(char *)malloc(DEFAULT_SIZE*sizeof(char *));
	else
		free(fileToCheck);
	fileToCheck=(char *)malloc(strlen(path)*sizeof(char *));
	strcpy(fileToCheck,path);	
}
