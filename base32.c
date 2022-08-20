#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "base32.h"
#define SIZE_OF_FINAL_FILE_LINE() (strlen("\t")+4) /*we have 4 32 base chars per line*/
#define BASE 32 /*the base which we are working in*/
#define SPACE ' '


struct {
	int char_decimal_code;
	char base_char	;
	char binary_representation[BINARY_DIGITS_PER_32CHAR];

} base32[]={
	{0,'!',"00000"},
	{1,'@',"00001"},
	{2,'#',"00010"},
	{3,'$',"00011"},
	{4,'%',"00100"},
	{5,'^',"00101"},
	{6,'&',"00110"},
	{7,'*',"00111"},
	{8,'<',"01000"},
	{9,'>',"01001"},
	{10,'a',"01010"},
	{11,'b',"01011"},
	{12,'c',"01100"},
	{13,'d',"01101"},
	{14,'e',"01110"},
	{15,'f',"01111"},
	{16,'g',"10000"},
	{17,'h',"10001"},
	{18,'i',"10010"},
	{19,'j',"10011"},
	{20,'k',"10100"},
	{21,'l',"10101"},
	{22,'m',"10110"},
	{23,'n',"10111"},
	{24,'o',"11000"},
	{25,'p',"11001"},
	{26,'q',"11010"},
	{27,'r',"11011"},
	{28,'s',"11100"},
	{29,'t',"11101"},
	{30,'u',"11110"},
	{31,'v',"11111"}
};

char getBaseCharBy5Binary(char binary[BINARY_DIGITS_PER_32CHAR])
{
	int i=0;
	while(strcmp(base32[i].binary_representation,binary)!=0)
		i++;
	return base32[i].base_char;
}

void getBaseCharsBy10Binary(char *binary, char finalCode[MAX_32_NUMBER_LEN])
{
	int i;
	char *firstBinary, *secondBinary;
	
	firstBinary=(char *)malloc((BINARY_DIGITS_PER_32CHAR+1)*sizeof(char *));
	for(i=0;i<BINARY_DIGITS_PER_32CHAR;i++)
		firstBinary[i]=binary[i];
	firstBinary[i]='\0';
	finalCode[0]=getBaseCharBy5Binary(firstBinary);
	secondBinary=(binary+BINARY_DIGITS_PER_32CHAR);
	finalCode[1]=getBaseCharBy5Binary(secondBinary);
	free(firstBinary);
}

char getBaseCharsById(int id)
{
	return base32[id].base_char;
}

void getBaseCharsByDecimal(int decimal, char finalCode[MAX_32_NUMBER_LEN])
{
	finalCode[0]=(decimal>BASE)?getBaseCharsById(decimal/BASE):SPACE;
	finalCode[1]=getBaseCharsById(decimal%BASE);
}
