%{ 
    #include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "abstracttree.h"
    //extern int yylval;
    int number;
%} 


digit    [0-9]
letter     [a-z]
whitespaces [ \t]
NL     [\n]
plus    [+]
mul    [*]
asgn     [=]
gt    [>]
lt     [<]

     
%%

{letter}    {yylval.nptr = TreeCreate(TYPE_VOID,NODETYPE_ID,0,yytext,NULL,NULL,NULL,NULL);return ID;}
{digit}+    {number=atoi(yytext);yylval.nptr = TreeCreate(TYPE_INT,NODETYPE_LEAF,number,NULL,NULL,NULL,NULL,NULL);return NUM;}
[;]        	{return DELIM;}
"=" 		{return ASGN;}
"read"      {return READ;}
"write"     {return WRITE;}
"if"        {return IF;}
"then"      {return THEN;}
"else"      {return ELSE;}
"endif"     {return ENDIF;}
"while"     {return WHILE;}
"do"        {return DO;}
"endwhile"  {return ENDWHILE;}
{plus}      {return PLUS;}
{mul}       {return MUL;}
{gt}        {return GT;}
{lt}        {return LT;}
"=="	   {return EQ;}
{NL}        {return NL;}
{whitespaces} ;
[()]        {return *yytext;}
.        	{printf("INVALID CHARACTER");exit(0);}

%%

int yywrap(){
    return 1;
}

