#include "BST.h"
BstNode::BstNode(){								//This is the BST node constructor
			value=0;
			h=0;
			left=NULL;
			right=NULL;
}
BstNode::BstNode(int item){						//This is BST Node parameterised constructor
			value=item;
			h=0;
			left=NULL;
			right=NULL;
		
}
//This is code for destructor helper function
void BST::clear(BstNode* node){
	if(node==NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete(node);
	return;
}

//Destructor
BST::~BST(){
	clear(root);
	root=NULL;
}
bool BST::Search(int item){							//Used to serach an element in the tree using a helper function search(item,root)
	if(search(item,root)){
		return true;
	}
	else
	return false;
}
BstNode* BST::search(int item,BstNode* root){
	BstNode* ptr=root;
	while(ptr!=NULL){
		total_keycomparison++; 						//updating no. of comparisons on node visits
		if(ptr->value==item){
			return ptr;								//Element is found therefore return reference
			}
		else if(item>ptr->value){					//If item values is greater than root value than moving to right subtree				
					ptr=ptr->right;				
			}
		else{
			if(item<ptr->value){					//If item values is less than root value than moving to left subtree				
					ptr=ptr->left;			
			}
		}
	}
	return NULL;
}
void BST::Insert(int item){							//Function to insert an element in the tree using helper function
	root=insert(root,item);
}

BstNode* BST::insert(BstNode* root,int item){

	if(root==NULL)									//If root is NULL returning the newly created node simply
		return new BstNode(item);
	total_keycomparison++;							//Updating the no. of comparisons on each node visit in recursive function
	
	//Searching the tree recursively to find position of insertion
	if(item< root->value){		
		root->left=insert(root->left,item);
	}
	else{
		if(item> root->value){
			root->right=insert(root->right,item);
		}
		else{
			return root;
		}
	}
	return root;
}

void BST::Delete(int item){
	int temp=total_keycomparison;
	if(search(item,root)==NULL){					//If the element is not present in the tree simply return by adding no. of comparison in search function
		return;
	}
	else{
		total_keycomparison=temp;					 
	}
	root=delete_(item,root);						//element is present so we will go and delete it
}
BstNode* BST::delete_(int item,BstNode* root){		
		total_keycomparison++;						//Updating no. of comparisons for each node visit in recursive calls
		if(item < root->value){
				root->left=delete_(item,root->left);
			}
		else{
				if(item > root->value){
					root->right=delete_(item,root->right);
					}
				else{
					//Node is leaf 
					if(root->left==NULL && root->right==NULL)
					{
						delete(root);
						return NULL;
					}
						
					else 
					//Node has single child replacing item node with its child and deleting it
					if(root->left!=NULL && root->right==NULL){
						BstNode* temp=root->left;
						delete(root);
						return temp;
					}
					else
						if(root->right!=NULL && root->left==NULL){
							BstNode* temp=root->right;
							delete(root);
							return temp;
						}
						else
						//Node has both the children
						{
							//finding inorder successor and then replacing it with item and deleting it
							BstNode* succ=left_most(root->right);
							root->value=succ->value;
							root->right=delete_(succ->value,root->right);
						}	
					}
				}			
						
		return root;		
}
BstNode* BST::right_most(BstNode* root){
	//Moving right until we get the leaf node and also check whether right pointer is valid or not
	BstNode* temp=root;
	while(temp!=NULL && temp->right!=NULL){
		total_keycomparison++;				//Updating key comparisons for each node visit
		temp=temp->right;
	}
	return temp;
}

BstNode* BST::left_most(BstNode* root){	
	//Moving right until we get the leaf node and also check whether left pointer is valid or not
	BstNode* temp=root;
	while(temp!=NULL && temp->left!=NULL){
		total_keycomparison++;				//Updating key comparisons for each node visit
		temp=temp->left;
	}
	return temp;
}
void BST::getOrder(BstNode* root, FILE* fp) {
 	if(root == NULL) {													//Returning when root is NULL
		return;
	}
	
	//Printing label as value with left and right pointer
   	fprintf(fp,"%d [label = \"<f0> | <f1> %d |  <f2>\"];\n",root->value,root->value);
	if(root->left){
		getOrder(root->left,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d  | <f2>\"];\n",root->left->value,root->left->value);
		fprintf(fp,"\"%d\":f0->\"%d\":f1;\n",root->value,root->left->value);
	}
	if(root->right){
		getOrder(root->right,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2>\"];\n",root->right->value,root->right->value);
		fprintf(fp,"\"%d\":f2->\"%d\":f1;\n",root->value,root->right->value);
	}
    
}
void BST::printTree(const char *filename){
 	FILE* fp;
	fp=fopen("tree.dotgv","w+");
    fprintf(fp,"%s\n","digraph {");
    fprintf(fp,"%s\n","node [shape = record, height=.1]");    
    BstNode* pointer=root;
    getOrder(pointer,fp);										//Creating syntax and writing it to t.dotgv file
	
    fprintf(fp,"%s\n", "}");
	fclose(fp);
    string cmd = "dot -Tpng tree.dotgv -o"+ string(filename); 		//Syntax to get output in filename 
    system((const char*)cmd.c_str());
    
 
}
long long int BST::get_final_height(){
	//Function returns the final height using helper function
	return get_final_height(root);
}
//This final height function will recursively find the height of tree and also update each node's height variable with its height
long long int BST::get_final_height(BstNode* node){
	
	//if node is NULL returning height 0
	if(node==NULL){
		return 0;
	}
	
	//Taking convention as leaf node has height 0
	if(node->left==NULL && node->right==NULL){
		node->h=0;
		return 0;
	}
	
	//if single child then adding current node to height and moving to the child
	if(node->left==NULL && node->right!=NULL){
		
		return node->h=( 1+ get_final_height(node->right));
	}
	else
	if(node->left!=NULL && node->right==NULL){
		
		return node->h=(1+ get_final_height(node->left));
	}
	else
	{
		//if both the childs are present then height is taken as the max of two subtree's height
		return node->h=(1+max(get_final_height(node->left),get_final_height(node->right)));
	}
	
}
float BST::get_Average_height(){
	
	//This function finds sum of heights of all the nodes of the tree and no. of nodes of the tree
	get_Average_height(root);
	
	//to avoid divide by zero
	if(no_of_nodes==0)
	return 0;
	
	//Average height
	return (sum_of_height*1.0/no_of_nodes);
}
void BST::get_Average_height(BstNode* node){
	//performing pre order traversal on tree and summing up all the height that were updated in final_height function 
	if(node==NULL){
		return ;
	}
	get_Average_height(node->left);
	sum_of_height+=node->h;
	no_of_nodes++;
	get_Average_height(node->right);
}
long long int BST::get_total_rotation(){
	//Function simply returns the total_rotation variable that was updated during all the operations
	return total_rotations;
}
long long int BST::get_total_keycomparison(){
	//Function simply returns the total_Keycomparison variable that was updated during all the operations
	return total_keycomparison;
}
long long int BST::get_no_of_nodes(){
	return no_of_nodes;
}

