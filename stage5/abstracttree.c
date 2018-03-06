struct Tnode *TreeCreate(int TYPE,int NODETYPE,int VALUE,char *NAME,struct Tnode *ArgList,struct Tnode *Ptr1,struct Tnode *Ptr2,struct Tnode *Ptr3){
	struct Tnode *temp;
	temp = (struct Tnode *)malloc(sizeof(struct Tnode));
	temp->TYPE = TYPE;
	temp->NODETYPE = NODETYPE;
	temp->VALUE = VALUE;
	if(NAME != NULL){
		temp->NAME = (char *)malloc(sizeof(NAME));
		strcpy(temp->NAME,NAME);
	}else
	{
		temp->NAME = NULL; 	
	}
	temp->ArgList = ArgList;
	temp->Ptr1 = Ptr1;
	temp->Ptr2 = Ptr2;
	temp->Ptr3 = Ptr3;
	//Put Gsymbol and Lsymbol also
	temp->Gentry = NULL;
	temp->Lentry = NULL;
	return temp;
}

int Evaluate(struct Tnode *root){
	switch(root->TYPE){
		case TYPE_INT:
			switch(root->NODETYPE){
				case NODETYPE_PLUS:
					return Evaluate(root->Ptr1) + Evaluate(root->Ptr2);
					break;
				case NODETYPE_MUL:
					return Evaluate(root->Ptr1) * Evaluate(root->Ptr2);
					break;
				case NODETYPE_LEAF:
					return root->VALUE;
					break;
				default:
					printf("error\n");
					exit(1);
					break;
			}
			break;
		case TYPE_BOOLEAN:
			switch(root->NODETYPE){
				case NODETYPE_GT:
					return (Evaluate(root->Ptr1) > Evaluate(root->Ptr2));
					break;
				case NODETYPE_LT:
					return (Evaluate(root->Ptr1) < Evaluate(root->Ptr2));
					break;
				case NODETYPE_EQ:
					return (Evaluate(root->Ptr1) == Evaluate(root->Ptr2));
					break;
				case NODETYPE_LEAF:
					return root->VALUE;
					break;
				default:
					printf("error\n");
					exit(1);
					break;
			}			
			break;
		case TYPE_VOID:
			switch(root->NODETYPE){
				case NODETYPE_ASGN:
					if(value[(root->Ptr1->NAME)[0] - 'a'] == NULL){
						value[(root->Ptr1->NAME)[0] - 'a'] = malloc(sizeof(int*));
					}
					*value[(root->Ptr1->NAME)[0] - 'a'] = Evaluate(root->Ptr2);
					return 1;
					break;
				case NODETYPE_READ:
					value[(root->Ptr1->NAME)[0] - 'a'] = malloc(sizeof(int*));
					scanf("%d",value[(root->Ptr1->NAME)[0] - 'a']);
					return 1;
					break;
				case NODETYPE_WRITE:
					printf("%d\n",Evaluate(root->Ptr1));
					return 1;
					break;
				case NODETYPE_IF:
					if(Evaluate(root->Ptr1)){
						Evaluate(root->Ptr2);
					}else if(root->Ptr3 != NULL){
						Evaluate(root->Ptr3);
					}
					return 1;
					break;
				case NODETYPE_WHILE:
					while(Evaluate(root->Ptr1)){
						Evaluate(root->Ptr2);
					}
					return 1;
					break;
				case NODETYPE_ID:
					if(value[(root->NAME)[0] - 'a'] != NULL){
						return *value[(root->NAME)[0] - 'a'];
					}
					else{
						printf("error\n");
						exit(1);
					}
					break;
				case NODETYPE_NONE:
					Evaluate(root->Ptr1);
					Evaluate(root->Ptr2);
					return 1;
					break;
				default:
					printf("error\n");
					exit(1);
					break;
			}
			break;
		default:
			printf("error\n");
			exit(1);
			break;
	}
}
