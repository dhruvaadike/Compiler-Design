struct Tnode *TreeCreate(int TYPE,int NODE,char* NAME,int VALUE,struct Tnode *ArgList,
										struct Tnode *Ptr1,struct Tnode *Ptr2,struct Tnode *Ptr3)
{
    
	  switch(NODE){
    	case NODE_IF    : if(Ptr1->TYPE != TYPE_BOOL){
    			 	yyerror("unexpected type of expression in if");exit(0);}
    			      break;
    	case NODE_IF_ELSE    : if(Ptr1->TYPE != TYPE_BOOL){
    			 	yyerror("unexpected type of expression in if_else");exit(0);}
    			      break;
    	case NODE_WHILE : if(Ptr1->TYPE != TYPE_BOOL){
    			 	yyerror("unexpected type of expression in while");exit(0);}
    			      break;
    	case NODE_PLUS  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for plus operation");exit(0);}
    	  		      break;
    	case NODE_MINUS  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for plus operation");exit(0);}
    	  		      break;
    	case NODE_MUL   : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
       		 		yyerror("mismatching operands for multiplication operation");exit(0);}
  		  	      break;
    	case NODE_GT    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for greater than relational operation");exit(0);}
    			      break;
    	case NODE_LT    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for lesser than relational operation");exit(0);}
    			      break;
    	case NODE_DEQ    : if(!((Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT) || (Ptr1->TYPE == TYPE_BOOL && Ptr2->TYPE == TYPE_BOOL))){
    			 	yyerror("mismatching operands for equal to relational operation");exit(0);}
    			      break;
    	case NODE_ASGN  : if(!((Ptr1->Gentry->type == STYPE_INT && Ptr2->TYPE == TYPE_INT)||(Ptr1->Gentry->type==STYPE_BOOLEAN && Ptr2->TYPE==TYPE_BOOL))){
    				yyerror("1.unexpected type of value for the variable");exit(0);
    			      }
                break; 
    	case NODE_ARR_ASGN : if(!((Ptr1->Gentry->type == STYPE_ARR_INT && Ptr3->TYPE == TYPE_INT)||(Ptr1->Gentry->type==STYPE_ARR_BOOLEAN && Ptr3->TYPE==TYPE_BOOL))){
    				yyerror("2.unexpected type of value for the variable");exit(0);
    			      }
                break;  	

    }
  
	struct Tnode * temp;
	temp = (struct Tnode*)malloc(sizeof(struct Tnode));
	temp -> TYPE = TYPE;
	temp -> NODE = NODE;
	temp -> NAME = NAME;
	temp -> VALUE =  VALUE;
	temp -> ArgList = ArgList;
	temp -> Ptr1 = Ptr1;
	temp -> Ptr2 = Ptr2;
	temp -> Ptr3 = Ptr3;
	temp -> Gentry = NULL;
	
	return temp;
}

