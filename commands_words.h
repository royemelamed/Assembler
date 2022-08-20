#include "assemblerArrays.h"
#define FIRST_PASS 1
#define SECOND_PASS 2
#define DATA (".data")
#define STRING (".string")
#define STRUCT (".struct")
#define ENTRY (".entry")
#define EXTERN (".extern")
#define IS_DATA(command) (strcmp(DATA,(command))==0)
#define IS_STRING(command) (strcmp(STRING,(command))==0)
#define IS_STRUCT(command) (strcmp(STRUCT,(command))==0)
#define IS_ENTRY(command) (strcmp(ENTRY,(command))==0)
#define IS_EXTERN(command) (strcmp(EXTERN,(command))==0)
#define IS_DATA_STRING_OR_STRUCT(command) (IS_DATA(command) || IS_STRING(command) || IS_STRUCT(command))
#define IS_ENTRY_OR_EXTERN(command) (IS_ENTRY(command) || IS_EXTERN(command))
#define COMMENT_LINE_CHAR ';'
#define END_SYMBOL_CHAR ':'
#define END_SYMBOL_STRING ":"
#define IC_AND_DC_DEFULT_VALUE 0
#define SPACE " "
#define SPACE_CHAR ' '
#define NEXT_PARAM_DELIMITER ","
#define NEXT_PARAM_DELIMITER_CHAR ','
#define STRING_WRAPPER_CHAR '\"'
#define END_OF_LINE "\n"
#define END_OF_LINE_CHAR '\n'
#define DIRECT_NUMBER_PREFIX '#'
#define STRUCT_DOT_CHR '.'
#define STRUCT_DOT_STR "."
#define NO_PARAM_NEEDED ""
#define APOSTROPH_CHAR '\"'
#define TAB_CHAR '\t'
#define VERTICAL_TAB_CHAR '\r'





/*commandFuncsPtr is a pointer to function thet recived 2 int and string, and returns validation code*/
typedef validation_code (*commandFuncsPtr)(int, int, char *);

/*Recived a command name and return pointer to commandFuncsPtr function*/
commandFuncsPtr getFunctionByName(char *command);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "mov" command with them. returns validation_code*/
validation_code funcMov(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "cmp" command with them. returns validation_code*/
validation_code funcCmp(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "add" command with them. returns validation_code*/
validation_code funcAdd(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "sub" command with them. returns validation_code*/
validation_code funcSub(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "not" command with them. returns validation_code*/
validation_code funcNot(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "clr" command with them. returns validation_code*/
validation_code funcClr(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "lea" command with them. returns validation_code*/
validation_code funcLea(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "inc" command with them. returns validation_code*/
validation_code funcInc(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "dec" command with them. returns validation_code*/
validation_code funcDec(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "jmp" command with them. returns validation_code*/
validation_code funcJmp(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "bne" command with them. returns validation_code*/
validation_code funcBne(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "get" command with them. returns validation_code*/
validation_code funcGet(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "prn" command with them. returns validation_code*/
validation_code funcPrn(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "jsr" command with them. returns validation_code*/
validation_code funcJsr(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "rts" command with them. returns validation_code*/
validation_code funcRts(int passNumber, int line, char *params);

/*Recived pass number (FIRST_PASS or SECOND_PASS), the line number and params and build a words of "hlt" command with them. returns validation_code*/
validation_code funcHlt(int passNumber, int line, char *params);

int isNumber(char *nameToCheck);

