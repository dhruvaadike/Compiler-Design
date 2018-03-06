%{ 
	#include <stdio.h> 
	#include <stdlib.h>
	#include <string.h>
	int yylex(void);
	extern FILE *yyin;
	#include "s4.h"
	#include "s4.c"
	
	struct Tnode *temp;
%} 

%union{
	int ival;
	struct Tnode* nptr;
	char c;
};

%token ID NUM ASGN DELIM READ WRITE IF THEN ENDIF ELSE WHILE DO ENDWHILE PLUS MUL GT LT EQ NL
%nonassoc GT LT EQ
%left PLUS 
%left MUL


%type <nptr> slist 
%type <nptr> expr 
%type <nptr> stmt 
%type <nptr> NUM
%type <nptr> ID


%%

start : slist NL				     { printf("Evaluation ");eval($1);exit(0);}
	;

slist : slist stmt				     { $$ = makeNode(TYPE_VOID,NODETYPE_SLIST,NULL,0,$1,$2,NULL); }
	| stmt					     { $$ = $1; }
	;

stmt  : ID ASGN expr DELIM			     { $$ = makeNode(TYPE_VOID,NODETYPE_ASGN,NULL,0,$1,$3,NULL);
						     }
	| READ '(' ID ')' DELIM			     { 
  						       $$ = makeNode(TYPE_VOID,NODETYPE_READ,NULL,0,$3,NULL,NULL); 
						     } 
	| WRITE '(' expr ')' DELIM		     { $$ = makeNode(TYPE_VOID,NODETYPE_WRITE,NULL,0,$3,NULL,NULL);}
	| IF '(' expr ')' THEN slist ENDIF DELIM     { $$ = makeNode(TYPE_VOID,NODETYPE_IF,NULL,0,$3,$6,NULL);}
	| WHILE '(' expr ')' DO slist ENDWHILE DELIM { $$ = makeNode(TYPE_VOID,NODETYPE_WHILE,NULL,0,$3,$6,NULL); }
	;

expr  : expr PLUS expr		{ $$ = makeNode(TYPE_INT,NODETYPE_PLUS,NULL,0,$1,$3,NULL); }
	| expr MUL expr		{ $$ = makeNode(TYPE_INT,NODETYPE_MUL,NULL,0,$1,$3,NULL); }
	| '(' expr ')'		{ $$ = $2; }
	| expr GT expr	 	{ $$ = makeNode(TYPE_BOOL,NODETYPE_GT,NULL,0,$1,$3,NULL); }
	| expr LT expr		{ $$ = makeNode(TYPE_BOOL,NODETYPE_LT,NULL,0,$1,$3,NULL); }
	| expr EQ expr	  	{ $$ = makeNode(TYPE_BOOL,NODETYPE_EQ,NULL,0,$1,$3,NULL); }
	| NUM			{ $$ = $1; }
	| ID			{ $$ = $1;}
	;


%%

int yyerror() 
{ 
	printf("Error"); 
return 0;
} 

int main() 
{ 
	
	yyparse(); 
	return 1; 
} 

