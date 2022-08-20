#include "SymbolsTable.h" /*includes assemblerArrays.h, errors.h*/
#define EXTERN_SYMBOL_INDEX -1


/*Recived a symbol name and adress, and add the symbol in extern format*/
void addExternSymbol(char *name, int decimalAdress);


/*Recived a symbol name and adress, and add the symbol in entry format*/
void addEntrySymbol(char *name);


/*Recived symbol name and return the adrres of the extern symbol (if it exist. if not return 0)*/
const int getExternAdressByName(char *name);


/*Recived adress of extern symbol and saves the symbol name in symbolName (if it exist)*/
const validation_code getExternNameByAdress(int adress, char **symbolName);


/*Recived symbol name and return the adrres of the extern symbol (if it exist. if not return 0)*/
const int getEntryAdressByName(char *name);


/*Recived adress of entry symbol and saves the symbol name in symbolName (if it exist)*/
const validation_code getEntryNameByAdress(int adress, char **symbolName);


/*Clear the extern table*/
void clearExternTable();


/*Clear the entry table*/
void clearEntryTable();


/*Recived a path and crate the extern and entry file in the path*/
void createExternEntryFiles(char *path);
