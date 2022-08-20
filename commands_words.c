#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "commands_words.h"
#define COMMA_CHAR ','
#define IS_SECOND_PASS (passNumber==SECOND_PASS)
#define VALIDATE_PARAM(param, method) ((method)==ADDRESSING_METHOD_TBD && (code=checkSymbolAsParam((param)))!=VALID)
#define FIRST_CHAR_IS_COMMA(param) ((param)[0]==COMMA_CHAR)
#define ONE_WORD 1
#define TWO_WORDS 2
#define STRUCT_NUMBER 1
#define STRUCT_STRING 2
#define STRUCT_NUMBER_CHAR '1'
#define STRUCT_STRING_CHAR '2'
#define FLAG_ON 1
#define FLAG_OFF 0
#define DOT_CHAR '.'
#define NEGATIVE_SIGN '-'
#define POSITIVE_SIGN '+'
#define ZERO_CHAR '0'


struct {
	char command[COMMAND_NAME_LENGTH];
	validation_code (*commandFuncsPtr)(int, int, char *);
} commandsFunctions[]={
	{"mov", funcMov},
	{"cmp", funcCmp},
	{"add", funcAdd},
	{"sub", funcSub},
	{"not", funcNot},
	{"clr", funcClr},
	{"lea", funcLea},
	{"inc", funcInc},
	{"dec", funcDec},
	{"jmp", funcJmp},
	{"bne", funcBne},
	{"get", funcGet},
	{"prn", funcPrn},
	{"jsr", funcJsr},
	{"rts", funcRts},
	{"hlt", funcHlt}
};

typedef enum
{
	NO_SKIP,
	SKIP_LABEL,
	SKIP_STRUCT
} skips;

/*-------------------------------internal methods decleration-------------------------------*/
void addWords(char *commandName, int passNumber,char *firstParam, addressingMethods firstMethod, skips firstSkip, char *secondParam, addressingMethods secondMethod, skips secondSkip);
addressingMethods getAdressingMethodByName(int passNumber, char *name, validation_code *code, int *structFlag);
validation_code checkSymbolAsParam(char *name);
int checkStructName(char *name);
/*------------------------------------------------------------------------------------------*/

commandFuncsPtr getFunctionByName(char *command)
{
	int i=0;
	while(strcmp(commandsFunctions[i].command,command)!=0)
		i++;
	return commandsFunctions[i].commandFuncsPtr;
}

