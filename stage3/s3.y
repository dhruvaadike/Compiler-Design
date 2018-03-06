%{ 
	#include <stdio.h> 
	#include <stdlib.h>
	int yylex(void);
	extern FILE *yyin;
	#include "s3.h"
	
%}

%union{
	int integer;
	char character;
	struct Node *nptr;
}

%token NUM READ WRITE ID NL '=' '+' '-' '*' '/'
%type <nptr> Slist Stmt expr NUM '=' '+' '*' '/' '-'
%type <nptr> READ WRITE ID
%left '+' '-'
%left '*' '/'

%%

start : Slist NL 		{printf("Evaluating\n");evaluate($1);printf("successful\n");exit(0);}
	;

Slist : Slist Stmt		{$$ = mkOperatorNode('S',NULL,NULL);$$->left = $1; $$->right = $2;}
	| Stmt				{$$ = $1;}
	;	


Stmt :  ID '=' expr ';' 	 {$2->left = $1; $2->right = $3; $$ = $2;}
	| READ '(' ID ')' ';'	 {$1->left = $3; $$ = $1;}
	| WRITE '(' expr ')' ';' {$1->left = $3; $$ = $1;}
	;

expr : expr '+' expr      {$2->left = $1; $2->right = $3; $$ = $2;}
	| expr '*' expr   {$2->left = $1; $2->right = $3; $$ = $2;}
	| expr '-' expr   {$2->left = $1; $2->right = $3; $$ = $2;}
	| expr '/' expr   {$2->left = $1; $2->right = $3; $$ = $2;}
	| '(' expr ')'	  {$$ = $2;}
	| NUM		  {$$ = $1;}
	| ID		  {$$ = $1;}
	;  

%%
yyerror() 
{ 
	printf("yyError"); 
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
	int i; 
	for(i=0;i<26;i++)
		free(value[i]);
	return 1; 
} 
