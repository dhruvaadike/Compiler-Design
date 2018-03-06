FILE *fp;
int cur_reg = -1,label = -1;
int k;

int reg_num()
{
	return cur_reg;
}

int get_reg()
{
	cur_reg += 1;
	if(cur_reg<=7)
	{
		return cur_reg;
	}
	else 
	{
		cur_reg -= 1;
		printf("Registers not available.\n");
	}
}

int free_reg()
{
	if(cur_reg>=-1) cur_reg -= 1;
}

int get_label()
{
	label += 1;
	return label;
}

void Generate(struct Tnode *root){
	fp = fopen("assembly","w+");
	if(fp == NULL){
		printf("assembly file not created.\n");
		exit(1);
	}
	fprintf(fp, "START\n");
	fprintf(fp, "MOV SP 1000\n");	
	Codegen(root);
	fprintf(fp, "HALT\n");
	fclose(fp);
}




int Codegen(struct Tnode *root)
{
	int r1,r2,index,l1,l2;
	switch(root->TYPE)
	{
		case TYPE_INT:
			switch(root->NODE)
			{
				case NODE_PLUS:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_MINUS:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"SUB R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_MUL:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"MUL R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_LEAF:
					r1 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r1,root->VALUE);
					return r1;
					break;
				case NODE_ID:
					r1 = get_reg();
					fprintf(fp,"MOV R%d [%d]\n",r1,(root->Gentry->binding));
					return r1;
					break;
				case NODE_ARR_ID:
					r1 = Codegen(root->Ptr2);
					r2 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r2,(root->Ptr1->Gentry->binding));
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					fprintf(fp,"MOV R%d [R%d]\n",r1,r1);
					return r1;
					break;
				default:
					printf("Error : Unknown NODETYPE under TYPE_INT\n");
					exit(1);
					break;
			}
			break;
		case TYPE_BOOL:
			switch(root->NODE)
			{
				case NODE_GT:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"GT R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_LT:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"LT R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_DEQ:
					r1 = Codegen(root->Ptr1);
					r2 = Codegen(root->Ptr2);
					fprintf(fp,"EQ R%d R%d\n",r1,r2);
					free_reg();
					return r1;
					break;
				case NODE_LEAF:
					r1 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r1,root->VALUE);
					return r1;
					break;
				case NODE_ID:
					r1 = get_reg();
					fprintf(fp,"MOV R%d [%d]\n",r1,(root->Gentry->binding));
					return r1;
					break;
				case NODE_ARR_ID:
					r1 = Codegen(root->Ptr2);
					r2 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r2,(root->Ptr1->Gentry->binding));
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					fprintf(fp,"MOV R%d [R%d]\n",r1,r1);
					return r1;
					break;
				default:
					printf("Error : Unknown NODETYPE under TYPE_BOOLEAN\n");
					exit(1);
					break;
			}
			break;
		case TYPE_VOID:
			switch(root->NODE)
			{
				case NODE_ASGN:
					r1 = Codegen(root->Ptr2);
					fprintf(fp,"MOV [%d] R%d\n",root->Ptr1->Gentry->binding,r1);
					free_reg();
					break;
				case NODE_ARR_ASGN:
					r1 = Codegen(root->Ptr2);
					r2 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r2,(root->Ptr1->Gentry->binding));
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					r2=Codegen(root->Ptr3);
					fprintf(fp,"MOV [R%d] R%d\n",r1,r2);
					free_reg(); 
					//free_reg();  // check point 
					break;
				case NODE_READ:
					r1=get_reg();
					fprintf(fp,"IN R%d\n",r1);
					fprintf(fp, "MOV [%d] R%d\n",root->Ptr1->Gentry->binding,r1);
					free_reg();
					break;
				case NODE_ARR_READ:
					r1=get_reg();
					fprintf(fp,"MOV R%d %d\n",r1,root->Ptr1->Gentry->binding);
					r2=Codegen(root->Ptr2);
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					r2=get_reg();
					fprintf(fp,"IN R%d\n",r2);
					fprintf(fp,"MOV [R%d] R%d\n",r1,r2);
					free_reg(); 
					//free_reg(); // check point 
					break;
				case NODE_WRITE:
					//fprintf(fp, "inwrite\n");
					r1=Codegen(root->Ptr1);
					fprintf(fp,"OUT R%d\n",r1);
					free_reg();
					break;
				case NODE_IF:
					r1=Codegen(root->Ptr1);
					l1=get_label();
					fprintf(fp,"JZ R%d L%d\n",r1,l1);
					free_reg();
					Codegen(root->Ptr2);
					fprintf(fp,"L%d:\n",l1);
					break;
				case NODE_IF_ELSE:
					r1=Codegen(root->Ptr1);
					l1=get_label();
					l2=get_label();
					fprintf(fp,"JZ R%d L%d\n",r1,l1);
					Codegen(root->Ptr2);
					fprintf(fp,"JMP L%d\n",l2);	
					fprintf(fp,"L%d:\n",l1);
					Codegen(root->Ptr3);
					fprintf(fp,"L%d:\n",l2);
					free_reg();
					break;
				case NODE_WHILE:
					l1=get_label();
					l2=get_label();
					fprintf(fp,"L%d\n",l1);
					r1=Codegen(root->Ptr1);
					fprintf(fp,"JZ R%d L%d\n",r1,l2);
					Codegen(root->Ptr2);
					fprintf(fp,"JMP L%d\n",l1);
					fprintf(fp,"L%d:\n",l2);
					free_reg();
					break;
				case NODE_ID:
					r1 = get_reg();
					fprintf(fp,"MOV R%d [%d]\n",r1,(root->Gentry->binding));
					return r1;
					break;
				case NODE_ARR_ID:
					r1 = Codegen(root->Ptr2);
					r2 = get_reg();
					fprintf(fp,"MOV R%d %d\n",r2,(root->Ptr1->Gentry->binding));
					fprintf(fp,"ADD R%d R%d\n",r1,r2);
					free_reg();
					fprintf(fp,"MOV R%d [R%d]\n",r1,r1);
					return r1;
					break;
				case IS_TOP:
					Codegen(root->Ptr1);
					Codegen(root->Ptr2);
					break;
				default:
					printf("Error : Unknown NODETYPE under TYPE_VOID\n");
					exit(1);
					break;
			}
			break;
		default:
			printf("Error : Unknown TYPE-> %s\n",root->TYPE);
			exit(1);
			break;

	}
	return 0;
}