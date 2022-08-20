#include <string.h>
#include <stdlib.h>
#include "MacroTable.h"


struct macroList
{
	char macroName[MAX_LINE_CHARS];
	char macroData[MAX_LINES_PER_MACRO];
	struct macroList *next;
};
struct macroList *head,*last;

void addMacro(char *name, char *data)
{ 
	struct macroList *newnode;
	newnode=(struct macroList *)malloc(sizeof(struct macroList));
	strcpy(newnode->macroName,name);
	strcpy(newnode->macroData,data);
	newnode->next=NULL;
	if(head==NULL)
	{ 
		head=newnode;
		last=newnode;
	}

	else
	{  
		newnode->next=head;
		head=newnode;
	}
}

const char * getMacroDataByName(char *name)
{

	struct macroList *ptr;
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
		if(strcmp(ptr->macroName,name)==0)
			return ptr->macroData;
	return NOT_A_MACRO;
}

void clearMacroList()
{
	free(head);
	head=(struct macroList *)malloc(sizeof(struct macroList));
	head=NULL;
	last=head;
}
