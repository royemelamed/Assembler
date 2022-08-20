#include <stdio.h>
#include <stdlib.h>
#include "firstPass.h"
#define MAX_SYMBOL_LENGTH 80
#define IS_SYMBOL 1
#define IS_NOT_SYMBOL 0
#define INCREMENT_DATA_COUNTER_FOR_STRUCT 2 /* +1 - for the string. +1 - for the number = +2*/
#define INCREMENT_DATA_COUNTER_FOR_STRING 1
#define INCREMENT_DATA_COUNTER_FOR_DATA 1 /*+1 for '\0' char*/
#define MISSING_PARAM_FORMAT ",,"

/*decleration of internal methods*/ 
int isSymbol(char *,int , char ** , validation_code *);
validation_code checkString(char *name);


validation_code firstPass(char *path)
{
	int isSymbolFlag, structNumber;
	char *symbolName, *token, *data, *command, *structText, *externSymbol,*tmp;
	char line[MAX_LINE_CHARS];
	FILE *fileOpen;
	validation_code lineValidationFlag=VALID,validationFlag = VALID;
	int lineCounter;
	/*opening file*/
	fileOpen = fopen(path,"r");
	if(fileOpen==NULL)
	{
		print_code(PATH_NOT_FOUND);
		return PATH_NOT_FOUND;
	}	
	/*reset all counters*/
	resetInstructionsAndData();
	resetSymbolsTable();
	clearExternTable();
	clearEntryTable();
	symbolName=(char *)malloc(MAX_SYMBOL_LENGTH*sizeof(char *));
	/*first pass on file*/
	for(lineCounter=1;fgets(line, MAX_LINE_CHARS, fileOpen) != NULL;lineCounter++)
	{
		lineValidationFlag=VALID;
		if(line[0]!=COMMENT_LINE_CHAR) /*to skip comment sentences*/
		{
			isSymbolFlag = isSymbol(line,lineCounter, &tmp, &lineValidationFlag);
			strcpy(symbolName, tmp);
			/*skip labels declerations*/
			if((token=strchr(line, END_SYMBOL_CHAR))==NULL)
				token=line;
			else
				token++; /*to skip symbol char*/
			command = strtok(token, (strchr(token, SPACE_CHAR) != NULL)?SPACE:END_OF_LINE); /*command represents command name*/
			if(IS_DATA_STRING_OR_STRUCT(command))
			{
				if(isSymbolFlag)
					addSymbol(symbolName, DATA_TYPE, RELOCATABLE_CHAR, FIRST_INDEX+getDataCounterValue());
				data = strtok(NULL, SPACE); /*data represents all params*/
				if(DATA_IS_EMPTY(data))
					lineValidationFlag = MISSING_PARAM;
				else if(IS_DATA(command))
				{	
					if(strstr(data,MISSING_PARAM_FORMAT)!=NULL)
						lineValidationFlag = MISSING_PARAM;
					else 
						for(token=strtok(data,NEXT_PARAM_DELIMITER);token!=NULL;token=strtok(NULL, NEXT_PARAM_DELIMITER))
						{
							removeChar(token, END_OF_LINE_CHAR);
							if(isNumber(token))
							{
								addDataWord(atoi(token)); /*token represemts 1 param*/
								incrementDataCounter(INCREMENT_DATA_COUNTER_FOR_DATA);
							}
							else
								lineValidationFlag = OPERAND_NOT_NUMBER;
						}
				}
				else if(IS_STRING(command))
				{
					if((lineValidationFlag=checkString(data))==VALID)
					{
						removeChar(data, STRING_WRAPPER_CHAR);
						removeChar(data, END_OF_LINE_CHAR);
						addStringWords(data);
						incrementDataCounter(strlen(data)+INCREMENT_DATA_COUNTER_FOR_STRING);
					}
				}
				else /*IS_STRUCT*/
				{
					lineValidationFlag=((structText=strchr(data,NEXT_PARAM_DELIMITER_CHAR))!=NULL)? checkString(++structText):MISSING_PARAM;
					/*"++" to skip NEXT_PARAM_DELIMITER_CHAR*/
					if(!isNumber((token=strtok(data,NEXT_PARAM_DELIMITER))))
						lineValidationFlag=OPERAND_NOT_NUMBER;
					if(lineValidationFlag==VALID)
					{

						structNumber = atoi(token);
						removeChar(structText, STRING_WRAPPER_CHAR);
						removeChar(structText, END_OF_LINE_CHAR);
						addStructWord(structNumber, structText);
						incrementDataCounter(strlen(structText) + INCREMENT_DATA_COUNTER_FOR_STRUCT);
					}
				}
			}
			else if(IS_EXTERN(command))
			{
				externSymbol = strtok(NULL, END_OF_LINE);
				if(DATA_IS_EMPTY(externSymbol))
					lineValidationFlag = MISSING_PARAM;
				else if((lineValidationFlag=checkSymbolName(externSymbol))==VALID)
					addSymbol(externSymbol, INSTRUCTION_TYPE, EXTERNAL_CHAR, EXTERN_SYMBOL_INDEX);
			}
			else if(!IS_ENTRY(command)) /*add to instruction*/
			{
				if(isSymbolFlag)
					addSymbol(symbolName, INSTRUCTION_TYPE, RELOCATABLE_CHAR, FIRST_INDEX+getInstructionCounterValue());	
				lineValidationFlag = isNameACommand(command)?(getFunctionByName(command))(FIRST_PASS, lineCounter, (data=strtok(NULL,END_OF_LINE))):UNKNOWN_COMMAND;
			}
		}
		if(lineValidationFlag!=VALID)
			print_code_with_line(lineCounter, (validationFlag=lineValidationFlag));		
	}
	free(symbolName);
	if(validationFlag == VALID)
	{
		updateSymbolsWithInstructionCounter(getInstructionCounterValue());
		validationFlag = secondPass(path);
	}
	return validationFlag;	
}

int isSymbol(char *line,int lineCounter, char ** symbolName, validation_code *validationFlag)
{
	char tmp[MAX_LINE_CHARS];
	strcpy(tmp,line);
	*symbolName = strtok(tmp, END_SYMBOL_STRING);
	if (strcmp(*symbolName, line) == 0)
		return IS_NOT_SYMBOL;
	if (((*validationFlag) = checkSymbolName(*symbolName)) != VALID)
		return IS_NOT_SYMBOL;
	if (isSymbolDeclared(*symbolName))
	{
		(*validationFlag) = SYMBOL_ALREADY_DECLARED;
		return IS_NOT_SYMBOL;
	}	
	return IS_SYMBOL;
}

validation_code checkString(char *name)
{
	int i=0;
	if(name[i]!=APOSTROPH_CHAR)
		return STRING_WITHOUT_APOSTROPH;
	while(name[i]!='\0' && name[i]!=END_OF_LINE_CHAR)
		i++;
	if(name[i]==END_OF_LINE_CHAR)
	{
		if (name[--i]==APOSTROPH_CHAR)
		{
			if(name[(i+=2)]=='\0') /*+2 - to skip APOSTROPH_CHAR and END_OF_LINE_CHAR*/
				return VALID;
		}	
		else
			return STRING_WITHOUT_APOSTROPH;
	}
	/*else we have more text than anticipated*/
	return EXTRA_TEXT;	
}
