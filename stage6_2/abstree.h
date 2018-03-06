#define TYPE_INT 	1
#define TYPE_BOOL 	2
#define TYPE_VOID 	3
#define NODE_ASGN	4
#define NODE_READ 	5
#define NODE_WRITE	6
#define NODE_IF 	7 
#define NODE_IF_ELSE 8 
#define NODE_ID  	9 
#define NODE_PLUS 	10 
#define NODE_MINUS 	11
#define NODE_MUL 	12
#define NODE_LT  	13
#define NODE_GT  	14
#define NODE_DEQ 	15
#define NODE_LEAF 	16
#define TRUE 		17
#define FALSE 		18
#define IS_TOP		19
#define NODE_WHILE 20
#define NODE_ARR_ASGN	21
#define NODE_ARR_READ 	22
#define NODE_ARR_ID  	23



struct Tnode {

int TYPE; 		
int NODE;
char* NAME; 	
int VALUE; 		
struct Tnode *ArgList; 
struct Tnode *Ptr1, *Ptr2, *Ptr3;	
struct Gsymbol *Gentry; 

};	


struct Tnode *TreeCreate(int TYPE,int NODE,char* NAME,int VALUE,struct Tnode *ArgList,
										struct Tnode *Ptr1,struct Tnode *Ptr2,struct Tnode *Ptr3);

int Evaluate(struct Tnode *root);
