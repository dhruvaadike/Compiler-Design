FILE *fp;

int reg_count = -1,label_count = -1;
int k;

void generate_code(struct Tnode *tree){
	fp = fopen("intercode","w+");
	if(fp == NULL){
		printf("Error generating the code : FILE not created\n");
		exit(1);
	}
	fprintf(fp, "START\n");
	fprintf(fp, "MOV SP 1000\n");	
	gen_code_eval(tree);
	fprintf(fp, "HALT\n");
	fclose(fp);
}

int register_count(){
	return reg_count;
}

int get_register(){
	if(reg_count < 7){
		reg_count++;
		return reg_count;
	}
	else{
		printf("Error : No enough registers to get_register | all registers are busy\n");
		exit(1);
	}
}

void free_register(){
	if(reg_count >= -1){
		reg_count--;
	}
}

void free_all_register(){
	reg_count = -1;
}

int get_label(){
	label_count++;
	return label_count;
}

int gen_code_eval(struct Tnode *tree){
	int index,i,j;
	if(fp == NULL){
		printf("Error : Output file for code generation in gen_code_eval function\n");
		exit(1);
	}
	switch(tree->TYPE){
		case TYPE_INT:
			switch(tree->NODETYPE){
   			 	case NODETYPE_PLUS:
	   				i = gen_code_eval(tree->Ptr1);
	   				j = gen_code_eval(tree->Ptr2);
	   				fprintf(fp, "ADD R%d R%d\n",i,j);
	   				free_register();
	   				return i;
	   				break;
	   		 	case NODETYPE_MUL:
   				 	i = gen_code_eval(tree->Ptr1);
	   				j = gen_code_eval(tree->Ptr2);
	   				fprintf(fp, "MUL R%d R%d\n",i,j);
	   				free_register();
	   				return i;
   				 	break;
   			 	case NODETYPE_LEAF:
   				 	i = get_register();
   				 	fprintf(fp, "MOV R%d %d\n",i,tree->VALUE);
   				 	return i;
   				 	break;
	         	case NODETYPE_ID:
	            	i = get_register();
					fprintf(fp,"MOV R%d [%d]\n",i,tree->Ptr1->NAME[0] - 'a');	            	
					return i;
					break;
   			 	//case NODETYPE_ARR_ID:
	           	//	break;
         		default:
   				 	printf("Error : Unknown NODETYPE under TYPE_INT\n");
   				 	exit(1);
   				 	break;
   		 	}
   			break;
		
		case TYPE_BOOLEAN:
			switch(tree->NODETYPE){
   				case NODETYPE_GT:	
					i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"GT R%d R%d\n",i,j);
					free_register();
					return i;					
   					break;
   				case NODETYPE_LT:
					i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"LT R%d R%d\n",i,j);									
					free_register();
					return i;   					
					break;
   			 	case NODETYPE_EQ:
					i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"EQ R%d R%d\n",i,j);
					free_register();
					return i;									
   					break;
   			 	case NODETYPE_GE:
           			i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"GE R%d R%d\n",i,j);
					free_register();
					return i;									
   					break;
         		case NODETYPE_LE:
           			i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"LE R%d R%d\n",i,j);
					free_register();
					return i;									
   					break;
         		case NODETYPE_NE:
           			i = gen_code_eval(tree->Ptr1);
					j = gen_code_eval(tree->Ptr2);
					fprintf(fp,"NE R%d R%d\n",i,j);
					free_register();
					return i;									
   					break;
         		case NODETYPE_LEAF:
   					i = get_register();
					fprintf(fp, "MOV R%d %d\n",i,tree->VALUE);
   				 	return i;
   				 	break;
         		case NODETYPE_ID:
					i = get_register();
					fprintf(fp,"MOV R%d [%d]\n",i,tree->Ptr1->NAME[0] - 'a');	            	
					return i;
           			break;
         		//case NODETYPE_ARR_ID:
           		//	break;
   			 	default:
   					printf("Error : Unknown NODETYPE under TYPE_BOOLEAN\n");
   				 	exit(1);
   					break;
   		 	}   		 
			break;

		case TYPE_VOID:
			switch(tree->NODETYPE){
				case NODETYPE_ASGN:
					i = gen_code_eval(tree->Ptr2);
					fprintf(fp, "MOV [%d] R%d\n",(tree->Ptr1->NAME)[0] - 'a',i);
					free_register();
					break;
				//case NODETYPE_ARR_ASGN:
   				//	break;
				case NODETYPE_READ:
					i = get_register();
					fprintf(fp, "IN R%d\n",i);
					fprintf(fp,"MOV [%d] R%d\n",tree->Ptr1->NAME[0] - 'a',i);
					free_register();
					break;
				//case NODETYPE_ARR_READ:
   				//	break;
				case NODETYPE_WRITE:
					i = gen_code_eval(tree->Ptr1);
					fprintf(fp, "OUT R%d\n",i);
					free_register();
					break;
				case NODETYPE_IF:
					i = gen_code_eval(tree->Ptr1);
					j = get_label();
					fprintf(fp, "JZ R%d L%d\n",i,j);
					gen_code_eval(tree->Ptr2);
					if(tree->Ptr3 != NULL){	
						k = get_label();
						fprintf(fp,"JMP L%d\n",k);
						fprintf(fp,"L%d:\n",j);
						gen_code_eval(tree->Ptr3);
						fprintf(fp,"L%d:\n",k);
					}
					else{
						fprintf(fp,"L%d:\n",j);
					}
					free_register();						
					break;
				case NODETYPE_WHILE:
					i = get_label();
					k = get_label();
					fprintf(fp,"L%d:\n",i);
					j = gen_code_eval(tree->Ptr1);
					fprintf(fp,"JZ R%d L%d\n",j,k);
					free_register();
					gen_code_eval(tree->Ptr2);
					fprintf(fp,"JMP L%d\n",i);
					fprintf(fp,"L%d:\n",k);				
					break;
				case NODETYPE_ID:
					i = get_register();
					fprintf(fp,"MOV R%d [%d]\n",i,tree->NAME[0] - 'a');	            	
					return i;
					break;
				//case NODETYPE_ARR_ID:
   				//	break;
				case NODETYPE_NONE:
					gen_code_eval(tree->Ptr1);
					gen_code_eval(tree->Ptr2);
					break;
				default:
					printf("Error : Unknown NODETYPE under TYPE_VOID\n");
					exit(1);
					break;
			}
			break;
	
		default:
			printf("Error : Incorrect TYPE of the node\n");
			exit(1);
			break;
	}
}
