#ifndef BST_H
#define BST_H

#include <iostream>
#include<limits.h>
#include<bits/stdc++.h>
using namespace std;
//Normal BST class definition
class BstNode{
	//structure for node of BST
	private:
		int value;				//key value
		int h;					//stores height of the node
		BstNode * left,*right;  //left and right child pointers
		
	public: 
		BstNode();
		BstNode(int item);
		~BstNode(){
		
		}

	friend class BST;
	
};

class BST{
	//structure for BST
	private:
		BstNode* root;
		//used for various parameter calculations
		long long int total_rotations,total_keycomparison,height,no_of_nodes,sum_of_height;
		float avg_ht;
		
		//Functions used while performing below operations
		long long int get_final_height(BstNode*);
		void get_Average_height(BstNode*);
		BstNode* insert(BstNode*,int);											//Function for inserting an element
		BstNode* search(int,BstNode*);											//Function for searching an element
		BstNode* delete_(int item,BstNode*);									//Function for deleting an element
		void getOrder(BstNode*, FILE*);			
		BstNode* right_most(BstNode*);
		BstNode* left_most(BstNode*);
		void clear(BstNode*);
	public:		
		BST(){																	//This is the Default Constructor
			root=NULL;
			total_rotations=0;
			total_keycomparison=0;
			height=0;
			avg_ht=0;
			sum_of_height=0;
			no_of_nodes=0;
		};															
		void Insert(int);
		void Delete(int);
		bool Search(int);							
		void printTree(const char*);		
		long long int get_total_rotation();
		long long int get_total_keycomparison();
		float get_Average_height();
		long long int get_final_height();	
		long long int get_no_of_nodes();
		//Destructor
		~BST();
		
};
#endif
