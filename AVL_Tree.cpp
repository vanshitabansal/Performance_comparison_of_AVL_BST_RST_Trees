#include "AVL_Tree.h"
using namespace std;

//copy constructor
AVL_Tree::AVL_Tree(const AVL_Tree &T){
	dummy=AVL_copy(T.dummy);
}
AVL_Node* AVL_Tree::AVL_copy(AVL_Node* root){				//Helper function for copy constructor
	if(root==NULL){
		return NULL;
	}
	AVL_Node* temp=new AVL_Node(root->key);					//Creating new node for attaching in the copy_of_tree
	temp->bf=root->bf;
	temp->LChild=AVL_copy(root->LChild);
	temp->RChild=AVL_copy(root->RChild);
	return temp;
}

bool AVL_Tree::AVL_Search(int item){						//Search function
	AVL_Node *current=dummy->RChild;										
	if(current==NULL)										//If the root is NULL then the value doesn't exists
		{
			return false;
		}
	while(current){
		if(item<current->key){								//if Element is less than root than traversing LChild subtree
			current=current->LChild;
		}
		else
		if(item>current->key){								//if Element is greater than root than traversing RChild subtree
			current=current->RChild;
		}
		else												//Element if found
			return true;
			
	}
	return false;
	
}

void AVL_Tree::Insert(int item){
	
	AVL_Node *T=dummy;										//Parent of node S(rebalancing point)
	AVL_Node *S=dummy->RChild;								//pointer to place where rebalancing might occur
	AVL_Node *P=dummy->RChild;								//pointer that traverses the tree
	AVL_Node *Q,*R;											//Q is temporary pointer
	
	AVL_Node *temp=new AVL_Node(item);						//Node temp created for item
	if(P==NULL){											//If tree is empty setting root to temp and Returning
		dummy->RChild=temp;
		return;
	}
	
	//Search and tracking S and T
	while(true){
		total_keycomparison++;								//Updating no. of comparisons for each node visit 
		if(item<P->key){            						//Moving to left subtree
			Q=P->LChild;				
			if(Q==NULL){
				P->LChild=temp;
				Q=P->LChild;
				break;
			}
			else{
				if(Q->bf!=0){							//rebalancing required here at node Q
					T=P;								//Parent of S
					S=Q;								//as S is pointer to rebalancing node
					
				}
				P=Q;									//Updating current pointer P
			}
		}
		else if(item>P->key){
			Q=P->RChild;
			if(Q==NULL){
				P->RChild=temp;
				Q=P->RChild;
				break;
			}
			else{
				if(Q->bf!=0){							//rebalancing required here at node Q
					T=P;								//Parent of S
					S=Q;								//as S is pointer to rebalancing node
			
				}
				P=Q;									//Updating current pointer P
			}
		}
		else{
			delete(temp);
			return;
		}
	}
	int a=0;											//to check where the node is added
	if(item<S->key){
		a=1;											//node is added to left
	}
	else{
		a=-1;											//node is added to right
	}
	auto link=[](int a,AVL_Node *P){					//for linking P to it's Lchild or RChild depending on where item is added
		if(a==1){
			return P->LChild;
		}
		else{
			return P->RChild;
		}
	};
	R=link(a,S);										//R is used for rotation
	P=link(a,S);										//P for adjusting balance factor
	
	while(P!=Q){										//adjusting all balance factor between S and Q
		total_keycomparison++;							//Updating no. of comparisons for each node visit 
		if(item<P->key){
			P->bf=1;
			P=P->LChild;
		}
		else if(item>P->key){
			P->bf=-1;
			P=P->RChild;
		}
	}
	if(S->bf==0){										//tree has got more height
		S->bf=a;
		return;
	}
	else if(S->bf==-1*a){								//tree has got more balanced
		S->bf=0;
		return;
	}
	else{
		//CASE 1: Single rotation
		
		if(R->bf==a){									//if both a and the side to which node is added are same
		total_rotations++;								//Updating no. of rotations for each rotation performed
			if(a==1){					
				P=R;									
				S->LChild=R->RChild;
				R->RChild=S;
				S->bf=0;
				R->bf=0;
				
			}
			else if(a==-1){				
				P=R;
				S->RChild=R->LChild;
				R->LChild=S;
				S->bf=0;
				R->bf=0;
			}
		}
		
		//CASE 2: Double rotation
		else if(R->bf==-1*a){							//if both a and the side to which node is added are different
		total_rotations+=2;								//Updating no. of rotations for each rotation performed
			if(a==1){
				P=R->RChild;
				R->RChild=P->LChild;
				P->LChild=R;
				S->LChild=P->RChild;
				P->RChild=S;
				
														//fixing balance factor for each case
				if(P->bf==1){							//BF changes depending on the current BF of root(P) of rotated subtree as S and R becomes child of P
					S->bf=-1;
					R->bf=0;
				}
				else if(P->bf==0){
					S->bf=0;
					R->bf=0;
				}
				else{
					S->bf=0;
					R->bf=1;
				}
				P->bf=0;
			}
			else if(a==-1){
				P=R->LChild;
				R->LChild=P->RChild;
				P->RChild=R;
				S->RChild=P->LChild;
				P->LChild=S;
				
				//fixing balance factor
				if(P->bf==1){
					S->bf=0;
					R->bf=-1;
				}
				else if(P->bf==0){
					S->bf=0;
					R->bf=0;
				}
				else{
					S->bf=1;
					R->bf=0;
				}
				P->bf=0;
			}
		}
	}
	if(S==T->RChild)								//attaching rotated subtree (with root P) again to T
		T->RChild=P;
	else 
		T->LChild=P;
}
void AVL_Tree::Delete(int item){
	stack<AVL_Node*> st;							//Stack for the path of node to be deleted
	AVL_Node* P=dummy->RChild;
	AVL_Node* D=NULL,*t=NULL;						//D is pointer to node to be deleted
	st.push(dummy);									//Initially stack will contain dummmy node
	
	
	//Searching item
	while(P){
		total_keycomparison++;						//Updating no. of comparisons for each node visit 
		if(item<P->key){
			st.push(P);
			P=P->LChild;
		}
		else if(item>P->key){
			st.push(P);
			P=P->RChild;
		}
		else{										//Found the item to be deleted
			D=P;
			break;
		}
	}

	if(D==NULL){
		return;
	}
	else{
		//CASE 1: Node to be deleted is a leaf Node
		if(D->LChild==NULL && D->RChild==NULL){			
			AVL_Node* ptr=st.top();
			if(ptr==dummy){
				dummy->RChild=NULL;
				delete(D);
				return;
			}		
			if(D->key<ptr->key){										//Making the parent's pointer to D as NULL
				ptr->LChild=NULL;
			}
			else{
				ptr->RChild=NULL;
			}
			delete(D);													//deallocating memory of D
			
		}
		//CASE 2: Node to be deleted has a single child
		else if(D->LChild==NULL || D->RChild==NULL){
			AVL_Node* temp;
			if(D->LChild==NULL){
				temp=D->RChild;
				D->key=D->RChild->key;									//Assigning value of child to D and deleting the child
				D->RChild=NULL;
				D->bf=0;
			}
			else{
				temp=D->LChild;
				D->key=D->LChild->key;
				D->LChild=NULL;
				D->bf=0;
			}
			delete(temp);
		}
		else{
			st.push(D);
			AVL_Node* succ=successor(D->RChild,st);						//Here we will replace the node with successor and then delete successor
			D->key=succ->key;
			item=succ->key;
			AVL_Node* ptr=st.top();
			
			//the successor will either be leaf or parent with single child (property of AVL tree) therefore deleting similar to CASE 1 or CASE 2
			if(succ->LChild==NULL && succ->RChild==NULL){
				if(succ->key<ptr->key){
					ptr->LChild=NULL;
				}
				else{
					ptr->RChild=NULL;
				}
				delete(succ);
			
			}
			else {AVL_Node* temp;
				if(succ->LChild==NULL){
					temp=succ->RChild;
					succ->key=succ->RChild->key;
					succ->RChild=NULL;
					succ->bf=0;
				}
				else{
					temp=succ->LChild;
					succ->key=succ->LChild->key;
					succ->LChild=NULL;
					succ->bf=0;
				}
				delete(temp);
			}
			
		}
		
	//Now balance factor should be fixed for all the nodes that were in path of root to D and D to successor
		auto link=[](int a,AVL_Node *P){
			if(a==1){										//for linking P to it's Lchild or RChild depending on where item is added
				return P->LChild;
			}
			else{
				return P->RChild;
			}
		};
	
		while(st.top()!=dummy){
			total_keycomparison++;									//Updating no. of comparisons for each node visit 
			AVL_Node* ptr=st.top();
			int a=(item<ptr->key)?1:-1;								// a is variable that tells from which side the node is deleted
			st.pop();
			t=st.top();												//For attaching the subtree again after rotation
			
			if(ptr->bf==a){											//Tree has got more balanced
					ptr->bf=0;
					continue;
			}
			else if(ptr->bf==0){									//Tree has got more height and the above tree will remain balanced so Returning
				ptr->bf=-1*a;
				return;
			}
			else{
				
				AVL_Node* R=link(ptr->bf,ptr);
				
				//Here we have same procedure of rebalancing as in insert function
				//CASE 1: Single rotation
				if(R->bf==-1*a){
					total_rotations++;								//Updating no. of rotations for each rotation performed
					if(a==-1){
						P=R;
						ptr->LChild=R->RChild;
						R->RChild=ptr;
						ptr->bf=0;
						R->bf=0;
						}
					else if(a==1){
						P=R;
						ptr->RChild=R->LChild;
						R->LChild=ptr;
						ptr->bf=0;
						R->bf=0;
					}
				}
				//Single rotation
				else if(R->bf==0){				//Edge case for deletion (different from insert) Element is deleted from subtree with 
					total_rotations++;			//Updating no. of rotations for each rotation performed
					if(a==-1){					//root->BF=0 so we need to update its BF.
						P=R;
						ptr->LChild=R->RChild;
						R->RChild=ptr;
						R->bf=a;
						}
					else if(a==1){
						P=R;
						ptr->RChild=R->LChild;
						R->LChild=ptr;
						R->bf=a;
					}
				}
				//CASE 2: Double rotation
				else if(R->bf==a){	
				total_rotations+=2;				//Updating no. of rotations for each rotation performed	
						if(a==-1){
							P=R->RChild;
							R->RChild=P->LChild;
							P->LChild=R;
							ptr->LChild=P->RChild;
							P->RChild=ptr;
							if(P->bf==1){
								ptr->bf=-1;
								R->bf=0;
							}
							else if(P->bf==0){
									ptr->bf=0;
									R->bf=0;
								}
							else{
								ptr->bf=0;
								R->bf=1;
							}
							P->bf=0;
						}
						else if(a==1){
								P=R->LChild;
								R->LChild=P->RChild;
								P->RChild=R;
								ptr->RChild=P->LChild;
								P->LChild=ptr;
								if(P->bf==1){
									ptr->bf=0;
									R->bf=-1;
								}
								else if(P->bf==0){
										ptr->bf=0;
										R->bf=0;
									}
								else{
									ptr->bf=1;
									R->bf=0;
								}
								P->bf=0;
							}
				}
				if(P->bf==-1 || P->bf==1){				//Edge case 2 for deletion (different from insertion)
					if(ptr==t->RChild){ 				//If the root of rotated subtree has same BF as before no need for checking 			
						t->RChild=P;					//above nodes we can return after attaching the subtree
					}
				else{
						t->LChild=P;
					}
					return;								//if root of rotated subtree has BF -1 or +1 we will return as no further rebalancingis required
				}
				
			}
			if(ptr==t->RChild){ 						//attaching the rotated subtree again to t
				t->RChild=P;
			}
			else{
				t->LChild=P;
			}
		
			
		}
	
	}
	
}
AVL_Node* AVL_Tree::successor(AVL_Node* node,stack<AVL_Node*> &st){
	while(node->LChild!=NULL){							//while left child is not null we move on and at last return the node
		st.push(node);
		total_keycomparison++;							//Updating no. of comparisons for each node visit 
		node=node->LChild;
	}
	return node;
}
void AVL_Tree::getOrder(AVL_Node* rt,FILE* fp) {
	
	if(rt == NULL) {													//Returning when root is NULL
		return;
	}
	
	//Printing label as key and balance factor with LChild and RChild pointer
   	fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->key,rt->key,rt->bf);
	if(rt->LChild){
		getOrder(rt->LChild,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->LChild->key,rt->LChild->key,rt->LChild->bf);
		fprintf(fp,"\"%d\":f0->\"%d\":f1;\n",rt->key,rt->LChild->key);
	}
	if(rt->RChild){
		getOrder(rt->RChild,fp);
		fprintf(fp,"%d [label = \"<f0> | <f1> %d | <f2> %d | <f3>\"];\n",rt->RChild->key,rt->RChild->key,rt->RChild->bf);
		fprintf(fp,"\"%d\":f3->\"%d\":f1;\n",rt->key,rt->RChild->key);
	}
	
}

