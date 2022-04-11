#include "RST.h"
using namespace std;

//This is RST Node or Treap Node constructor
TreapNode::TreapNode(){
			key=0;
			priority=0;
			h=0;
			left=NULL;
			right=NULL;
}

//This is Treap node parameterised constructor with random priority
TreapNode::TreapNode(int item){
			key=item;
			priority=rand()%1000+1;   //random value is generated using rand() function
			h=0;
			left=NULL;
			right=NULL;
		
}

//This is Treap node parameterised constructor with user defined priority
TreapNode::TreapNode(int item,int p){
			key=item;
			priority=p;
			h=0;
			left=NULL;
			right=NULL;
}

//This is code for destructor helper function
void RST::clear(TreapNode* node){
	if(node==NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete(node);
	return;
}

//Destructor
RST::~RST(){
	clear(root);
	root=NULL;
}

//copy constructor
RST::RST(const RST &T){
	root=RST_copy(T.root);
}
TreapNode* RST::RST_copy(TreapNode* root){						//Helper function for copy constructor
	if(root==NULL){
		return NULL;
	}
	TreapNode* temp=new TreapNode(root->key);					//Creating new node for attaching in the copy_of_tree
	temp->priority=root->priority;                              //Copying everything to temp
	temp->left=RST_copy(root->left);
	temp->right=RST_copy(root->right);
	return temp;
}
long long int RST::get_no_of_nodes(){
	return no_of_nodes;
}
long long int RST::get_total_rotation(){
	
	//Function simply returns the total_rotation variable that was updated during all the operations
	return total_rotations;
}
long long int RST::get_total_keycomparison(){
	
	//Function simply returns the total_Keycomparison variable that was updated during all the operations
	return total_keycomparison;
}
long long int RST::get_final_height(){
	
	//Function returns the final height using helper function
	return get_final_height(root);
}
//This final height function will recursively find the height of tree and also update each node's height variable with its height
long long int RST::get_final_height(TreapNode* node){
	
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
float RST::get_Average_height(){
	
	//This function finds sum of heights of all the nodes of the tree and no. of nodes of the tree
	get_Average_height(root);
	
	//to avoid divide by zero
	if(no_of_nodes==0)
	return 0;
	
	//Average height
	return (sum_of_height*1.0/no_of_nodes);
}
void RST::get_Average_height(TreapNode* node){
	
	//performing pre order traversal on tree and summing up all the height that were updated in final_height function 
	if(node==NULL){
		return ;
	}
	get_Average_height(node->left);
	sum_of_height+=node->h;
	no_of_nodes++;
	get_Average_height(node->right);
}
bool RST::Search(int item){						//Search function
	TreapNode *current=root;										
	if(current==NULL)								     	//If the root is NULL then the value doesn't exists
		{
			return false;
		}
	while(current){
		if(item<current->key){								//if Element is less than root than traversing left subtree
			current=current->left;
		}
		else
		if(item>current->key){								//if Element is greater than root than traversing right subtree
			current=current->right;
		}
		else												//Element if found
			return true;
			
	}
	return false;
	
}
void RST::Insert(int item){
	int p=rand()%1000+1;									//Generating random priority using rand() function
	root=insert(root,item,p);								//helper function to insert (k,p) pair
}
void RST::insert(int item,int p){							//Insert function for user defined priority				
	root=insert(root,item,p);
}
TreapNode* RST::insert(TreapNode* root,int item,int p){
		
	if(root == NULL)										//If the node is NULL simply adding newly created and node and returning it
		return new TreapNode(item,p);
	
	total_keycomparison++;									//Updating the no. of comparison for each node visit 
	if(item < root->key){
		
		//Node to be inserted in left subtree
		root->left = insert(root->left,item,p);
		
		//checking whether rotation is required or not
		if(root->priority > root->left->priority){
		
			//Performing Right rotation 
			/*     root(key,2)
			     /           \
			child(key,1)	child   RIGHT ROTATION
			*/
			TreapNode *lt = root->left;
			TreapNode *right_of_left = lt->right;
			lt->right = root;
			root->left = right_of_left;
			
			total_rotations++;     							//Updating the total number of rotation count
			return lt;
		}
		return root;
	}	
	else if(item > root->key){
		
		//Node to be inserted in right subtree
		root->right = insert(root->right,item,p);
		
		//checking whether rotation is required or not
		if(root->priority > root->right->priority){
			
			//Performing left rotation 
			/*     root(key,2)
			     /           \
			child	      child(key,1)   LEFT ROTATION
			*/
			TreapNode *rt = root->right;
			TreapNode *left_of_right = rt->left;
			rt->left = root;
			root->right = left_of_right;
			
			total_rotations++;								//Updating the total number of rotation count
			return rt;
		}
		return root;
	}	
	return root; 
}
void RST::Delete(int item){									//function to delete a node using helper function
	root=Delete(root,item);
}
TreapNode* RST:: fix_priority(TreapNode* root){
	
	//This function does rotations if required, to maintain the heap property in treaps
	if(root == NULL)
		return NULL;
		
	total_keycomparison++;									//Updating the no. of comparison for each node visit
	
	int left_priority = INT_MAX; 							//initailising left and right child priority as infinity
	int right_priority = INT_MAX;
	
	// CASE 1: node to be deleted is a leaf node
	if(root->left == NULL && root->right == NULL){
		return NULL; 
	}
	// left child exists therefore updating left child priority
	if(root->left != NULL)
		left_priority = root->left->priority;
		
	//  right child exists therefore updating right child priority
	if(root->right != NULL)
		right_priority = root->right->priority;
	
	//Performing right rotation 
			/*     node(key,infinity)
			     /              \
			leftchild(key,1)   rightchild(key,2)   RIGHT ROTATION
			*/	
	if(left_priority < right_priority){
		
		TreapNode *lt = root->left;
		TreapNode *right_of_left = lt->right;
		lt->right = root;
		root->left = right_of_left;
		
		total_rotations++;								//Updating the total number of rotation count
		lt->right = fix_priority(lt->right);			//fixing priority now for right child
	
		return lt;
	}
	//Performing left rotation 
			/*     node(key,infinity)
			     /              \
			leftchild(key,2)   rightchild(key,1)   LEFT ROTATION
			*/	
	else{
		
		TreapNode *rt = root->right;
		TreapNode *left_of_right = rt->left;
		rt->left = root;
		root->right = left_of_right;
		
		total_rotations++;								//Updating the total number of rotation count
		rt->left = fix_priority(rt->left);				//fixing priority now for left child
	
		return rt;
	}
	
}
TreapNode* RST::Delete(TreapNode* root,int item){
	
	TreapNode *new_root = NULL;
	
	//if the tree doesn't contain the item returning null
	if(root == NULL)
		return NULL;
		
	total_keycomparison++;										//Updating the no. of comparison for each node visit 
	if(item < root->key){	
		//item to be deleted is may be in the left subtree	
		root->left = Delete(root->left, item);
		}
	else if(item > root->key){	
		//item to be deleted is may be in the right subtree
		root->right = Delete(root->right, item);
	}
	else{
		//found the node to be deleted, making its priority as infinity so as to move it downwards and maintain heap property also
		root->priority = INT_MAX;
		
		//fixing the priorties downwards 
		new_root = fix_priority(root);
		delete(root);
		root = new_root;
	}
	return root;
	
}

void RST::getOrder(TreapNode* rt,FILE* fp) {
	
	if(rt == NULL) {													//Returning when root is NULL
		return;
	}
	
	//Printing label as key and priority with left and right pointer
   	fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->key,rt->key,rt->priority);
	if(rt->left){
		getOrder(rt->left,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->left->key,rt->left->key,rt->left->priority);
		fprintf(fp,"\"%d\":f0->\"%d\":f1;\n",rt->key,rt->left->key);
	}
	if(rt->right){
		getOrder(rt->right,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->right->key,rt->right->key,rt->right->priority);
		fprintf(fp,"\"%d\":f3->\"%d\":f1;\n",rt->key,rt->right->key);
	}
	
}
void RST::Print(const char *filename){
	FILE* fp;
	fp=fopen("t.dotgv","w+");
    fprintf(fp,"%s\n","digraph {");
    fprintf(fp,"%s\n","node [shape = record, height=.1]");    
    TreapNode* pointer=root;
    getOrder(pointer,fp);										//Creating syntax and writing it to t.dotgv file
	
    fprintf(fp,"%s\n", "}");
	fclose(fp);
    string cmd = "dot -Tpng t.dotgv -o"+ string(filename); 		//Syntax to get output in filename 
    system((const char*)cmd.c_str());
    
}
