%{ 
#include <stdio.h> 
#include <stdlib.h>
//#include "lex.yy.c"
int yylex();
extern FILE *yyin;
%} 

%token NUM
%left '+'
%left '*'

%% 
start : expr '\n'		{printf("\nComplete , ans is %d\n",$$);exit(1);} 
	; 

expr:  expr '+' expr		{$$ = $1 + $3;printf("+ ");} 
	| expr '*' expr		{$$ = $1 * $3;printf("* ");} 
	| '(' expr ')'	 	{$$ = $2; }
	| NUM		 	{printf("%d  ",$1);}
	; 


%% 

yyerror() 
{ 
	printf("Error"); 
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
