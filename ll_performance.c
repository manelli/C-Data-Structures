#include <stdio.h>
#include "lldef.h"

int main(void)
{
	int m1, m2, m3, valu;
	struct LINKLIST l1;
	
	/* How many Iterations? */
	printf("m3: ");
	scanf("%d", &m3);
	printf("m3: %d\n",m3);

	/* Initialize list */
	llsetlist(&l1);
	llsetsize(sizeof(int));
	/* ¿? */llzero();
	valu = 0;

	/* Create list with 100 elements */
	for(m1 = 0; m1 < 100; m1++)
	{
		lladd(&valu);
		++valu;
	}

	/* Read through list once for each iteration */
	printf("start\n");
	for(m2=0; m2<m3; m2++)
	{
		llhead();
		for(m1=1; m1<100; m1++)
			llnext();
	}
	printf("stop\n");

	return 0;
}
