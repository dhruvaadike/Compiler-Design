%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "abstree.h"
     #include "symboltable.h"
    #include "abstree.c"
   
    #include "symboltable.c"
    int yylex();
    void yyerror(char const *s);
    struct Tnode *root,*head,*troot,*thead;
    int result,tempp;
    FILE * fp;
    extern FILE *yyin;
%}

%union
{
    struct Tnode * nptr;
};

%token ENDPGM DECL ENDDECL T F INT BOOL NUM ID PLUS MUL ASGN READ WRITE MINUS NEWLINE LT GT DEQ ELSE IF THEN ENDIF WHILE DO EWHILE
%left PLUS MINUS
%left MUL
%right ASGN
%nonassoc LT GT DEQ
%type <nptr> NUM
%type <nptr> INT 
%type <nptr> program 
%type <nptr> ID
%type <nptr> expr
%type <nptr> slist
%type <nptr> stmt
%type <nptr> T
%type <nptr> F

%%

program : DECL dlist ENDDECL slist ENDPGM {
                             printf("Starting to Evaluate\n");
                            result = Evaluate($4);
                            printf("Evaluate\n");
                            exit(1);
                        }
        ;

dlist: dlist decl {}
    |  decl {}
    ;

decl : type idlist ';' {} 
    ;

type : INT   { tempp = STYPE_INT; }
    | BOOL   { tempp = STYPE_BOOLEAN; }    /*checkpoint*/
    ;

idlist : idlist ',' id {}
    |  id {}

id : ID  {Ginstall($1->NAME,tempp,1,NULL);/*printf("%s installed\n",$1->NAME ); */}
    | ID '[' NUM  ']' {
                        if (tempp==STYPE_INT) 
                        Ginstall($1->NAME,STYPE_ARR_INT,$3->VALUE,NULL);            
                        else
                       Ginstall($1->NAME,STYPE_ARR_BOOLEAN,$3->VALUE,NULL);
                    // printf("%s installed\n",$1->NAME );
                    }
    ;

slist : slist stmt  {$$ = TreeCreate(TYPE_VOID,IS_TOP,NULL,0,NULL,$1,$2,NULL);}
    | stmt          {$$ = $1; }
    ;

stmt : ID ASGN expr ';'          {
                                    Gtemp=Glookup($1->NAME);
                                    //printf("---------\n");
                                    if(Gtemp==NULL){
                                        yyerror("undefined variable ");/*printf("%s",$1->NAME);exit(0);*/}  
                                    else if(Gtemp->type == STYPE_ARR_INT || Gtemp->type == STYPE_ARR_BOOLEAN){
                                        yyerror("invalid reference to an array ");
                                        printf("%s",$1->NAME);
                                        exit(0);
                                    }
                                   else $1->Gentry=Gtemp;
                                    $$ = TreeCreate(TYPE_VOID, NODE_ASGN,NULL,0,NULL,$1,$3,NULL);

                                }
        | READ '(' ID ')' ';'    { 
                                    Gtemp=Glookup($3->NAME);
                                    if(Gtemp==NULL){
                                        yyerror("undefined variable ");printf("%s",$3->NAME);exit(0);}  
                                    else if(Gtemp->type == STYPE_ARR_INT || Gtemp->type == STYPE_ARR_BOOLEAN){
                                        yyerror("invalid reference to an array ");
                                        printf("%s",$3->NAME);
                                        exit(0);
                                    }
                                    else 
                                        $3->Gentry=Gtemp;
                                    $$ = TreeCreate(TYPE_VOID, NODE_READ,NULL,0,NULL,$3,NULL,NULL);
                                } 

        | ID '[' expr ']' ASGN expr ';'   {  // printf("ARR ASSGN\n");
                                            Gtemp=Glookup($1->NAME);
                                            if(Gtemp==NULL){
                                                yyerror("undefined variable ");printf("%s",$1->NAME);exit(0);}  
                                            else if(Gtemp->type == STYPE_INT || Gtemp->type == STYPE_BOOLEAN){
                                                yyerror("invalid reference to a variable ");
                                                printf("%s",$1->NAME);
                                                exit(0);        
                                            }
                                            else $1->Gentry=Gtemp;
                                            if($3->TYPE==TYPE_BOOL) {printf("index value is not integer\n");exit(1);}
                                            $$ = TreeCreate(TYPE_VOID,NODE_ARR_ASGN,NULL,0,NULL,$1,$3,$6);
                                        }
        | READ '(' ID '[' expr ']' ')' ';'    {  // printf("ARR READ\n");
                                                Gtemp=Glookup($3->NAME);
                                                if(Gtemp==NULL){
                                                    yyerror("undefined variable ");printf("%s",$3->NAME);exit(0);}  
                                                else if(Gtemp->type == STYPE_INT || Gtemp->type == STYPE_BOOLEAN){
                                                    yyerror("invalid reference to a variable ");
                                                    printf("%s",$3->NAME);
                                                    exit(0);        
                                                }
                                                else 
                                                    $3->Gentry=Gtemp;
                                                $$ = TreeCreate(TYPE_VOID,NODE_ARR_READ,NULL,0,NULL,$3,$5,NULL);
                                            }
        | WRITE '(' expr ')' ';'  { $$ = TreeCreate(TYPE_VOID, NODE_WRITE,NULL,0,NULL,$3,NULL,NULL); }
        |IF '(' expr ')' THEN slist ENDIF ';'            { $$ = TreeCreate(TYPE_VOID, NODE_IF,NULL,0,NULL,$3,$6,NULL); }
        |IF '(' expr ')' THEN slist ELSE slist ENDIF ';' { $$ = TreeCreate(TYPE_VOID, NODE_IF_ELSE,NULL,0,NULL,$3,$6,$8); }
        |WHILE '(' expr ')' DO slist EWHILE ';' {$$ = TreeCreate(TYPE_VOID, NODE_WHILE,NULL,0,NULL,$3,$6,NULL);}
        ;





