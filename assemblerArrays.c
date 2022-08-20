#include <string.h>
#include <stdlib.h>
#include "assemblerArrays.h"
#define EXTERNAL_SYMBOL_WORD_BINARY_REPRESENTETION "0000000001" /*this is the fixed represention for external symbols*/
#define DEFAULT_BINARY_CODE "0000000000"
#define DEFAULT_BINARY_CODE_WITHOUT_ARE_BITS "00000000"
#define BINARY_BASE 2
#define ZERO_CHAR_VALUE '0'
#define ONE_CHAR_VALUE '1'


int *ic=0;
int *dc=0;

/*-------------------------------internal methods decleration-------------------------------*/
void itob(int number, int maxBinaryDigits,char **finalBinaryCode);
void itobPositive(int number, int maxBinaryDigits,char **finalBinaryCode);
void itobNegative(int number, int maxBinaryDigits,char **finalBinaryCode);
/*------------------------------------------------------------------------------------------*/

void incrementInstructionCounter(int num)
{
	(*ic)+=num;
}

void incrementDataCounter(int num)
{
	(*dc)+=num;
}

void setInstructionCounter(int num)
{
	(*ic)=num;
}

void setDataCounter(int num)
{
	(*dc)=num;
}

int getInstructionCounterValue()
{
	return (*ic);
}

int getDataCounterValue()
{
	return (*dc);
}

void addInstructionWord(char command[COMMAND_NAME_LENGTH], int addressingId1, int addressingId2, char areType)
{
	char binaryCode[MAX_BITS];
	strcpy(binaryCode,getBinaryByCommand(command));
	strcat(binaryCode,getBinaryByAddressingId(addressingId1));
	strcat(binaryCode,getBinaryByAddressingId(addressingId2));
	strcat(binaryCode,getBinaryByAreType(areType));
	strcpy(instructions[(*ic)],binaryCode);
}

void addNumericWord(int number)
{
	char *binaryCode;
	binaryCode=(char *)malloc(MAX_BITS*sizeof(char *));
	strcpy(binaryCode,DEFAULT_BINARY_CODE_WITHOUT_ARE_BITS);
	itob(number,MAX_BITS-BINARY_DIGITS_PER_ARE,&binaryCode);
	strcat(binaryCode,getBinaryByAreType(ABSOLUTE_CHAR)); /*Numeric words are added with absolute char*/
	strcpy(instructions[*ic],binaryCode);
	free(binaryCode);
	
}

void addSymbolAddressWord(char *symbolName)
{
	char *binaryCode;
	binaryCode=(char *)malloc(MAX_BITS*sizeof(char *));
	strcpy(binaryCode,DEFAULT_BINARY_CODE);
	if(checkIfExternal(symbolName))
		strcpy(binaryCode,EXTERNAL_SYMBOL_WORD_BINARY_REPRESENTETION);
	else
	{
		strcpy(binaryCode,DEFAULT_BINARY_CODE_WITHOUT_ARE_BITS);
		itob(getIndexBySymbolName(symbolName), MAX_BITS-BINARY_DIGITS_PER_ARE,&binaryCode);
		strcat(binaryCode,getBinaryByAreType(RELOCATABLE_CHAR)); /*symbols address words are added with relocatable char*/
	}
	strcpy(instructions[*ic],binaryCode);
	free(binaryCode);
}

void addStructAddressWords(char *symbolName, int structIndex)
{
	addSymbolAddressWord(symbolName);
	(*ic)++;
	addNumericWord(structIndex);
	(*ic)--;
}

void addRegistersInstructionWord(char *sourceRegister, char *destinationRegister)
{
	char binaryCode[MAX_BITS];
	if(strcmp(sourceRegister,NO_REGISTER)!=0)
		strcpy(binaryCode, getBinaryByRegister(sourceRegister));
	else
		strcpy(binaryCode, NO_REGISTER);
	if(strcmp(destinationRegister,NO_REGISTER)!=0)
		strcat(binaryCode, getBinaryByRegister(destinationRegister));
	else
		strcat(binaryCode, NO_REGISTER);
	strcat(binaryCode, getBinaryByAreType(ABSOLUTE_CHAR)); /*register words are added with absolute char*/
	strcpy(instructions[*ic],binaryCode);
}

