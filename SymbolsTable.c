#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SymbolsTable.h"

struct symbolList
{
	char symbolName[MAX_LABEL_CHARS];
	char symbolType; /*'i for instruction, 'd' for data*/
	char areType; /*'r' for relocatable, 'e' for external*/
	int index;
	struct symbolList *next;
};
struct symbolList *head,*last;

void addSymbol(char *name, char symbolType, char areType, int index)
{
	struct symbolList *newnode;
	newnode=(struct symbolList *)malloc(sizeof(struct symbolList));
	strcpy(newnode->symbolName,name);
	newnode->symbolType=symbolType;
	newnode->areType=areType;
	newnode->index=index;
	newnode->next=NULL;
	if(last==NULL)
		last=newnode;
	else
		newnode->next=head;
	head=newnode;
}


void resetSymbolsTable()
{
	free(head);
	head=(struct symbolList *)malloc(sizeof(struct symbolList));
	head=NULL;
	last=head;
}

int checkIfRelocatable(char *name)
{
	struct symbolList *tmp;
	tmp=head;
	while(tmp!=NULL && strcmp(tmp->symbolName,name)!=0)
		tmp=tmp->next;
	if(tmp!=NULL && tmp->areType==RELOCATABLE_CHAR)
		return 1;
	return 0;
}

int checkIfExternal(char *name)
{
	struct symbolList *tmp;
	tmp=head;
	while(tmp!=NULL && strcmp(tmp->symbolName,name)!=0)
	{
		tmp=tmp->next;
	}
	if(tmp!=NULL && tmp->areType==EXTERNAL_CHAR)
		return 1;
	return 0;
}

int getIndexBySymbolName(char *name)
{
	struct symbolList *tmp;
	tmp=head;
	while(tmp!=NULL && strcmp(tmp->symbolName,name)!=0)
		tmp=tmp->next;
	if(tmp==NULL)
		return 0;
	return tmp->index;
}

int isSymbolDeclared(char *name)
{
	struct symbolList *tmp;
	tmp=head;
	while(tmp!=NULL && strcmp(tmp->symbolName,name)!=0)
		tmp=tmp->next;
	if(tmp==NULL)
		return 0;
	return 1;
}

char getAreTypeBySymbolName(char *name)
{
	struct symbolList *tmp;
	tmp=head;
	while(tmp!=NULL && strcmp(tmp->symbolName,name)!=0)
		tmp=tmp->next;
	if(tmp==NULL)
		return 0;
	return tmp->areType;
}

validation_code checkSymbolName(char *name)
{
	int i;
	if(!isalpha(name[0])) /*first charachter must be a letter*/
		return INVALID_SYMBOL_NAME;
	for(i=1;i<strlen(name);i++)
		if(!isalnum(name[i]))
			return INVALID_SYMBOL_NAME;
	return VALID;
}

void updateSymbolsWithInstructionCounter(int counter)
{
	struct symbolList *tmp;
	for(tmp=head; tmp!=NULL; tmp = tmp -> next)
		if((tmp -> symbolType)==DATA_TYPE)
			(tmp -> index) += counter;
	return;
}
