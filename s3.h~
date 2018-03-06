/*
	Node structure
	an operator to indicating the operator branch
	a value : for expression tree
	and left , right : left and right branches 
*/
struct Node{
	char *operatorr;
	int *value;
	struct Node *left,*right;
};


struct Node* mkOperatorNode(char c,struct Node *l,struct Node *r);

struct Node* mkLeafNode(int n);

int evaluate(struct Node *t);

int *value[26];

/*
	@arguments : n - value , 
	@return    : a leafnode of expression tree with the value attribute set with argument passed
*/
struct Node* mkLeafNode(int n){
	struct Node *temp;
	temp = (struct Node *)malloc(sizeof(struct Node));	
	temp->operatorr= NULL;
	temp->value = malloc(sizeof(int));
	*(temp->value) = n;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

/*
	@arguments : c - operator , *l - left branch pointer, *r - right branch pointer
	@return    : a tree with operator as root and with left and right branches passed
*/
struct Node* mkOperatorNode(char c,struct Node *l,struct Node *r){
	struct Node *temp;	
	temp = (struct Node *)malloc(sizeof(struct Node));	
	temp->operatorr = malloc(sizeof(char));	
	*(temp->operatorr) = c;
	temp->value = NULL;
	temp->left = l;
	temp->right = r;
	return temp;
}

/*
	@argument : t : expression tree
	@return   : the value of expression tree
*/
int evaluate(struct Node *t){
	if(t->operatorr == NULL)
		return *(t->value);
	if(t->value == NULL && t->left == NULL && t->right == NULL){
		if(value[*(t->operatorr) - 'a'] == NULL){
            printf("undeclared variable\n");
        }
        else{
            return *value[*(t->operatorr) - 'a'];
        }
	}
	switch(*(t->operatorr)){
		case '+' : return evaluate(t->left) + evaluate(t->right);break;
		case '-' : return evaluate(t->left) - evaluate(t->right);break;
		case '*' : return evaluate(t->left) * evaluate(t->right);break;
		case '/' : return evaluate(t->left) / evaluate(t->right);break;
		case '=' : if(value[*(t->left->operatorr) - 'a'] == NULL){
						value[*(t->left->operatorr) - 'a'] = malloc(sizeof(int*));
					}
					*value[*(t->left->operatorr) - 'a'] = evaluate(t->right);
					break;
		case 'R' : if(value[*(t->left->operatorr) - 'a'] == NULL){
						value[*(t->left->operatorr) - 'a'] = malloc(sizeof(int*));
					}
					scanf("%d",value[*(t->left->operatorr) - 'a' ]);
					break;
		case 'W' : printf("%d\n",evaluate(t->left));break;
		case 'S': evaluate(t->left);evaluate(t->right);break;
	}
}
