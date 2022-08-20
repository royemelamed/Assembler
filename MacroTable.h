#define MAX_LINE_CHARS 80
#define MAX_LINES_PER_MACRO 500
#define NOT_A_MACRO "not macro" /*note: macro name shouldn't tested with space, so we can be sure that this definition won't be tested on any case*/

/*Recived a macro name and macro data and add the macro to the macro table*/
void addMacro(char *name, char *data);


/*Recived a macro name and returns the macrro data (if the name exist. if not return NOT_A_MACRO)*/
const char * getMacroDataByName(char *name);


/*Clear all the macro list*/
void clearMacroList();