validation_code funcMov(int passNumber, int line, char *params)
{
	char *firstParam, *secondParam;
	skips firstSkip=NO_SKIP, secondSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod,secondMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,NEXT_PARAM_DELIMITER);
	secondParam=strtok(NULL,END_OF_LINE);
	if(firstParam == NULL ||secondParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber, firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*dealing with second param*/
	secondMethod=getAdressingMethodByName(passNumber, secondParam,&code, &structFlag);
	if(!IS_SECOND_PASS && secondMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		secondSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(secondMethod==IMMEDIATE_ADDRESSING_METHOD) /*we can't assign param to direct number*/
		return BAD_OPERAND_DECLERATION;
	else if(VALIDATE_PARAM(firstParam,firstMethod) || VALIDATE_PARAM(secondParam,secondMethod)) /*we wish to check that the name of params are valid*/
			return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("mov", passNumber,firstParam, firstMethod, firstSkip, secondParam, secondMethod, secondSkip);
	return code;
}

validation_code funcCmp(int passNumber, int line, char *params)
{
	char *firstParam, *secondParam;
	skips firstSkip=NO_SKIP, secondSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod,secondMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,NEXT_PARAM_DELIMITER);
	secondParam=strtok(NULL,END_OF_LINE);
	if(firstParam == NULL ||secondParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber, firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*dealing with second param*/
	secondMethod=getAdressingMethodByName(passNumber,secondParam,&code, &structFlag);
	if(!IS_SECOND_PASS && secondMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		secondSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod) || VALIDATE_PARAM(secondParam,secondMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("cmp", passNumber,firstParam, firstMethod, firstSkip, secondParam, secondMethod, secondSkip);
	return code;
}

validation_code funcAdd(int passNumber, int line, char *params)
{
	char *firstParam, *secondParam;
	skips firstSkip=NO_SKIP, secondSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod,secondMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,NEXT_PARAM_DELIMITER);
	secondParam=strtok(NULL,END_OF_LINE);
	if(firstParam == NULL ||secondParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber, firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*dealing with second param*/
	secondMethod=getAdressingMethodByName(passNumber, secondParam,&code, &structFlag);
	if(!IS_SECOND_PASS && secondMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		secondSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(secondMethod==IMMEDIATE_ADDRESSING_METHOD) /*we can't add param to direct number*/
		return BAD_OPERAND_DECLERATION;
	else if(VALIDATE_PARAM(firstParam,firstMethod) || VALIDATE_PARAM(secondParam,secondMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("add", passNumber,firstParam, firstMethod, firstSkip, secondParam, secondMethod, secondSkip);
	return code;
}

validation_code funcSub(int passNumber, int line, char *params)
{
	char *firstParam, *secondParam;
	skips firstSkip=NO_SKIP, secondSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod,secondMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,NEXT_PARAM_DELIMITER);
	secondParam=strtok(NULL,END_OF_LINE);
	if(firstParam == NULL ||secondParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber, firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*dealing with second param*/
	secondMethod=getAdressingMethodByName(passNumber, secondParam,&code, &structFlag);
	if(!IS_SECOND_PASS && secondMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		secondSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod) || VALIDATE_PARAM(secondParam,secondMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("sub", passNumber,firstParam, firstMethod, firstSkip, secondParam, secondMethod, secondSkip);
	return code;
}

validation_code funcNot(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber, firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("not", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcClr(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;

	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("clr", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcLea(int passNumber, int line, char *params)
{
	char *firstParam, *secondParam;
	skips firstSkip=NO_SKIP, secondSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod,secondMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,NEXT_PARAM_DELIMITER);
	secondParam=strtok(NULL,END_OF_LINE);
	if(firstParam == NULL ||secondParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*dealing with second param*/
	secondMethod=getAdressingMethodByName(passNumber,secondParam,&code, &structFlag);
	if(!IS_SECOND_PASS && secondMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		secondSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(secondMethod==IMMEDIATE_ADDRESSING_METHOD) /*we can't assign param to direct number*/
		return BAD_OPERAND_DECLERATION;
	else if(VALIDATE_PARAM(firstParam,firstMethod) || VALIDATE_PARAM(secondParam,secondMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("lea", passNumber,firstParam, firstMethod, firstSkip, secondParam, secondMethod, secondSkip);
	return code;
}

validation_code funcInc(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("inc", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcDec(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("dec", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcJmp(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("jmp", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}


validation_code funcBne(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("bne", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcGet(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("get", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcPrn(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("prn", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcJsr(int passNumber, int line, char *params)
{
	char *firstParam;
	skips firstSkip=NO_SKIP;
	validation_code code=VALID;
	addressingMethods firstMethod;
	int structFlag=FLAG_OFF;
	/*spliting params*/
	firstParam=strtok(params,END_OF_LINE);
	if(firstParam == NULL || FIRST_CHAR_IS_COMMA(params))
		return MISSING_PARAM;
	/*dealing with first param*/
	firstMethod=getAdressingMethodByName(passNumber,firstParam,&code, &structFlag);
	if(!IS_SECOND_PASS && firstMethod==ADDRESSING_METHOD_TBD) /*to skip unknown labels on first pass*/
		firstSkip=structFlag? SKIP_STRUCT:SKIP_LABEL;
	/*command validations*/
	if(VALIDATE_PARAM(firstParam,firstMethod)) /*we wish to check that the name of params are valid*/
		return code;
	else if(code!=VALID && (IS_SECOND_PASS || code!=BAD_OPERAND_DECLERATION)) /*to skip unknown labels on first pass*/
			return code;
	else /*add words to arrays*/
		addWords("jsr", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, firstParam, firstMethod, firstSkip);
	return code;
}

validation_code funcRts(int passNumber, int line, char *params)
{
	validation_code code=VALID;
	/*command validations*/
	if(params != NULL)
		return EXTRA_TEXT;
	else if(code!=VALID)
		return code;
	else /*add words to arrays*/
		addWords("rts", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP);
	return code;
}

validation_code funcHlt(int passNumber, int line, char *params)
{
	validation_code code=VALID;
	/*command validations*/
	if(params != NULL)
		return EXTRA_TEXT;
	else if(code!=VALID)
		return code;
	else /*add words to arrays*/
		addWords("hlt", passNumber,NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP, NO_PARAM_NEEDED, NO_ADDRESSING_METHOD_NEEDED, NO_SKIP);
	return code;
}

addressingMethods getAdressingMethodByName(int passNumber, char *name, validation_code *code, int *structFlag)
/*Reciverd param name and return the addressing method of it.
passNumber = SECOND_PASS or FIRST_PASS
NOTE: The function updates code pointer in case of error and update the struct flag if detected*/
{
	int structIndex=0;
	char tmp[MAX_LINE_CHARS];
	char *symbolName, *nameTmp;
	symbolName=(char *)malloc(MAX_LABEL_CHARS*sizeof(char *));
	nameTmp=(char *)malloc(MAX_LINE_CHARS*sizeof(char *));
	strcpy(nameTmp,name);
	/*immediate addressing method*/
	if(nameTmp[0]==DIRECT_NUMBER_PREFIX)
	{
		strcpy(tmp,nameTmp+1); /*to pass DIRECT_NUMBER_PREFIX*/
		if(isNumber(tmp))
			return IMMEDIATE_ADDRESSING_METHOD;
		else
		{
			(*code)=OPERAND_NOT_NUMBER;
			return NO_ADDRESSING_METHOD_NEEDED;
		}
	}
	/*register addressing method*/
	if(isNameARegister(nameTmp))
		return IMMEDIATE_REGISTER_ADDRESSING_METHOD;
	/*direct or address access addressing method*/
	(*structFlag)=(strchr(nameTmp,STRUCT_DOT_CHR)!=NULL);
	if(*structFlag)
	{
		strcpy(symbolName,strtok(nameTmp,STRUCT_DOT_STR));
		structIndex=atoi(strtok(NULL, END_OF_LINE));
	}
	else
		strcpy(symbolName,nameTmp);
	if(getIndexBySymbolName(symbolName) || checkIfExternal(symbolName))
	{
		if(!(*structFlag))
			return DIRECT_ADDRESSING_METHOD;
		else
		{
			if(structIndex==STRUCT_NUMBER || structIndex==STRUCT_STRING)
				return ADDRESS_ACCESS_ADDRESSING_METHOD;
			else
			{
				(*code)=WRONG_STRUCT_FIELD;
				return NO_ADDRESSING_METHOD_NEEDED;	
			}
		}
	}
	free(symbolName);
	if(passNumber!=FIRST_PASS)
	{
		(*code)=BAD_OPERAND_DECLERATION; /*not valid operand (no addressing method detected)*/
		return NO_ADDRESSING_METHOD_NEEDED;
	}
	return ADDRESSING_METHOD_TBD;
}

void addWords(char *commandName, int passNumber,char *firstParam, addressingMethods firstMethod, skips firstSkip, char *secondParam, addressingMethods secondMethod, skips secondSkip)
/*Add all the words of one line from file*/
{
	int registerFlag=FLAG_OFF, firstTmp=firstMethod, secondTmp=secondMethod;
	if(firstSkip)
		firstTmp=firstSkip;
	if(secondSkip)
		secondTmp=secondSkip;
	addInstructionWord(commandName,firstTmp,secondTmp,ABSOLUTE_CHAR);
	incrementInstructionCounter(ONE_WORD);
	switch(firstMethod)
	{
		case IMMEDIATE_ADDRESSING_METHOD:
			addNumericWord(atoi(strchr(firstParam, DIRECT_NUMBER_PREFIX)+1));
			incrementInstructionCounter(ONE_WORD);
			break;
		case DIRECT_ADDRESSING_METHOD:
			addSymbolAddressWord(firstParam);
			if(IS_SECOND_PASS && checkIfExternal(firstParam))
				addExternSymbol(firstParam,getInstructionCounterValue());
			incrementInstructionCounter(ONE_WORD);
			break;
		case ADDRESS_ACCESS_ADDRESSING_METHOD:
			addStructAddressWords(strtok(firstParam,STRUCT_DOT_STR),atoi(strchr(firstParam,STRUCT_DOT_CHR)+1));
			incrementInstructionCounter(TWO_WORDS);
			break;
		case IMMEDIATE_REGISTER_ADDRESSING_METHOD:
			registerFlag=FLAG_ON;
			if(secondMethod==IMMEDIATE_REGISTER_ADDRESSING_METHOD)
				addRegistersInstructionWord(firstParam,secondParam);
			else
				addRegistersInstructionWord(firstParam,NO_REGISTER);
			incrementInstructionCounter(ONE_WORD);
			break;
		case ADDRESSING_METHOD_TBD:
			incrementInstructionCounter(firstSkip);
			break;
		default:
			break;
	}
	switch(secondMethod)
	{
		case IMMEDIATE_ADDRESSING_METHOD:
			addNumericWord(atoi(strchr(secondParam, DIRECT_NUMBER_PREFIX)+1));
			incrementInstructionCounter(ONE_WORD);
			break;
		case DIRECT_ADDRESSING_METHOD:
			addSymbolAddressWord(secondParam);
			if(IS_SECOND_PASS && checkIfExternal(secondParam))
				addExternSymbol(secondParam,getInstructionCounterValue());
			incrementInstructionCounter(ONE_WORD);
			break;
		case ADDRESS_ACCESS_ADDRESSING_METHOD:
			addStructAddressWords(strtok(secondParam,STRUCT_DOT_STR),atoi(strchr(secondParam,STRUCT_DOT_CHR)+1));
			incrementInstructionCounter(TWO_WORDS);
			break;
		case IMMEDIATE_REGISTER_ADDRESSING_METHOD:
			if(!registerFlag)
			{
				addRegistersInstructionWord(NO_REGISTER,secondParam);
				incrementInstructionCounter(ONE_WORD);
			}
			break;
		case ADDRESSING_METHOD_TBD:
			incrementInstructionCounter(secondSkip);
			break;
		default:
			break;
	}
} 

int isNumber(char *nameToCheck)
{
	int i=0;
	if(nameToCheck[i]==NEGATIVE_SIGN || nameToCheck[i]==POSITIVE_SIGN)
		i++;
	else if(nameToCheck[i]==ZERO_CHAR) /*to make sure 0 numbers are considered as numbers*/
		return 1;
	while(nameToCheck[i]!='\0' && isdigit(nameToCheck[i]))
		i++;
	return (nameToCheck[i]=='\0');
}

validation_code checkSymbolAsParam(char *name)
{
	if(checkSymbolName(name)==VALID)
		return VALID;
	if(checkStructName(name))
		return VALID;
	return INVALID_SYMBOL_NAME;
}

int checkStructName(char *name)
{
	char *ptr;
	ptr=strchr(name,DOT_CHAR);
	if(ptr==NULL || (ptr+1)==NULL)
		return 0;
	if((*(ptr+1))!='\0')
		if( (*(ptr+1))==STRUCT_NUMBER_CHAR || (*(ptr+1))==STRUCT_STRING_CHAR )
			return 1;
	return 0;
}

