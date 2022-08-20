#include <string.h>
#include "commands_words.h" /*includes assemblerArrays.h, errors.h*/
#define DATA_IS_EMPTY(data) ((data)==NULL || strcmp((data), "\n")==0)



/*Updates the machine code of the operands that use symbols, using the symbol values ​​from the symbol table. At the end of the second pass, the program will be completely translated into machine code*/
validation_code secondPass(char *path);
