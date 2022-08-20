#define REGISTER_LENGTH 3 /*2 chars per register name, and '\0' at the end of the string*/
#define BINARY_DIGITS_PER_REGISTER 5 /*register is represented by 4 binary digits in the word, and '\0' at the end of the string*/
#define NUM_OF_REGISTERS 8
#define NO_REGISTER "0000" /*binaric representation for future words without register*/

/*Recived a register name and returns the binary number of the register*/
char * getBinaryByRegister(char name[REGISTER_LENGTH]);

/*Recived a name and returns if it is a name of register*/
int isNameARegister(char *name);