expr : expr PLUS expr        {$$ = TreeCreate(TYPE_INT, NODE_PLUS , NULL,0, NULL, $1, $3, NULL);}
		|expr MINUS expr  	 {$$ = TreeCreate(TYPE_INT, NODE_MINUS , NULL,0 , NULL, $1, $3, NULL);}
		|expr MUL expr       {$$ = TreeCreate(TYPE_INT, NODE_MUL , NULL,0 , NULL, $1, $3, NULL);}
        |expr LT expr        {$$ = TreeCreate(TYPE_BOOL, NODE_LT , NULL, 0, NULL, $1, $3, NULL);}
        |expr GT expr        {$$ = TreeCreate(TYPE_BOOL, NODE_GT , NULL, 0, NULL, $1, $3, NULL);}
        |expr DEQ expr       {$$ = TreeCreate(TYPE_BOOL, NODE_DEQ , NULL,0, NULL, $1, $3, NULL);}
        | '(' expr ')'       {$$ = $2;}
        | NUM	             {$$ = $1;}
        | ID 				 {
                                Gtemp=Glookup($1->NAME);
                                if(Gtemp==NULL){
                                    yyerror("undefined variable ");
                                    printf("%s",$1->NAME);
                                    exit(0);
                                }
                                else if(Gtemp->type == STYPE_ARR_INT || Gtemp->type == STYPE_ARR_BOOLEAN){
                                    yyerror("invalid reference to an array ");
                                    printf("%s",$1->NAME);
                                    exit(0);
                                }
                                else {
                                    $1->Gentry=Gtemp;
                                    if(Gtemp->type == STYPE_INT){
                                        $1->TYPE = TYPE_INT;
                                    }
                                    else if(Gtemp->type == STYPE_BOOLEAN){
                                        $1->TYPE = TYPE_BOOL;    
                                    }
                                    $$=$1;
                                }
                            }
        | ID '[' expr ']'     {   
                                Gtemp=Glookup($1->NAME);
                                if(Gtemp==NULL){
                                    printf("undefined variable ");
                                    printf("%s",$1->NAME);
                                    exit(0);
                                }
                                else if(Gtemp->type == STYPE_INT || Gtemp->type == STYPE_BOOLEAN){
                                    yyerror("invalid reference to a variable ");
                                    printf("%s",$1->NAME);
                                    exit(0);        
                                }
                                else { 
                                    $1->Gentry=Gtemp;
                                    if(Gtemp->type == STYPE_ARR_INT){
                                        $1->TYPE = TYPE_INT;
                                    }
                                    else if(Gtemp->type == STYPE_ARR_BOOLEAN){
                                        $1->TYPE = TYPE_BOOL;
                                    }
                                    if($3->TYPE==TYPE_BOOL) {printf("index value is not integer\n");exit(1);}
                                    $$ = TreeCreate($1->TYPE,NODE_ARR_ID,NULL,0,NULL,$1,$3,NULL);
                                }
                            }
        | T    {$$ = $1;}
        | F    {$$ = $1;}
        ;

%%

void yyerror(char const *s) 
{ 
    printf("yac yyerror %s\n",s); 
    return ;
} 

int main(int argc,char* argv[]) 
{ 
    if(argc > 1)
    {
        fp = fopen(argv[1],"r");
        if(fp)
            yyin = fp;
    }    
    yyparse(); 
    return 1; 
}
