#define TYPE_INT 1
#define TYPE_BOOLEAN 2
#define TYPE_VOID 3
#define NODETYPE_LEAF 0
#define NODETYPE_ID 1
#define NODETYPE_PLUS 2
#define NODETYPE_MUL 3
#define NODETYPE_GT 4
#define NODETYPE_LT 5
#define NODETYPE_EQ 6
#define NODETYPE_ASGN 7
#define NODETYPE_READ 8
#define NODETYPE_WRITE 9
#define NODETYPE_IF 10
#define NODETYPE_THEN 11
#define NODETYPE_ELSE 12
#define NODETYPE_ENDIF 13
#define NODETYPE_WHILE 14
#define NODETYPE_DO 15
#define NODETYPE_ENDWHILE 16
#define NODETYPE_NONE 17
#define NODETYPE_GE 21
#define NODETYPE_LE 22
#define NODETYPE_NE 23

int* value[26];

struct Tnode {

int TYPE; // Integer, Boolean or Void (for statements)
/* Must point to the type expression tree for user defined types */
int NODETYPE;
/* this field should carry following information:
* a) operator : (+,*,/ etc.) for expressions
* b) statement Type : (WHILE, READ etc.) for statements */
char* NAME; // For Identifiers/Functions
int VALUE; // for constants
struct Tnode *ArgList; // List of arguments for functions
struct Tnode *Ptr1, *Ptr2, *Ptr3;	/* Maximum of three subtrees (3 required for IF THEN ELSE */
struct Gsymbol *Gentry; // For global identifiers/functions
struct Lsymbol *Lentry; // For Local variables
};	

struct Tnode *TreeCreate(int TYPE,int NODETYPE,int VALUE,char* NAME,struct Tnode *ArgList,struct Tnode *Ptr1,struct Tnode *Ptr2,struct Tnode *Ptr3);

int Evaluate(struct Tnode *root);

