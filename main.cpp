#include <iostream>
#include<array>
#include<bits/stdc++.h>
#include "BST.h"
#include "RST.h"
#include "AVL_Tree.h"
using namespace std;
const char file[]="TestCase.txt";
int operation_count=10000;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
 The code for BST, AVL and RST(Randomised Search Tree) are included has header files. To check their implementation please check the respective files.
*/

int RST_main()
{	cout<<"\nThis is implementation of Treap Data Structure:\n";
	cout<<"----------------------------------------------------------------------------------\n";
	cout<<"The choices for various functions are listed below:\n";
	RST *tree=new RST();

	int flag=1;
		cout<<"-------------------------------------------------\n";
		cout<<"Choices: \n"<<"0: Quit this menu\n"<<"1: Insert\n"<<"2: Search\n"<<"3: Delete\n"<<"4: PrintTree\n"<<"5: Get a Created tree and print it\n";
		cout<<"6: Insert item with priority\n\n";
		char ch;
		do{
			cout<<"Enter your choice of function: \n";
			int c,item,n=0,p=0;
			string name;
			cin>>c;
			switch(c){
				case 0: flag=0;						//To quit this menu and go to previous menu
				 		break;
				case 1: cout<<"Enter the number of item to be inserted into the tree: \n";
						cin>>n;
						cout<<"Enter the item(s) to be inserted: \n";
						while(n-->0){
							cin>>item;
							try{
								tree->Insert(item);	
								cout<<item<<" inserted successfully!\n";
							}
							catch(const char *error){
								cerr << error << "\n";
							}
						}
						cout<<"-------------------------------------------------\n";
						break;
				case 2: cout<<"Enter number of item to be searched in the tree: \n";
						cin>>n;
						cout<<"Enter item(s) to be searched in the tree: \n";
						while(n-->0){
							cin>>item;
							if(tree->Search(item)) cout<<"The element is present in the Tree!"<<"\n";
							else cout<<"Not Found, element is not present in the tree!\n";
						}
						cout<<"-------------------------------------------------\n";
						break;
				case 3: cout<<"Enter number of item to be Deleted from the tree: \n";
						cin>>n;
						cout<<"Enter item(s) to be Deleted from the tree: \n";
						while(n-->0){
							cin>>item;
							try{
								if(tree->Search(item)){
									tree->Delete(item);	
									cout<<item<<" Deleted successfully!\n";
								}
								else{
									cout<<item<<" doesn't exist!\n";
								}
							}
							catch(const char *error){
								cerr << error << "\n";
							}
						}
						cout<<"-------------------------------------------------\n";
						break;
				case 4: cout<<"Enter the output file name: example xyz.png\n";
						cin>>name;
						tree->Print(name.c_str());
						cout<<"If you are a linux user and .png file is not created please convert the .dotgv file to png to view the tree!\n";
						cout<<"-------------------------------------------------\n";
						break;
						
				case 5: try{
							tree->Insert(30);
							tree->Insert(20);
							tree->Insert(39);
							tree->Insert(26);
							tree->Insert(12);
							tree->Insert(78);
							tree->Insert(40);
							tree->Insert(11);
							tree->Insert(17);
							tree->Insert(35);
							tree->Insert(130);
							
						}
						catch(const char *error){
							cerr << error << "\n";
						}
						tree->Print("output.png");
						cout<<"You can view the sample tree in output.png\n";
						cout<<"If you are a linux user and .png file is not created please convert the .dotgv file to png to view the tree!\n";
						cout<<"-------------------------------------------------\n";
						break;
				case 6: //insert item with priority
						cout<<"Enter the number of item to be inserted into the tree: \n";
						cin>>n;
						cout<<"Enter the item and respective priority pairs to be inserted eg. 5 1: \n";
						while(n-->0){
							cin>>item>>p;
							try{
								tree->insert(item,p);	
								cout<<item<<" inserted successfully!\n";
							}
							catch(const char *error){
								cerr << error << "\n";
							}
						}						
						break;
				default: cout<<"You have entered a wrong choice: \n";
			}
	
		}while(flag!=0);
	cout<<"---------------------------------------------------------------------------\n";
	delete tree;					//deallocating tree memory to avoid memory leakage
	
	return 0;
}
bool Perform_operation_on_BST(BST* tree){

	FILE* fp=fopen(file,"r");
	
	//Checking if the file is read properly or not
	if(fp==NULL){
		return 0;
	}
	
	//If the word read from the file is INSERT then performing insert operation else delete operation
	int op=0,item=0;
	char function[7];
	fscanf(fp,"%d",&op);
	for(int i=0;i<op;i++){
		
		//Reading string and storing in "function"
		fscanf(fp,"%s",&function);
		if(strcmp("Insert",function)==0){
			fscanf(fp,"%d",&item);
			tree->Insert(item);
		}
		else{
			fscanf(fp,"%d",&item);
			tree->Delete(item);
		}
	}
	fclose(fp);	
	return 1;
}

