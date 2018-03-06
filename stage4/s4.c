struct Tnode* makeNode(int type,int nodetype,char *name, int value, struct Tnode *ptr1,struct Tnode *ptr2,struct Tnode *ptr3){
	struct Tnode *temp;
	temp = (struct Tnode *)malloc(sizeof(struct Tnode));
	temp->TYPE = type;
	temp->NODETYPE = nodetype;
	if(name != NULL)
	{
		temp->NAME = malloc(sizeof(name));
		strcpy(temp->NAME,name);
	}
	else
		temp->NAME = NULL;
	temp->VALUE=value;
	temp->ptr1 = ptr1;
	temp->ptr2 = ptr2;
	temp->ptr3 = ptr3;
	//temp->Gentry = NULL;
	//temp->Lentry = NULL;
}

int eval(struct Tnode *n){
	if(n!=NULL){
		switch(n->TYPE){
			case TYPE_INT: switch(n->NODETYPE){
						case NODETYPE_PLUS: return eval(n->ptr1)+eval(n->ptr2);break;
						case NODETYPE_MUL:  return eval(n->ptr1)*eval(n->ptr2);break;
						case NODETYPE_LEAF: return (n->VALUE);break;
					}
					break;
			case TYPE_BOOL: switch(n->NODETYPE){
						case NODETYPE_GT: if(eval(n->ptr1)>eval(n->ptr2)) 
									return RTRUE;
								  else
									return RFALSE;
								  break;
						case NODETYPE_LT: if(eval(n->ptr1)<eval(n->ptr2)) 
									return RTRUE;
								  else
									return RFALSE;
								  break;
						case NODETYPE_EQ: if(eval(n->ptr1)==eval(n->ptr2)) 
									return RTRUE;
								  else
									return RFALSE;
								  break;
						
					}
				        break;
			case TYPE_VOID:	switch(n->NODETYPE){
						case NODETYPE_ID : 
							if(var[(n->NAME)[0] - 'a'] != NULL){
								return *var[(n->NAME)[0] - 'a'];
							}
							else{
								printf("error\n");
								exit(1);
							}
							break;
						case NODETYPE_SLIST:
							eval(n->ptr1);
							eval(n->ptr2);
							break;
						case NODETYPE_ASGN:
							if(var[(n->ptr1->NAME)[0] - 'a'] == NULL)
								var[(n->ptr1->NAME)[0] - 'a'] = malloc(sizeof(int*));
							*var[(n->ptr1->NAME)[0] - 'a'] = eval(n->ptr2);
							return 1;
							break;
						case NODETYPE_READ:
							if(var[(n->ptr1->NAME)[0] - 'a'] == NULL)
								var[(n->ptr1->NAME)[0] - 'a'] = malloc(sizeof(int*));
							scanf("%d",var[(n->ptr1->NAME)[0] - 'a']);
							return 1;
							break;
						case NODETYPE_WRITE:
							printf("%d\n",eval(n->ptr1));
							return 1;
							break;
						case NODETYPE_IF:
							if(eval(n->ptr1) == RTRUE)
								eval(n->ptr2);
							else if(n->ptr3 != NULL)
								eval(n->ptr3);
							return 1;
							break;
						case NODETYPE_WHILE:
							while(eval(n->ptr1) == RTRUE)
								eval(n->ptr2);
							return 1;
							break;				
					}
		}
	}

}




