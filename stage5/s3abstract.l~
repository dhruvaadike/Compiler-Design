%{ 
	#include <stdio.h> 
	#include "y.tab.h"
	#include <stdlib.h>
	#include <string.h>
	#include "abstracttree.h"
	int number;
%} 

digit		[0-9]
letter 		[a-z]
whitespaces [ \t]
NL 			[\n]
plus		[+]
mul			[*]
asgn 		[=]

%% 

<<EOF>>    	{return ENDOFFILE;} //returns end of file
{digit}+	{number=atoi(yytext);yylval.nptr = TreeCreate(TYPE_INT,NODETYPE_LEAF,number,NULL,NULL,NULL,NULL,NULL);return NUM;}
[;]   		{return DELIM;}
"="    	 	{return ASGN;}
"read"  	{return READ;}
"write" 	{return WRITE;}
{plus}  	{return PLUS;}
{letter}	{yylval.nptr = TreeCreate(TYPE_VOID,NODETYPE_ID,0,yytext,NULL,NULL,NULL,NULL);return ID;}
{mul}   	{return MUL;}
{NL}    		;
{whitespaces} 	;
[()]    	{return *yytext;}
.   		{printf("INVALID CHARACTER");exit(0);}

%% 
int yywrap()
{
	return 1;
}
