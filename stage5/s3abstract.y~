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

%token NUM READ WRITE ID NL ASGN PLUS MUL DELIM ENDOFFILE
%type <nptr> Slist Stmt expr NUM ASGN PLUS MUL
%type <nptr> READ WRITE ID
%left PLUS
%left MUL

%%

start : Slist ENDOFFILE 		{
									root = $1;
									printf("Evaluating the tree\n");
									//Evaluate($1);
									generate_code($1);									
									exit(0);
								}
	;

Slist : Slist Stmt		{$$ = TreeCreate(TYPE_VOID,NODETYPE_NONE,0,NULL,NULL,$1,$2,NULL);}
	| Stmt				{$$ = $1;}
	;	

Stmt  : ID ASGN expr DELIM  			{
											$$ = TreeCreate(TYPE_VOID,NODETYPE_ASGN,0,NULL,NULL,$1,$3,NULL);
										}
	| READ '(' ID ')' DELIM         	{	
											$$ = TreeCreate(TYPE_VOID,NODETYPE_READ,0,NULL,NULL,$3,NULL,NULL);
										}
	| WRITE '(' expr ')' DELIM     		{
											$$ = TreeCreate(TYPE_VOID,NODETYPE_WRITE,0,NULL,NULL,$3,NULL,NULL);
										}
	;

expr  : expr PLUS expr  	{$$ = TreeCreate(TYPE_INT,NODETYPE_PLUS,0,NULL,NULL,$1,$3,NULL);}
	| expr MUL expr 		{$$ = TreeCreate(TYPE_INT,NODETYPE_MUL,0,NULL,NULL,$1,$3,NULL);}
	| '(' expr ')'  		{$$ = $2;}
	| NUM           		{$$ = $1;}
	| ID            		{$$=$1;}
	;

%%

yyerror(char const *s)
{
	printf("yyerror - line %d : character %d %s",yylineno,yychar,s);
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
//	int i; 
	//for(i=0;i<26;i++)
		//free(value[i]);
	return 1;
}