bool Perform_operation_on_AVL(AVL_Tree* tree){	
	FILE* fp=fopen(file,"r");
	
	//Checking if the file is read properly or not
	if(fp==NULL){
		return 0;
	}
	
	//If the word read from the file is INSERT then performing insert operation else delete operation
	int op=0,item=0;
	char function[7];
	fscanf(fp,"%d",&op);
	for(int i=0;i<op;i++){	
	
		//Reading string and storing in "function"
		fscanf(fp,"%s",&function);
		if(strcmp("Insert",function)==0){
			fscanf(fp,"%d",&item);
			tree->Insert(item);
		}
		else{
			fscanf(fp,"%d",&item);
			tree->Delete(item);
		}	
	}
	fclose(fp);	
	return 1;
}

bool Perform_operation_on_RST(RST* tree){
	FILE* fp=fopen(file,"r");
	
	//Checking if the file is read properly or not
	if(fp==NULL){
		return 0;
	}
	
	//If the word read from the file is INSERT then performing insert operation else delete operation
	int op=0,item=0;
	char function[7];
	fscanf(fp,"%d",&op);
	for(int i=0;i<op;i++){
		
		//Reading string and storing in "function"
		fscanf(fp,"%s",&function);
		if(strcmp("Insert",function)==0){
			fscanf(fp,"%d",&item);
			tree->Insert(item);
		}
		else{
			fscanf(fp,"%d",&item);
			tree->Delete(item);
		}
	}
	fclose(fp);	
	return 1;
}
void Generate_testCases(int operation_count,int inst,int del){
	
	//inst is insertion count ratio and del is deletion count ratio
	int insertcount=1,deletecount=0;
	
	//open file TestCase.txt in write mode
	FILE* fp=fopen(file,"w");
	int item=0,p=0,op=-1,index=0,count=0;

	//Maintaining array for keeping track of inserted items in treap
	int arr[operation_count]={0};
	
	//Handling file error
	if(fp==NULL){
		cout<<"Error in opening File!\n";
		return;
	}
	
	//Writing the number of operation counts in file
	fprintf(fp,"%d\n",operation_count);
	
	//Generating random item number for insertion
	item=rand()%operation_count+1;;
	
	//Wrting INSERT in file for insert operation
	fprintf(fp,"Insert %d\n",item);
	
	//Updating count of element in array and storing item simultanously
	arr[count++]=item;
	
	//looping till operation count
	for(int i=1;i<operation_count;i++){	
	
		//for percentage of delete and insert	
		op=rand()%10;		
		if(op<inst){
		
			item=rand()%operation_count+1;
			
			//writing it in file Example INSERT 120
			fprintf(fp,"Insert %d\n",item);
			insertcount++;
			arr[count++]=item;
		}
		else{
			if(count==1){
				count*=2;
			}
			
			//count variable constricts the deleted item to be mostly from the elements from tree
			//count/2 is done so that some elements get left in tree after all operations, height of tree doesn't go to 0 in this case
			index=rand()%(count/2);
			item=arr[index];
			fprintf(fp,"Delete %d\n",item);
			deletecount++;
		}
		
	}
	fclose(fp);	
	//cout<<"No. of Insert operations: "<<insertcount<<" No. of Delete operations: "<<deletecount<<endl;
	
}
void Generate_testCases(int operation_count){
	int insertcount=1,deletecount=0;
	
	//open file TestCase.txt in write mode
	FILE* fp=fopen(file,"w");
	int item=0,p=0,op=-1,index=0,count=0;

	//Maintaining array for keeping track of inserted items in treap
	int arr[operation_count]={0};
	
	//Handling file error
	if(fp==NULL){
		cout<<"Error in opening File!\n";
		return;
	}
	
	//Writing the number of operation counts in file
	fprintf(fp,"%d\n",operation_count);
	
	//Generating random item number for insertion
	item=rand()%operation_count+1;;
	
	//Wrting INSERT in file for insert operation
	fprintf(fp,"Insert %d\n",item);
	
	//Updating count of element in array and storing item simultanously
	arr[count++]=item;

	//looping till operation count
	for(int i=1;i<operation_count;i++){
		
		//for percentage of delete and insert 50:50
		op=rand()%2;		
		if(op==0){
		
			item=rand()%operation_count+1;
			
			//writing it in file Example INSERT 120
			fprintf(fp,"Insert %d\n",item);
			insertcount++;
			arr[count++]=item;
		}
		else{
			if(count==1){
				count*=2;
			}
			//count variable constricts the deleted item to be mostly from the elements from tree
			//count/2 is done so that some elements get left in tree after all operations, height of tree doesn't go to 0 in this case
			index=rand()%(count/2);
			item=arr[index];
			fprintf(fp,"Delete %d\n",item);
			deletecount++;
		}
		
	}
	fclose(fp);	
	//cout<<"NO. of Insert operations: "<<insertcount<<" No. of Delete operations: "<<deletecount<<endl;
}

