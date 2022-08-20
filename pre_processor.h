#include "file_methods.h"
#include "MacroTable.h"


/*This program will implement all macros (if found), according to format, in the given path
The processed file will be available in the given path. with ".am" postfix.
NOTE: This method relies on the definition that macro is set properly with no user errors. we won't check any related input errors, and assume that macros are set propperly*/
int preProcessor(char *path);


/*This program will convert the given path to ".am" format.*/
void createDotAmPath (char *path);

