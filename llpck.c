#include "lldef.h"
#include <stdio.h>

static struct LINKLIST *list;

#define moveitem(A,B)	movmem(A,B,list->itemlength)
/* Use this macro as moveitem(from, to) */

void llsetmatch(int* numatch)
{
	list->match = numatch;
}

/* Set clp to desired link, return True if found, False otherwise */
int llcheck(char* lookfor)
{
	if(!ll_length())
		return 0;
	for(;;)
	{
		if((*list->match)(list->clp->item, lookfor))
			return 1;
		else
		{
			if(!llnext())
				return 0;
		}
	}
}

void llsetlist(struct LINKLIST *new_list) /* Set this module to work with a new list */
{
	list = new_list;
}


void llsetsize(int size) /* Set the storage requirements for the list */
{
	list->itemlength = size;
}

static struct LINKTYPE *llcrlink() /* Allocate storage for a link */
{
	char *malloc();
	struct LINKTYPE *link;

	link = (struct LINKTYPE *)malloc(sizeof(struct LINKTYPE));
	link->item = malloc(list->itemlength);
	return(link);
}

void llinit(char *newitem) /* Initialize the structure. */
{
	list->head = list->tail = list->clp = llcrlink();
	list->clp->next = list->clp->previous = NULL;
	moveitem(newitem, list->clp->item);
	list->listlength = 1;
}

void llhead(void) /* Set the CLP to the head of the list */
{
	list->clp = list->head;
}

void lltail(void) /* Set the CLP to the head of the list */
{
	list->clp = list->tail;
}

/* Set the CLP to the next link, return FALSE if at end of list, 
	TRUE otherwise. */
int llnext(void)
{
	if (list->clp->next == NULL)
		return 0;
	else {
		list->clp = list->clp->next;
		return 1;
	}
}

/*
Set the CLP to the previous link, return FALSE if at head of list, 
TRUE otherwise. */
int llprevious(void)
{
	if (list->clp->previous == NULL)
		return 0;
	else {
		list->clp = list->clp->previous;
		return 1;
	}
}

void llretrieve(char *newitem) /* Retrieve the item from the CLP link. */
{
	moveitem(list->clp->item, newitem);
}

/*
Add a new link containing this item to the link following the CLP, 
and reset CLP to new link. */
void lladd(char *newitem)
{
	struct LINKTYPE *newlink;
	struct LINKTYPE *llcrlink();

	/* Create new link */
	newlink = llcrlink();
	moveitem(newitem, newlink->item);
	list->listlength++;

	/*Reset pointers */
	newlink->next = list->clp->next;
	newlink->previous = list->clp;
	if (list->tail == list->clp)
		list->tail = newlink;
	else
		list->clp->next->previous = newlink;
	list->clp->next = newlink;
	list->clp = newlink;
}

void lladdhead(char *newitem) /* Add a new head, reset CLP. */
{
	struct LINKTYPE *newlink;
	struct LINKTYPE *llcrlink();

	/* If empty, initialize list */
	if(!ll_length())
	{
		llinit(newitem);
		return;
	}

	/* Create new link */
	newlink = llcrlink();
	moveitem(newitem, newlink->item);
	list->listlength++;
	
	/* Reset pointers */
	newlink->previous = NULL;
	newlink->next = list->head;
	list->head->previous = newlink;
	list->clp = list->head = newlink;
}

void lldelete(void) /* Delete and free the CLP, reset CLP to head. */
{
	struct LINKTYPE *before, *after;

	/* Is this the only link? */
	if(list->head == list->clp && list->tail == list->clp)
		list->head = list->tail = NULL;
	
	/* Is this the head */
	else if(list->head == list->clp)
	{
		list->head = list->head->next;
		list->head->previous = NULL;
	}

	/* Is this the tail? */
	else if(list->tail == list->clp)
	{
		list->tail = list->tail->previous;
		list->tail->next = NULL;
	}

	/* Otherwise, it must be inside the list */
	else
	{
		before = list->clp->previous;
		after = list->clp->next;
		before->next = after;
		after->previous = before;
	}

	/* Delete CLP */
	free(list->clp)
	list->clp = list->head;
	list->listlength--;
}

int ll_length(void) /* Return the length of the list */
{
	return(list->listlength);
}
