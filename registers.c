#include <string.h>
#include "registers.h"

struct {
	char registerName[REGISTER_LENGTH];
	char binary_representation[BINARY_DIGITS_PER_REGISTER];
} registers[]={
	{"r1","0001"},
	{"r2","0010"},
	{"r3","0011"},
	{"r4","0100"},
	{"r5","0101"},
	{"r6","0110"},
	{"r7","0111"},
	{"r8","1000"}
};

char * getBinaryByRegister(char name[REGISTER_LENGTH])
{
	int i=0;
	while(strcmp(registers[i].registerName,name)!=0)
		i++;
	return registers[i].binary_representation;
}

int isNameARegister(char *name)
{
	int i;
	for(i=0;i<=NUM_OF_REGISTERS;i++)
	{
		if(strcmp(registers[i].registerName,name)==0)
			return 1;
	}
	return 0;
}