void AVL_Tree::AVL_Print(const char *filename){

	FILE* fp;
	fp=fopen("t.dotgv","w+");
    fprintf(fp,"%s\n","digraph {");
    fprintf(fp,"%s\n","node [shape = record, height=.1]");    
    AVL_Node* pointer=dummy->RChild;
    getOrder(pointer,fp);										//Creating syntax and writing it to t.dotgv file
	
    fprintf(fp,"%s\n", "}");
	fclose(fp);
    string cmd = "dot.exe -Tpng t.dotgv -o"+ string(filename); 		//Syntax to get output in filename 
    system((const char*)cmd.c_str());
    
}

float AVL_Tree::get_Average_height(){
	
	//This function finds sum of heights of all the nodes of the tree and no. of nodes of the tree
	get_Average_height(dummy->RChild);
	
	//to avoid divide by zero
	if(no_of_nodes==0)
	return 0;
	
	//Average height
	return (sum_of_height*1.0/no_of_nodes);
}
void AVL_Tree::get_Average_height(AVL_Node* node){
	
	//performing pre order traversal on tree and summing up all the height that were updated in final_height function 
	if(node==NULL){
		return ;
	}
	get_Average_height(node->LChild);
	sum_of_height+=node->h;
	no_of_nodes++;
	get_Average_height(node->RChild);
}
long long int AVL_Tree::get_total_rotation(){
	
	//Function simply returns the total_rotation variable that was updated during all the operations
	return total_rotations;
}
long long int AVL_Tree::get_total_keycomparison(){
	
	//Function simply returns the total_Keycomparison variable that was updated during all the operations
	return total_keycomparison;
}
long long int AVL_Tree::get_final_height(){
	//Function returns the final height using helper function
	return get_final_height(dummy->RChild);
}
//This final height function will recursively find the height of tree and also update each node's height variable with its height
long long int AVL_Tree::get_final_height(AVL_Node* node){
	
	//if node is NULL returning height 0
	if(node==NULL){
		return 0;
	}
	
	//Taking convention as leaf node has height 0
	if(node->LChild==NULL && node->RChild==NULL){
		node->h=0;
		return 0;
	}
	
	//if single child then adding current node to height and moving to the child
	if(node->LChild==NULL && node->RChild!=NULL){
		
		return node->h=( 1+ get_final_height(node->RChild));
	}
	else
	if(node->LChild!=NULL && node->RChild==NULL){
		
		return node->h=(1+ get_final_height(node->LChild));
	}
	else
	{
		//if both the childs are present then height is taken as the max of two subtree's height
		return node->h=(1+max(get_final_height(node->LChild),get_final_height(node->RChild)));
	}
	
}
long long int AVL_Tree::get_no_of_nodes(){
	return no_of_nodes;
}
