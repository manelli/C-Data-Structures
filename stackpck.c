#include <stdio.h>
#include "stackdef.h"

static struct STACK *st;	/* Pointer to currently active stack */

void st_push(char *newitem)
{
	if(!ll_length())
		llinit(newitem);
	else
		lladhead(newitem);
}

void st_pop(char *olditem)
{
	llretrieve(olditem);
	lldelete();
}