void addDataWord(int number)
{
	char *binaryCode;
	binaryCode=(char *)malloc(MAX_BITS*sizeof(char *));
	strcpy(binaryCode,DEFAULT_BINARY_CODE);
	itob(number,MAX_BITS-1, &binaryCode); /*decreasing -1 to make binary strings with 10 d*/
	strcpy(data[*dc],binaryCode);
	free(binaryCode);
}

void addStringWords(char *s)
{
	int i;
	char *binaryCode;
	binaryCode=(char *)malloc(MAX_BITS*sizeof(char *));
	strcpy(binaryCode,DEFAULT_BINARY_CODE);
	for (i=0;i<strlen(s);i++) /*validate that equals add the \0!!!*/
	{
		itob(s[i],MAX_BITS-1,&binaryCode); /*decreasing -1 to make binary strings with 10 digits*/
		strcpy(data[(*dc)+i],binaryCode);
	}
	strcpy(data[(*dc)+i],DEFAULT_BINARY_CODE);
	free(binaryCode);
}

void addStructWord(int structNumber, char *structText)
{
	addDataWord(structNumber);
	(*dc)++; /*so we won't ovveride structNumber data*/
	addStringWords(structText);
	(*dc)--; /*so we won't change *dc value to the client*/
}

void freeCounters()
{
	free(ic);
	free(dc);
}


void itob(int number, int maxBinaryDigits,char **finalBinaryCode)
/*Recived number to convert to binary and maximum digits to represent and save the convert number in finalBinaryCode*/
{
	if(number>=0)
		itobPositive(number,maxBinaryDigits, finalBinaryCode);
	else
		itobNegative(number,maxBinaryDigits, finalBinaryCode);
}

void itobPositive(int number, int maxBinaryDigits, char **finalBinaryCode)
/*Convert positive number to binary*/
{
	int i;
	for(i=maxBinaryDigits-1;i>=0 && number>0;i--) /*filling binary number in reverse*/
	{
		(*finalBinaryCode)[i]=(ZERO_CHAR_VALUE+number%BINARY_BASE);
		number/=BINARY_BASE ;
	}
}

void itobNegative(int number, int maxBinaryDigits, char **finalBinaryCode)
/*Convert negative number to binary*/
{
	int i;
	number*=(-1);
	for(i=maxBinaryDigits-1;i>=0;i--) /*creating one's complement binary representation. */
	{
		(*finalBinaryCode)[i]=(ZERO_CHAR_VALUE+(1-(number%BINARY_BASE))); /*0 will turn to 1, 1 will turn to 0, which will make inverted binary number*/
		number/=BINARY_BASE ;
	}
	for(i=maxBinaryDigits-1;i>=0 && (*finalBinaryCode)[i]!=ZERO_CHAR_VALUE;i--) /*filling binary number in reverse*/
		(*finalBinaryCode)[i]=ZERO_CHAR_VALUE; /*increasing binary number by 1*/
	if(i>0 || *finalBinaryCode[0]!=ONE_CHAR_VALUE)
		(*finalBinaryCode)[i]=ONE_CHAR_VALUE; /*finishing increasing proccess */
}

void resetInstructionsAndData()
{

	ic=(int *)malloc(sizeof(int *));
	setInstructionCounter(STARTING_VALUE_FOR_COUNTERS);
	strcpy(instructions[0],"\0");
	dc=(int *)malloc(sizeof(int *));
	setDataCounter(STARTING_VALUE_FOR_COUNTERS);
	strcpy(data[0],"\0");
}


void removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}
