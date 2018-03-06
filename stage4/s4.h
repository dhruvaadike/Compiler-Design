struct Tnode{
	int TYPE;	/* INT or BOOL or VOID(for statements)*/
	int NODETYPE;	/*must point to the type expression tree for user defined types */
	char *NAME;
	int VALUE;
	struct Tnode *ptr1, *ptr2, *ptr3;
	//strcut Gsymbol *Gentry;
	//struct Lsymbol *Lentry;
};

int *var[26];

#define TYPE_INT 1
#define TYPE_BOOL 2
#define TYPE_VOID 3
#define NODETYPE_PLUS 4
#define NODETYPE_MUL 5
#define NODETYPE_LT 6
#define NODETYPE_GT 7
#define NODETYPE_EQ 8
#define NODETYPE_LEAF 9 //here for number
#define NODETYPE_ID 10
#define NODETYPE_ASGN 11
#define NODETYPE_READ 12
#define NODETYPE_WRITE 13
#define NODETYPE_WHILE 14
#define NODETYPE_IF 15
#define NODETYPE_STMT 16
#define NODETYPE_SLIST 17
#define RTRUE 18
#define RFALSE 19

struct Tnode* makeNode(int type,int nodetype,char* name, int value, struct Tnode *ptr1,struct Tnode *ptr2,struct Tnode *ptr3);
int eval(struct Tnode *n);

