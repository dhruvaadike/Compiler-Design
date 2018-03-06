%{ 
    #include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    int yylex(void);
    extern FILE *yyin;
    extern int yylineno;
    #include "abstracttree.h"
    #include "abstracttree.c"
	#include "codegen.c" 
    struct Tnode *root;
%} 

%union{
    int ival;
    struct Tnode * nptr;
    char c;
};
 
%token ID NUM ASGN DELIM READ WRITE IF THEN ENDIF ELSE WHILE DO ENDWHILE PLUS MUL GT LT EQ NL
%type <nptr> ID
%type <nptr> NUM
%type <nptr> READ
%type <nptr> WRITE
%type <nptr> IF
%type <nptr> THEN
%type <nptr> ENDIF
%type <nptr> ELSE
%type <nptr> WHILE
%type <nptr> DO
%type <nptr> ENDWHILE
%type <nptr> PLUS
%type <nptr> MUL
%type <nptr> GT
%type <nptr> LT
%type <nptr> EQ
%type <nptr> NL
%type <nptr> slist
%type <nptr> stmt
%type <nptr> expr
%left PLUS 
%left MUL
%nonassoc GT LT EQ

%%

start : slist NL    {root = $1;printf("Evaluating the tree\n");generate_code($1);exit(1);}
    ;

slist : slist stmt  {$$ = TreeCreate(TYPE_VOID,NODETYPE_NONE,0,NULL,NULL,$1,$2,NULL);}
    | stmt          {$$ = $1;}
    ;

stmt  : ID ASGN expr DELIM              {$$ = TreeCreate(TYPE_VOID,NODETYPE_ASGN,0,NULL,NULL,$1,$3,NULL);}
    | READ '(' ID ')' DELIM             {$$ = TreeCreate(TYPE_VOID,NODETYPE_READ,0,NULL,NULL,$3,NULL,NULL);}
    | WRITE '(' expr ')' DELIM          {printf("write");$$ = TreeCreate(TYPE_VOID,NODETYPE_WRITE,0,NULL,NULL,$3,NULL,NULL);}
    | IF '(' expr ')' THEN slist ENDIF DELIM    {$$ = TreeCreate(TYPE_VOID,NODETYPE_IF,0,NULL,NULL,$3,$6,NULL);}
	| IF '(' expr ')' THEN slist ELSE slist ENDIF DELIM    {$$ = TreeCreate(TYPE_VOID,NODETYPE_IF,0,NULL,NULL,$3,$6,$8);}
    | WHILE '(' expr ')' DO slist ENDWHILE DELIM    {$$ = TreeCreate(TYPE_VOID,NODETYPE_WHILE,0,NULL,NULL,$3,$6,NULL);}
    ;

expr  : expr PLUS expr  {$$ = TreeCreate(TYPE_INT,NODETYPE_PLUS,0,NULL,NULL,$1,$3,NULL);}
    | expr MUL expr {$$ = TreeCreate(TYPE_INT,NODETYPE_MUL,0,NULL,NULL,$1,$3,NULL);}
    | '(' expr ')'  {$$ = $2;}
    |  expr GT expr   {$$ = TreeCreate(TYPE_BOOLEAN,NODETYPE_GT,0,NULL,NULL,$1,$3,NULL);}
    |  expr LT expr  {$$ = TreeCreate(TYPE_BOOLEAN,NODETYPE_LT,0,NULL,NULL,$1,$3,NULL);}
    |  expr EQ expr   {$$ = TreeCreate(TYPE_BOOLEAN,NODETYPE_EQ,0,NULL,NULL,$1,$3,NULL);}
    | NUM   {$$ = $1;}
    | ID    {$$ = $1;}
    ;


%%
yyerror(char const *s) 
{ 
    printf("yyerror - line %d : character %c %s\n",yylineno,yychar,s); 
} 
int main(int argc,char* argv[]) 
{ 
    if(argc>1)
    {
        FILE *fp = fopen(argv[1],"r");
        if(fp)
            yyin = fp;
    }    
    yyparse(); 
    return 1; 
} 

