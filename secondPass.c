#include <stdio.h>
#include "secondPass.h"

validation_code secondPass(char * path)
{

	char line[MAX_LINE_CHARS];
	char *token, *commandName;
	FILE *fptr;
	int lineCounter;
	validation_code validationFlag=VALID, lineValidationFlag=VALID;
	setInstructionCounter(STARTING_VALUE_FOR_COUNTERS);
	fptr = fopen(path,"r");
	if (fptr == NULL) /* Unable to open file hence exit */
	{
		print_code(PATH_NOT_FOUND);
		return PATH_NOT_FOUND;
	}

	for(lineCounter=1;fgets(line, MAX_LINE_CHARS, fptr)!=NULL;lineCounter++)
	{
		lineValidationFlag=VALID;
		if(line[0]!=COMMENT_LINE_CHAR) /*to skip comment sentences*/
		{
			if((token=strchr(line, END_SYMBOL_CHAR))!= NULL) /*to ignore symbols declerations*/
			{
				if (strchr(token, SPACE_CHAR) != NULL)
					commandName=strtok(token+1,SPACE); /*token should represent command*/
				else
					commandName=strtok(token+1, END_OF_LINE); /*command represents command name*/
			}
			else if (strchr(line, SPACE_CHAR) != NULL)
				commandName=strtok(line, SPACE); /*command represents command name*/
			else
				commandName=strtok(line, END_OF_LINE); /*command represents command name*/

			if(!IS_DATA_STRING_OR_STRUCT(commandName) && !IS_EXTERN(commandName))
			{
				token=strtok(NULL,END_OF_LINE); /*token should represent params*/
				if(IS_ENTRY(commandName))
				{
					if((lineValidationFlag=DATA_IS_EMPTY(token)?MISSING_PARAM:checkSymbolName(token))==VALID)
						addEntrySymbol(token);
					else
						print_code_with_line(lineCounter,lineValidationFlag);
				}
				else
					lineValidationFlag=(getFunctionByName(commandName))(SECOND_PASS, lineCounter, token);			
			}
			if(lineValidationFlag!=VALID) /*we're saving the total validation code we can know if 1 row had error*/
				validationFlag=lineValidationFlag;
		}
	}
	
	fclose(fptr);
	return validationFlag;
}