int Evaluate(struct Tnode *root){
    int index;
    switch(root->TYPE){
   	 case TYPE_INT:
   		 switch(root->NODE){
   			 case NODE_PLUS:
   				 return Evaluate(root->Ptr1) + Evaluate(root->Ptr2);
   				 break;
   			 case NODE_MINUS:
   				 return Evaluate(root->Ptr1) - Evaluate(root->Ptr2);
   				 break;
   			 case NODE_MUL:
   				 return Evaluate(root->Ptr1) * Evaluate(root->Ptr2);
   				 break;
   			 case NODE_LEAF:
   				 return root->VALUE;
   				 break;
   			 case NODE_ID:
   			 	 return *(root->Gentry->binding);
   				 break;
   			 case NODE_ARR_ID:
   				 index = Evaluate(root->Ptr2);
   					 if(root->Ptr1->Gentry->type == STYPE_ARR_INT )
   					  {
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size)
   				     	 {
   				     		 return *((root->Ptr1->Gentry->binding)+index);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				      }

   			
   				 break;
	         default:
	   				 printf("error\n");
	   				 exit(1);
	   				 break;
   		 }
   		 break;
   	 case TYPE_BOOL:
   		 switch(root->NODE){
   			 case NODE_GT:
   				 return (Evaluate(root->Ptr1) > Evaluate(root->Ptr2));
   				 break;
   			 case NODE_LT:
   				 return (Evaluate(root->Ptr1) < Evaluate(root->Ptr2));
   				 break;
   			 case NODE_DEQ:
   				 return (Evaluate(root->Ptr1) == Evaluate(root->Ptr2));
   				 break;
   			 case NODE_LEAF:
   				 return root->VALUE;
   				 break;
   			 case NODE_ID:
   				     	 return *(root->Gentry->binding);

   				 
   				 break;
   			 case NODE_ARR_ID:
   				 index = Evaluate(root->Ptr2);
   					
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size)
   				     	 {
   				     		 return *((root->Ptr1->Gentry->binding)+index);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				   break;
   			 default:
   				 printf("error\n");
   				 exit(1);
   				 break;
   		    }		 
   		 break;
   	 case TYPE_VOID:
   		 switch(root->NODE) 
   		 {
   			 case NODE_ASGN:
   					 if(root->Ptr1->Gentry->type == STYPE_INT || root->Ptr1->Gentry->type == STYPE_BOOLEAN){
   				     	 *(root->Ptr1->Gentry->binding) = Evaluate(root->Ptr2);
   				      }
   				     
   				
   				 break;
   			 case NODE_ARR_ASGN:
   				 index = Evaluate(root->Ptr2);
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
   				     		 *(root->Ptr1->Gentry->binding+index) = Evaluate(root->Ptr3);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				
   				 break;
   			 case NODE_READ:
   					 if(root->Ptr1->Gentry->type == STYPE_INT)
   					 {
   				     	 scanf("%d",root->Ptr1->Gentry->binding);
   				     }
		              else if(root->Ptr1->Gentry->type == STYPE_BOOLEAN)
		              {
		                char temp[5];
		                scanf("%s",temp);
		                if(strcmp(temp,"true") == 0){
		                  *(root->Ptr1->Gentry->binding) = 1;  
		                }
		                else if(strcmp(temp,"false") == 0){
		                  *(root->Ptr1->Gentry->binding) = 0;
		                }
		                else{
		                  printf("Incompatible type with boolean\n");
		                  exit(1);
		                }
		              } 
   				 break;
   			 case NODE_ARR_READ:
   				 index = Evaluate(root->Ptr2);
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
	                  if(root->Ptr1->Gentry->type == STYPE_ARR_INT){
	   				     		 scanf("%d",(root->Ptr1->Gentry->binding)+index);
	                  }
	                  else{
	                    char temp[5];
	                    scanf("%s",temp);
	                    if(strcmp(temp,"true") == 0){
	                      *((root->Ptr1->Gentry->binding)+index) = 1;  
	                    }
	                    else if(strcmp(temp,"false") == 0){
	                      *((root->Ptr1->Gentry->binding)+index) = 0;
	                    }
	                    else{
	                      printf("Incompatible type with boolean\n");
	                      exit(1);
	                    }
	                  }
	              }
	              else
   				    { 		
   				    		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   								exit(1);
   					}				
	   				     	
	   				     
   				 break;
   			 case NODE_WRITE:
				   if(root->Ptr1->TYPE == TYPE_BOOL){
              if(Evaluate(root->Ptr1)){
                printf("true\n");
              }
              else{
                printf("false\n");
              }
           }
           else{
              printf("%d\n",Evaluate(root->Ptr1));
   				 }
           break;
   			 case NODE_IF:
   				 if(Evaluate(root->Ptr1)){
   					 Evaluate(root->Ptr2);
   				 }
   				 //return 1;
   				 break;
   			case NODE_IF_ELSE:
   				 if(Evaluate(root->Ptr1)){
   					 Evaluate(root->Ptr2);
   				 }
   				 else {
   					 Evaluate(root->Ptr3);
   				 }
   				 //return 1;
   				 break;
   			 case NODE_WHILE:
   				 while(Evaluate(root->Ptr1)){
   					 Evaluate(root->Ptr2);
   				 }
   				 //return 1;
   				 break;
   			 case NODE_ID:
   				     	 return *(root->Gentry->binding);
   				     
   				 
   				 break;
   			 case NODE_ARR_ID:
   				 index = Evaluate(root->Ptr2);
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
   				     		 return *((root->Ptr1->Gentry->binding)+index);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				      
   				     
   				
   				 break;
   			 case IS_TOP:
   				 Evaluate(root->Ptr1);
   				 Evaluate(root->Ptr2);
   				 //return 1;
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
    return 0;
}



















