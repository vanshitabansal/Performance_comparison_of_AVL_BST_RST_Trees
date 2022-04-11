#ifndef AVL_TREE_H
#define AVL_TREE_H


#include <iostream>
#include<limits.h>
#include<bits/stdc++.h>
using namespace std;
//AvL tree class definiton
//Structure of AVL tree
/*
			dummy    (helpful in case of rotation at root of tree)
		   /    \
		  /      \
		 NULL    original tree
									 */
class AVL_Node{
	private:
		int key;
		int bf;				//balance factor bf=height(left subtree)-height(right subtree)
		int h;
		AVL_Node * LChild,*RChild;
		
	public: 
		AVL_Node(){
		
		}
		AVL_Node(int item){
			key=item;
			LChild=NULL;
			RChild=NULL;
			bf=0;
		}
		~AVL_Node(){
			delete(LChild);
			delete(RChild);
		}

	friend class AVL_Tree;
	
};
class AVL_Tree{
	private:
		AVL_Node* dummy;
		
		//used for various parameter calculations
		long long int total_rotations,total_keycomparison,height,no_of_nodes,sum_of_height;
		float avg_ht;
		
		//Functions used while performing below operations
		void getOrder(AVL_Node* ,FILE* );									//Helper function for printing tree
		AVL_Node* successor(AVL_Node*,stack<AVL_Node*>&);					//Function to find successor of a node
		AVL_Node* AVL_copy(AVL_Node*);
		long long int get_final_height(AVL_Node*);
		void get_Average_height(AVL_Node*);
		
	public: 
		
		AVL_Tree(){
			dummy=new AVL_Node();											//dummy node is the head and root of the AVL tree is stored in its right child
			dummy->LChild=NULL;
			dummy->RChild=NULL;
			total_rotations=0;
			total_keycomparison=0;
			height=0;
			avg_ht=0;
			sum_of_height=0;
			no_of_nodes=0;
		}
		AVL_Tree(const AVL_Tree &); 
		AVL_Tree &operator=(const AVL_Tree &); 
		void Insert(int); 
		void Delete(int); 
		bool AVL_Search(int); 
		void AVL_Print(const char*); 
		long long int get_total_rotation();
		long long int get_total_keycomparison();
		float get_Average_height();
		long long int get_final_height();
		long long int get_no_of_nodes();
		~AVL_Tree(){
			delete(dummy);
		} 
};
#endif
