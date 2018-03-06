%{ 
	#include <stdio.h> 
	#include "y.tab.h"
	extern YYSTYPE yylval;
	#include "s4.h"
%} 


digit	[0-9]
letter 	[a-z]
whitespaces [ \t]
NL 	[\n]
plus	[+]
mul	[*]
asgn 	[=]
gt	[>]
lt 	[<]

	 
%%

{letter}	{yylval.nptr = makeNode(TYPE_VOID,NODETYPE_ID,yytext,0,NULL,NULL,NULL);return ID;}
{digit}+	{yylval.nptr = makeNode(TYPE_INT,NODETYPE_LEAF,NULL,atoi(yytext),NULL,NULL,NULL); return NUM;}
{asgn}		{return ASGN;}
[;]		{return DELIM;}
"read"		{return READ;}
[()]		{return *yytext;}
"write"		{return WRITE;}
"if"		{return IF;}
"then"		{return THEN;}
"endif"		{return ENDIF;}
"else"		{return ELSE;}
"while"		{return WHILE;}
"do"		{return DO;}
"endwhile"	{return ENDWHILE;}
{plus}		{return PLUS;}
{mul}		{return MUL;}
{gt}		{return GT;}
{lt}		{return LT;}
==		{return EQ;}
{NL}		{return NL;}
{whitespaces}	;
.		{printf("INVALID CHARACTER");exit(0);}

%%

int yywrap(){
	return 1;
}
