#include "externEntryTables.h" /*includes errors.h*/
#define MAX_ROWS 5000 /*as insructed, we can define max rows for optimal programming on 5000 words!*/
#define MAX_BITS 11 /*10 is the max bits per intruction or data, plus 1 for '\0' char*/
#define INSTRUCTIONS_WORD 'i' /*if you wish to add instruction word, send 'i' as charcter to the relevant methods*/
#define DATA_WORD 'd' /*if you wish to add data word, send 'd' as charcter to the relevant methods*/
#define STARTING_VALUE_FOR_COUNTERS 0

char instructions[MAX_ROWS][MAX_BITS];
char data[MAX_ROWS][MAX_BITS]; 

/*Increment to data counter num*/
void incrementDataCounter(int num);


/*Increment to instruction counter num*/
void incrementInstructionCounter(int num);


/*Set to data counter new vlaue, num*/
void setDataCounter(int num);


/*Set to instruction counter new vlaue, num*/
void setInstructionCounter(int num);


/*Return the data counter*/
int getDataCounterValue();


/*Return the instruction counter*/
int getInstructionCounterValue();


/*Add a single command word to instructions array*/
void addInstructionWord(char command[COMMAND_NAME_LENGTH], int addressingId1, int addressingId2, char areType);


/*Add a single numeric number (which presentes with '#') as word to instructions array*/
void addNumericWord(int number);


/*Add a single symbol address as word to instructions array*/
void addSymbolAddressWord(char *symbolName);


/*Add a struct symbol address as word to instructions array*/
void addStructAddressWords(char *symbolName, int structIndex);


/*Add a register (or registers) representions word to instructions array.
send NO_REGISTER on each parameter to signal that the param does not contain register*/
void addRegistersInstructionWord(char *sourceRegister, char *destinationRegister);


/*Add a single numeric number as single word to the data array*/
void addDataWord(int number);


/*Add a single string as words to the data array*/
void addStringWords(char *s);


/*Add a single struct (number & string) as words to the data array*/
void addStructWord(int structNumber, char *structText);


/*Reset all arrays and counters to default.*/
void resetInstructionsAndData();


/*Free all counters from memory*/
void freeCounters();

/*Function to remove all occurrences of garbage chars from string*/
void removeChar(char *str, char garbage);
