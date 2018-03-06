%{ 
	#include <stdio.h> 
	#include "y.tab.h"
	#include <stdlib.h>
	struct Node* mkOperatorNode(char c,struct Node *l,struct Node *r);
	struct Node* mkLeafNode(int n);
	int evaluate(struct Node *t);
	struct Node *temp;
	int number;
%} 

%% 

[a-z]  		{yylval.nptr = mkOperatorNode(yytext[0],NULL,NULL); return ID;}
[0-9]+ 		{number = atoi(yytext);yylval.nptr = mkLeafNode(number);return NUM;}
[=+*-/]		{yylval.nptr = mkOperatorNode(yytext[0],NULL,NULL); return *yytext;}
[();] 	{return *yytext;}
[\n]		{return NL;}
read		{yylval.nptr = mkOperatorNode('R',NULL,NULL);return READ;}
write		{yylval.nptr = mkOperatorNode('W',NULL,NULL);return WRITE;}	
[ \t]		;

%% 
int yywrap()
{
	return 1;
}

