#ifndef RST_H
#define RST_H

#include <iostream>
#include<limits.h>
#include<bits/stdc++.h>
using namespace std;

/*
Implement dictionary ADT (Abstract Data Type) using treap by taking random priority. You need to 
implement at least insert, delete, and search. Build an interactive user interface that performs insertion, 
deletion, searching and printing.
Compare the performance of treap with BST (Binary Search Tree) and AVL tree. For performance 
evaluation, perform several insertion and deletion in interleaved fashion. You should generate testcases
into a file. Your program must read testcase file to generate several parameters such as total no of key 
comparison during insertion and deletion, height of the final tree, average height of each element in the 
final tree, total number of rotations (double rotation in AVL tree can be counted as 2 single rotations)
etc.
Generate several testcase files by varying the total number of operations and compare them using 
graphs/charts/tables. Also compare between theoretical and empirical results. You may use additional 
parameters of your choice that help in result analysis
*/

//RST class definition
class TreapNode{
	private:
		int key;
		int priority;				//Randomly generated
		int h;						//stores height of node
		TreapNode * left,*right;
		
	public: 
		TreapNode();				//Default constructor
		TreapNode(int item);		//Parameterised constructor
		TreapNode(int item,int p);  //Parameterised constructor with user defined priority
		~TreapNode(){
		
		}

	friend class RST;
	
};
class RST{
	private:
		TreapNode* root;
		
		//used for various parameter calculations
		long long int total_rotations,total_keycomparison,height,no_of_nodes,sum_of_height;
		float avg_ht;
		
		//Functions used while performing below operations
		void getOrder(TreapNode* ,FILE* );					//Helper function for printing tree
		TreapNode* RST_copy(TreapNode*);
		TreapNode* insert(TreapNode*,int,int);
		TreapNode* Delete(TreapNode*,int);
		TreapNode* fix_priority(TreapNode*); 				//function to maintain heap property
		long long int get_final_height(TreapNode*);
		void get_Average_height(TreapNode*);
		void clear(TreapNode*);
	public: 
		RST(){
			root=NULL;
			
			//initialising all the variables with 0 to avoid garbage values
			total_rotations=0;
			total_keycomparison=0;
			height=0;
			avg_ht=0;
			sum_of_height=0;
			no_of_nodes=0;
		}
		RST(const RST &); 
		RST &operator=(const RST &); 
		void Insert(int); 
		void insert(int,int); 
		void Delete(int); 
		bool Search(int); 
		void Print(const char*); 
		
		//Functions to perform parameter calculation
		long long int get_total_rotation();
		long long int get_total_keycomparison();
		float get_Average_height();
		long long int get_final_height();
		long long int get_no_of_nodes();
		~RST();
};

#endif
