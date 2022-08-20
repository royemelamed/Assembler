#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "externEntryTables.h"
#include "base32.h"
#define MAX_LINE_CHARS 80
#define EXT_FILE_POSTFIX ".ext"
#define DOT_EXT_POSTFIX_LEN 4
#define ENT_FILE_POSTFIX ".ent"
#define DOT_ENT_POSTFIX_LEN 4

/*-------------------------------internal methods decleration-------------------------------*/
void createExternFile(char *path);
void createEntryFile(char *path);
void createDotExtPath (char *path);
void createDotEntPath (char *path);
/*------------------------------------------------------------------------------------------*/


struct externTable
{
	char symbolName[MAX_LINE_CHARS];
	int decimalAdress;
	struct externTable *next;
};

struct externTable *extHead,*extLast;

struct entryTable
{
	char symbolName[MAX_LINE_CHARS];
	struct entryTable *next;
};

struct entryTable *entHead,*entLast;


void addExternSymbol(char *name, int decimalAdress)
{
	struct externTable *newnode;
	newnode=(struct externTable *)malloc(sizeof(struct externTable));
	strcpy(newnode->symbolName,name);
	newnode->decimalAdress=decimalAdress;
	newnode->next=NULL;
	if(extLast==NULL)
		extLast=newnode;
	else 
		newnode->next=extHead;
	extHead=newnode;
}

const int getExternAdressByName(char *name)
{
	struct externTable *ptr;
	for(ptr=extHead;ptr!=NULL;ptr=ptr->next)
		if(strcmp(ptr->symbolName,name)==0)
			return ptr->decimalAdress;
	return 0;
}

const validation_code getExternNameByAdress(int adress, char **symbolName)
{
	struct externTable *ptr;
	for(ptr=extHead;ptr!=NULL;ptr=ptr->next)
		if(ptr->decimalAdress==adress)
		{
			strcpy((*symbolName),ptr->symbolName);
			return VALID;
		}
	return UNKNOWN_ERROR;
}

void clearExternTable()
{
	free(extHead);
	extHead=(struct externTable *)malloc(sizeof(struct externTable));
	extHead=NULL;
	extLast=extHead;
}

void addEntrySymbol(char *name)
{
	struct entryTable *newnode;
	newnode=(struct entryTable *)malloc(sizeof(struct entryTable));
	strcpy(newnode->symbolName,name);
	newnode->next=NULL;
	if(entLast==NULL)
		entLast=newnode;
	else  
		newnode->next=entHead;
	entHead=newnode;
}

const int getEntryAdressByName(char *name)
{
	struct entryTable *ptr;
	for(ptr=entHead;ptr!=NULL;ptr=ptr->next)
		if(strcmp(ptr->symbolName,name)==0)
			return getIndexBySymbolName(ptr -> symbolName);
	return UNKNOWN_ERROR; /*macro name isn't exist. NOTE: change npt a macro*/
}

const validation_code getEntryNameByAdress(int adress, char **symbolName)
{
	struct entryTable *ptr;
	for(ptr=entHead;ptr!=NULL;ptr=ptr->next)
		if(getIndexBySymbolName(ptr -> symbolName)==adress)
		{
			strcpy((*symbolName),ptr->symbolName);
			return VALID;
		}
	return UNKNOWN_ERROR;
}


void clearEntryTable()
{
	free(entHead);
	entHead=(struct entryTable *)malloc(sizeof(struct entryTable));
	entHead=NULL;
	entLast=entHead;
}

void createExternEntryFiles(char *path)
{
	createExternFile(path);
	createEntryFile(path);
}



void createExternFile(char *path)
/*Create the extern file in the path*/
{
	char *extPath, baseChars[MAX_32_NUMBER_LEN];
	FILE *fptr;
	struct externTable *ptr;
	if(extHead!=NULL)
	{
		extPath=(char *)malloc(strlen(path)+DOT_EXT_POSTFIX_LEN*sizeof(char));
		strcpy(extPath,path); 
		createDotExtPath(extPath);
		fptr=fopen(extPath,"w");
		if (extPath == NULL) /* Unable to open file hence exit */
		{
			print_code(UNKNOWN_ERROR);
			exit(EXIT_SUCCESS);
		}

		for(ptr=extHead;ptr!=NULL;ptr=ptr->next)
		{
			getBaseCharsByDecimal(FIRST_INDEX+ptr->decimalAdress,baseChars);
			fputs(ptr->symbolName,fptr);
			fputc('\t',fptr);
			fputs(baseChars,fptr);
			fputc('\n',fptr);
		}
		free(extPath);
		fclose(fptr);
	}
}

void createEntryFile(char *path)
/*Create the entry file in the path*/
{
	char *entPath, baseChars[MAX_32_NUMBER_LEN];
	FILE *fptr;
	struct entryTable *ptr;
	if(entHead!=NULL)
	{
		entPath=(char *)malloc(strlen(path)+DOT_ENT_POSTFIX_LEN*sizeof(char));
		strcpy(entPath,path); 
		createDotEntPath(entPath);
		fptr=fopen(entPath,"w");
		if (entPath == NULL) /* Unable to open file hence exit */
		{
			print_code(UNKNOWN_ERROR);
			exit(EXIT_SUCCESS);
		}
		for(ptr=entHead;ptr!=NULL;ptr=ptr->next)
		{
			getBaseCharsByDecimal(getIndexBySymbolName(ptr -> symbolName),baseChars);
			fputs(ptr->symbolName,fptr);
			fputc('\t',fptr);
			fputs(baseChars,fptr);
			fputc('\n',fptr);
		}
		free(entPath);
		fclose(fptr);
	}
}

void createDotExtPath (char *path)
/*Create the format of the extern file*/
{
	char *pDot=strchr(path,'.');
	if(pDot==NULL) /*meaning that there isn't format for the file*/
		strcat(path,EXT_FILE_POSTFIX);
	else
	{
		*(pDot+1)='e';
		*(pDot+2)='x';
		*(pDot+3)='t';
		*(pDot+4)='\0';
	}
}

void createDotEntPath (char *path)
/*Create the format of the entry file*/
{
	char *pDot=strchr(path,'.');
	if(pDot==NULL) /*meaning that there isn't format for the file*/
		strcat(path,ENT_FILE_POSTFIX);
	else
	{
		*(pDot+1)='e';
		*(pDot+2)='n';
		*(pDot+3)='t';
		*(pDot+4)='\0';
	}
}
