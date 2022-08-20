#include "errors.h"
#include "registers.h"
#define COMMAND_NAME_LENGTH 3
#define BINARY_DIGITS_PER_COMMAND 5 /*4 binary digits and '\0' at the end of the string*/
#define BINARY_DIGITS_PER_ARE 3 /*2 binary digits and '\0' at the end of the string*/
#define BINARY_DIGITS_PER_ADDRESSING 3 /*2 binary digits and '\0' at the end of the string*/
#define COMMAND_NOT_FOUND -1 /*flag for signaling that command isn't found*/
#define FIRST_INDEX 100

typedef enum
{
	ZERO_OPERANDS=0,
	ONE_OPERAND=1,
	TWO_OPERANDS=2
} operandsNumber;

typedef enum
{
	IMMEDIATE_ADDRESSING_METHOD=0,
	DIRECT_ADDRESSING_METHOD=1,
	ADDRESS_ACCESS_ADDRESSING_METHOD=2,
	IMMEDIATE_REGISTER_ADDRESSING_METHOD=3,
	ADDRESSING_METHOD_TBD=4,
	NO_ADDRESSING_METHOD_NEEDED=-1
} addressingMethods;


typedef enum
{
	ABSOLUTE_CHAR='a',
	RELOCATABLE_CHAR='r',
	EXTERNAL_CHAR='e'
} areChars;

/*Recived a command name and return the binary representation of it*/
const char * getBinaryByCommand(char *command);


/*Recived are type and return the binary representation of it*/
const char * getBinaryByAreType(areChars type);


/*Recived addressing id and return the binary representation of it*/
const char * getBinaryByAddressingId(addressingMethods id);


/*Recived name and return if it is a command name*/
int isNameACommand(char *name);
