#include <string.h>
#include "processor_commands.h"
#define NUM_OF_COMMANDS 16


struct {
	char command[COMMAND_NAME_LENGTH];
	int action_decimal_code;
	char binary_representation[BINARY_DIGITS_PER_COMMAND]; /*we have only 16 commands*/
	operandsNumber operandsNumber;
} commands[]={
	{"mov",0,"0000",TWO_OPERANDS},
	{"cmp",1,"0001",TWO_OPERANDS},
	{"add",2,"0010",TWO_OPERANDS},
	{"sub",3,"0011",TWO_OPERANDS},
	{"not",4,"0100",ONE_OPERAND},
	{"clr",5,"0101",ONE_OPERAND},
	{"lea",6,"0110",TWO_OPERANDS},
	{"inc",7,"0111",ONE_OPERAND},
	{"dec",8,"1000",ONE_OPERAND},
	{"jmp",9,"1001",ONE_OPERAND},
	{"bne",10,"1010",ONE_OPERAND},
	{"get",11,"1011",ONE_OPERAND},
	{"prn",12,"1100",ONE_OPERAND},
	{"jsr",13,"1101",ONE_OPERAND},
	{"rts",14,"1110",ZERO_OPERANDS},
	{"hlt",15,"1111",ZERO_OPERANDS}
};

struct {
	areChars type;
	char binary_representation[BINARY_DIGITS_PER_ARE];
} areBits[]={
	{ABSOLUTE_CHAR,"00"},
	{EXTERNAL_CHAR,"01"},
	{RELOCATABLE_CHAR,"10"}
};

struct {	
	addressingMethods adressingMethod;
	char binary_representation[BINARY_DIGITS_PER_ADDRESSING];
} addressingBits[]={
	{IMMEDIATE_ADDRESSING_METHOD,"00"},
	{DIRECT_ADDRESSING_METHOD,"01"},
	{ADDRESS_ACCESS_ADDRESSING_METHOD,"10"},
	{IMMEDIATE_REGISTER_ADDRESSING_METHOD,"11"},
	{NO_ADDRESSING_METHOD_NEEDED, "00"} /*for commands without any extra paramter, we will add 00 in words*/
};

const char *getBinaryByCommand(char *command)
{
	int i=0;
	while(strcmp(commands[i].command,command)!=0)
		i++;
	return commands[i].binary_representation;
}

const char * getBinaryByAreType(areChars type)
{
	int i=0;
	while(areBits[i].type!=type)
		i++;
	return areBits[i].binary_representation;
}

const char * getBinaryByAddressingId(addressingMethods id)
{
	int i=0;
	while(addressingBits[i].adressingMethod!=id)
		i++;
	return addressingBits[i].binary_representation;
}

int isNameACommand(char *name)
{
	int i=0;
	while(strcmp(commands[i].command,name)!=0 && i<NUM_OF_COMMANDS)
		i++;
	return i<NUM_OF_COMMANDS;
}
