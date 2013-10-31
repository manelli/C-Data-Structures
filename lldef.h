struct LINKTYPE
{
	struct LINKTYPE *next;
	struct LINKTYPE *previous;
	char *item;
};

struct LINKLIST
{
	struct LINKTYPE *head;
	struct LINKTYPE *tail;
	struct LINKTYPE *clp;

	int listlength;
	int itemlength;

	int (*match)(); /*pointer to function returning int*/
};

void		llsetMatch(int *numatch);
int		llcheck(char *lookfor);
void		llsetlist(struct LINKLIST *new_list);
void		llsetsize(int size);
void		llinit(char *newitem);
void		llhead(void);
void		lltail(void);
int		llnext(void);
int		llprevious(void);
void		llretrieve(char *newitem);
void		lladd(char *newitem);
void		lladdhead(char *newitem);
void		lldelete(void);
int		ll_length(void);
