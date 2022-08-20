#include "processor_commands.h" /*includes errors.h*/
#define MAX_LABEL_CHARS 30
#define INSTRUCTION_TYPE 'i'
#define DATA_TYPE 'd'

/*Recived a name, symbol type, are type and index, and add the symbol to the symbol table*/
void addSymbol(char *name, char symbolType, char areType, int index);

/*Clear all the the symbol table*/
void resetSymbolsTable();

/*Recived a symbol name and return the index of the symbol (if it exist. if not retrun 0)*/
int getIndexBySymbolName(char *name);

/*Check if the name is already saved as symbol*/
int isSymbolDeclared(char *name);

/*Recived a symbol name and return if it is an external symbol*/
int checkIfExternal(char *name);


/*Recived a symbol name and return if it is an relocatable symbol*/
int checkIfRelocatable(char *name);


/*Recived a symbol name and return the are type of the symbol*/
char getAreTypeBySymbolName(char *name);


/*Recived a symbol name and return if the symbol name is valid*/
validation_code checkSymbolName(char *name);


/*Update all symbols indexes after first pass (step 17, page 45)*/
void updateSymbolsWithInstructionCounter(int counter);
