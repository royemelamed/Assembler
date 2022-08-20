#include <string.h>
#include "secondPass.h" /*includes assemblerArrays.h*/

/*Recived a file path and preparis an all the relevant data for crating the output files*/
validation_code firstPass(char * path);


/*Recived a line and the line number and check if is a symbol and return if yes (and save the symbol in symbolName) or no. if there is an error save it in validationFlag*/
int isSymbol(char *line,int lineCounter, char ** symbolName, validation_code *validationFlag);
