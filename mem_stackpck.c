#include "stackdef.h"

static struct STACK memstk;	/* Stack of memory pointers */

struct pnt_type
{
	int type;	/* Either IS_MARK or IS_PNT */
	char *pnt;	/* Address of allocated memory */
};

#define IS_MARK 0	/* Stack marker */
#define IS_PNT 1	/* Pointer */

static struct pnt_type pointer;

void mark_stack(void)
{
	static int first = 1;

	/* Initialize stack if first time through */
	stset(&memstk);
	if(first)
	{
		stitemsize(sizeof(struct pnt_type));
		first = 0;
	}
	
	/* Mark the stack */
	pointer.type = IS_MARK;
	st_push(&pointer);
}

char *get_mem(int nbytes)	/* Number of bytes requested */
{
	char *malloc();

	stset(&memstk);
	pointer.type = IS_PNT;
	pointer.pnt = malloc(nbytes);
	st_push(&pointer);
	return pointer.pnt;
}

void rel_mem(void)
{
	stset(&memstk);
	st_pop(&pointer);
	while(pointer.type == IS_PNT)
	{
		free(pointer.pnt);
		st_pop(&pointer);
	}
}

