struct Gsymbol* Glookup(char* name){
    struct Gsymbol *temp;
    temp = Ghead;
    while(temp != NULL && strcmp(temp->name,name) != 0){
   	 temp = temp->next;    
    }
    return temp;    
}

void Ginstall(char* name, int type,int size,struct ArgStruct *Arglist){
    struct Gsymbol *check;
    check = Glookup(name);
    if(check != NULL)			
	  {
        yyerror("variable redefined ");
        printf(" %s",name);
        exit(0);
    }
    struct Gsymbol *temp;
    temp = (struct Gsymbol *)malloc(sizeof(struct Gsymbol));
    temp->name = (char *)malloc(sizeof(name));
    strcpy(temp->name,name);
    temp->type = type;
    temp->size = size;
    temp->Arglist = Arglist;
    temp->next = NULL;
    switch(temp->type){
   	 case STYPE_INT:
   		 temp->binding = malloc(sizeof(int));
   		 break;
   	 case STYPE_BOOLEAN:
   		 temp->binding = malloc(sizeof(int));
   		 break;
   	 case STYPE_ARR_INT:
   		 temp->binding = malloc(sizeof(int)*(temp->size));
   		 break;
   	 case STYPE_ARR_BOOLEAN:
   		 temp->binding = malloc(sizeof(int)*(temp->size));
   		 break;
   	 default:
   		 printf("unknown type to allocate space in Gsymbol table\n");
   		 break;
    }
       
    
    /*adding the node to symbol table entries*/
    if(Ghead == NULL){
   	 Ghead = temp;   	 
   	 return;    
    }
    temp->next = Ghead;
    Ghead = temp;
    return;
}

