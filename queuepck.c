#include <stdio.h>
#include "queuedef.h"

static struct QUEUE *q; /* Pointer to currently active queue */

void q_push(char *newitem)
{
	if(!ll_length())
		llinit(newitem);
	else
		lladhead(newitem);
}

void q_pop(char *olditem)
{
	lltail();
	llretrieve(olditem);
	lldelete();
}
