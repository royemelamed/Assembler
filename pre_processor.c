#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pre_processor.h"
#include "processor_commands.h" /*includes registers.h, errors.h*/
#define AFTER_MACRO_FILE_POSTFIX ".am"
#define DOT_AM_POSTFIX_LEN (strlen(AFTER_MACRO_FILE_POSTFIX)) /*length of ".am" string*/
#define MACRO_DECLERATION "macro" /*copy of action which decalres macro*/
#define END_MACRO "endmacro\n" /*copy of line which concluds macro*/
#define REQUIRED_SPACE_FLAG '&' /*char which we can implement in order to change string excpet given char. this char shouldn't be on our line, so we can use it*/
#define COMMENT_DEFENITION_CHAR ';'
#define IS_SPACE(c) ((c)==' ' || (c)== '\t' || (c)=='\r')
#define EMPTY_LINE 1
#define COMMENT_LINE 2
#define REGULAR_LINE 3 
#define LINE_IS_EMPTY(type) ((type)==EMPTY_LINE)
#define LINE_IS_COMMENT(type) ((type)==COMMENT_LINE)
#define EMPTY_STRING ""
#define SPACE " "
#define SPACE_CHAR ' '
#define END_OF_LINE_CHAR '\n'
#define END_SYMBOL_CHAR ':'
#define COMMENT_CHAR ';'


/*-------------------------------internal methods decleration-------------------------------*/
void createDotAmPath (char *path);
int isMacroNameValid(char *name);
int formatLine(char *line);
int removeSpacesFromString(char *str);
/*------------------------------------------------------------------------------------------*/

int preProcessor(char *path)
{
	char line[MAX_LINE_CHARS], macroName[MAX_LINE_CHARS];
	char *token, *afterMacroPath;
	char macroData[MAX_LINES_PER_MACRO*MAX_LINE_CHARS], fullMacro[MAX_LINES_PER_MACRO*MAX_LINE_CHARS];
	FILE *psource, *pam;
	int linesCounter=1,lineType;
	validation_code code=VALID,lineCode=VALID; /*this will alert us on errors*/
	
	/*setting up all variables for function*/
	afterMacroPath=(char *)malloc(strlen(path)+DOT_AM_POSTFIX_LEN*sizeof(char));
	psource=fopen(path,"r");
	if (psource == NULL) /* Unable to open file hence exit */
	{
		print_code(FILE_NOT_FOUND);
		return FILE_NOT_FOUND;
	}
	/*Creating the ".am" path and file*/
	strcpy(afterMacroPath,path); 
	createDotAmPath(afterMacroPath);
	pam=fopen(afterMacroPath,"w");
	clearMacroList(); /*clearing all macros previous data*/

	for(linesCounter=1;fgets(line, MAX_LINE_CHARS, psource)!=NULL;linesCounter++)
	{
		lineCode=VALID;
		lineType=formatLine(line);
		if(!LINE_IS_EMPTY(lineType))
		{
			if(LINE_IS_COMMENT(lineType))
				fputs(line,pam);
			else
			{
				strcpy(fullMacro, line); /*before breaking line, optional assembling of line*/
				if(strcmp((token=strtok(line,SPACE)),MACRO_DECLERATION)==0) /*spliting to check if token equlas to "macro"*/
				{
					strcpy(macroName,(token=strtok(NULL, EMPTY_STRING))); /*token represents macro name*/
					if(!isMacroNameValid(macroName))
						lineCode=INVALID_MACRO_NAME;
					else if(strcmp(getMacroDataByName(macroName),NOT_A_MACRO)!=0)
						lineCode=DOUBLE_MACRO_DECLERATION;
					else
					{
						for(;fgets(line, MAX_LINE_CHARS, psource)!=NULL && strcmp(line,END_MACRO)!=0;linesCounter++) /*collecting all macro data*/
						{
							lineCode=VALID;
							lineType=formatLine(line);
							if(!LINE_IS_EMPTY(lineType))
								strcat(macroData,line);
						}
						addMacro(macroName,macroData);
					}
				}
				else
				{
					strcpy(macroData,getMacroDataByName(token));
					fputs((strcmp(macroData,NOT_A_MACRO)==0)?fullMacro:macroData, pam);
					/*else, this is a macro decleration, we should write the macro commands to the file*/
				}
			}
		}
		/*reseting macro data for future macros*/
		strcpy(macroData, "");
		strcpy(fullMacro, "");
		if(lineCode!=VALID)
			print_code_with_line(linesCounter,(code=lineCode));
	}
	free(afterMacroPath);
	fclose(psource);
	fclose(pam);
	return code;
}

void createDotAmPath (char *path)
/*Create am format path based on given path*/
{
	char *pDot=strchr(path,'.');
	if(pDot==NULL) /*meaning that there isn't format for the file*/
		strcat(path,AFTER_MACRO_FILE_POSTFIX);
	else
	{
		*(pDot+1)='a';
		*(pDot+2)='m';
		*(pDot+3)='\0';
	}
}


int isMacroNameValid(char *name)
/*Recived a macro name and check if it valid*/
{
	return (!isNameACommand(name) && !isNameARegister(name) && strcmp(name,MACRO_DECLERATION)!=0 && strcmp(name,END_MACRO)!=0);
}

int formatLine(char *line)
/*Recived a line and clear white spaces in the line. line will point at first char that isn't blank space in line*/
{
	int i=0;
	char *tmp, *dotsPointer;
	tmp=line;
	/*skip spaces on start of the line*/
	while(IS_SPACE(tmp[i]) && i<strlen(tmp))
		i++;
	if(tmp[i]==END_OF_LINE_CHAR)
		return EMPTY_LINE;
	else if(tmp[i]==COMMENT_CHAR)
	{
		line=(tmp+i);
		return COMMENT_LINE;
	}
	/*to skip label name*/
	dotsPointer=strchr(tmp,END_SYMBOL_CHAR);
	if(dotsPointer!=NULL)
		tmp=dotsPointer+1;
	/*skip spaces before command name*/
	while(IS_SPACE(tmp[i]) && i<strlen(tmp))
		i++;
	/*skip command name*/
	while(!IS_SPACE(tmp[i]) && i<strlen(tmp))
		i++;
	if(i<strlen(tmp)) /*meaning we passed trough command name and not finished line*/
	{
		tmp [i]=REQUIRED_SPACE_FLAG;
		removeSpacesFromString(line);
		i = (int)(strchr(line, REQUIRED_SPACE_FLAG) - line);
		line[i]=SPACE_CHAR; /*so we can differ command name from params*/
	}
	else
		removeSpacesFromString(line);
	return REGULAR_LINE;
}

int removeSpacesFromString(char *str)
/*Recived a string and remove the all spaces from it*/
{
	int count=0;
	char *src, *dst;
	for(src=dst=str;*src!='\0';src++)
	{
		(*dst)=*src;
		if(!IS_SPACE(*dst))
			dst++;
		else
			count++;
	}
	(*dst)='\0';
	return count;
}