void comparison_generator(){
	int op=0,size=0,flag=0;
	
	//Declaring array that contains various operation count for performinn insert and delete
	int array[]={10,35,50,100,350,500,1200,1500,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,8500,9000,9500,10000};
	cout<<"\n1: Number of operations\n2: Height of BST\n3: Height of AVL\n4: Height of RST\n5: Average height of BST\n";
	cout<<"6: Average Height of AVL\n7: Average Height of RST\n8: Number of comparison BST\n";
	cout<<"9: Number of comparison AVL\n10: Number of comparison RST\n11: Number of rotation AVL\n12: Number of rotation RST\n\n";
	cout<<"The comparison table is as follows!\n\n";
	cout<<"---------------------------------------------------------------------------------------------------------------------\n";
	cout<<"1\t2\t3\t4\t5  \t6  \t7  \t8\t9\t10\t11\t12\t\n";
	cout<<"---------------------------------------------------------------------------------------------------------------------\n";
	
	size=sizeof(array)/sizeof(int);
	for(int i=0;i<size;i++){
		
		//creating objects of each tree class
		RST* rst=new RST();
		BST* bst=new BST();
		AVL_Tree* avl=new AVL_Tree();
		op=array[i];
		
		//Generating test case file for respective operation count "op"
		Generate_testCases(op);
		
		//Performing insert and delete opeation on the three trees using file reading 
		Perform_operation_on_BST(bst);
		Perform_operation_on_RST(rst);
		Perform_operation_on_AVL(avl);
		
		//Displaying results of various parameters
		cout<<op<<"\t";
		cout<<bst->get_final_height()<<"\t";
		cout<<avl->get_final_height()<<"\t";
		cout<<rst->get_final_height()<<"\t";
		cout<<round(bst->get_Average_height()*10000.0)/10000.0<<"\t";
		cout<<round(avl->get_Average_height()*10000.0)/10000.0<<"\t";
		cout<<round(rst->get_Average_height()*10000.0)/10000.0<<"\t";
		cout<<bst->get_total_keycomparison()<<"\t";
		cout<<avl->get_total_keycomparison()<<"\t";
		cout<<rst->get_total_keycomparison()<<"\t";
		cout<<avl->get_total_rotation()<<"\t";
		cout<<rst->get_total_rotation()<<"\t";
		//cout<<bst->get_no_of_nodes()<<"\t";
		//cout<<avl->get_no_of_nodes()<<"\t";
		//cout<<rst->get_no_of_nodes()<<"\t";
		cout<<endl;
		
		//Deallocating memory to avoid memory leakage
		delete(rst);
		delete(bst);
		delete(avl);
	}
	
}
int main(int argc, char** argv) {
		srand(time(0));
		cout<<"This is DS Assignment number 3 (214101056)\n";
		cout<<"-----------------------------------------------------------\n";
		cout<<"NOTE: RST refers to treap\n\n";
		cout<<"Please choose among the following operation\n";
		cout<<"1: Go to implementation of Treap data structure.\n";
		cout<<"2: Do comparison between RST, BST and AVL Tree.\n";
		cout<<"3: Get Automatically generated comparison table of three.\n\n";
		cout<<"To use your own Test Case file choose option 2.\n";
		cout<<"-----------------------------------------------------------\n";
		char ch;		
		do{
			cout<<"Enter your choice of function:\n";
			int c;
			cin>>c;			
			switch(c){				
				case 1://create treap object
						RST_main();						
				break;				
				case 2://Menu to compare various operations on the three trees 
						cout<<"\n---------------------Perform Operations------------------------------\n";
						cout<<"1: Generate test case file";
						cout<<" (To use your own testcase file simply copy and paste the test case \nvalues into TestCase.txt file and perform any of the below operation)\n";
						cout<<"Also, make sure that the test case file follows the same convention as this assignment has.\n";
						cout<<"2: Run operations on BST\n";
						cout<<"3: Run operations on AVL Tree\n";
						cout<<"4: Run operations on Treaps(RST)\n";
						cout<<"5: Quit this menu\n";
						char choice;
						do{
							cout<<"Enter your choice: \n";
							int num,ex=0,flag=0,r1=0,r2=0;
							char r;
							RST* rst;
							BST* bst;
							AVL_Tree* avl;
							cin>>num;
							switch(num){
								case 1:	cout<<"Enter the number of operations you want to perform(e.g. 10000)\n";
										cin>>operation_count;
										cout<<"Do you want user defined ratio for nunber of insert and delete operation?(Y/N)\n";
										cin>>r;
										if(r=='Y'||r=='y'){
											while(r1+r2!=10){
												cout<<"Enter the ratio (e.g. 7 3, meaning 70% insert and 30% delete)\n";
												cin>>r1>>r2;
												if(r1+r2!=10){
													cout<<"Please enter valid ratio!\n";												
												}												
												else{
													Generate_testCases(operation_count,r1,r2);
								 					cout<<"Test case generated successfully, to check please open TestCase.txt\n";
												}
											}										
											   
										}
										else{
											Generate_testCases(operation_count);											
								 			cout<<"Test case generated successfully, to check please open TestCase.txt\n";
										}								 		
										break;
								case 2: bst=new BST();
										flag=Perform_operation_on_BST(bst);
										if(flag==1){
											bst->printTree("BST.png");
											cout<<"Performed operations successfully! You can view the resulting tree in BST.png\n\n";
											cout<<"The number of key comparisons: "<<bst->get_total_keycomparison()<<endl;
											cout<<"The number of total rotations: "<<bst->get_total_rotation()<<", As we do no perform any rotations in BST"<<endl;
											cout<<"The final height of tree is: "<<bst->get_final_height()<<endl;
											cout<<"The Average height of nodes is: "<<bst->get_Average_height()<<endl;
											cout<<endl;
										}
										else{
											cout<<"Error in opening file!\n";
										}											
										delete(bst);
										break;
								case 3: avl=new AVL_Tree();
										flag=Perform_operation_on_AVL(avl);
										if(flag==1){
											avl->AVL_Print("AVL.png");
											cout<<"Performed operations successfully! You can view the resulting tree in AVL.png\n\n";
											cout<<"The number of key comparisons: "<<avl->get_total_keycomparison()<<endl;
											cout<<"The number of total rotations: "<<avl->get_total_rotation()<<endl;
											cout<<"The final height of tree is: "<<avl->get_final_height()<<endl;
											cout<<"The Average height of nodes is: "<<avl->get_Average_height()<<endl;											
										}
										else{
											cout<<"Error in opening file!\n";
										}
										delete(avl);
										break;
								case 4: rst=new RST();
										flag=Perform_operation_on_RST(rst);
										if(flag==1){
											rst->Print("RST.png");
											cout<<"Performed operations successfully! You can view the resulting tree in RST.png\n\n";
											cout<<"The number of key comparisons: "<<rst->get_total_keycomparison()<<endl;
											cout<<"The number of total rotations: "<<rst->get_total_rotation()<<endl;
											cout<<"The final height of tree is: "<<rst->get_final_height()<<endl;
											cout<<"The Average height of nodes is: "<<rst->get_Average_height()<<endl;	
										}
										else{
											cout<<"Error in opening file!\n";
										}
										delete(rst);
										break;
								case 5: ex=5;
										break;
								default: cout<<"You have entered a wrong choice!\n";
							}
							if(ex==5)
								break;
						
						}while(true);
						break;			
				case 3: //generating automator of comparison between three trees.
						comparison_generator();
						break;
			
				default: cout<<"You have entered a wrong choice! \n";
			}
		cout<<"Do you want to continue with comparison or treap operation?(Y/N)?\n";
		cin>>ch;
		}while(ch=='Y'||ch=='y');
	return 0;
}

