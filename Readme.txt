
Note: RST means Randomised search Tree which is TREAP. So, wherever you see RST it refers to treap. 


SYSTEM REQUIREMENTS:

	Install graphviz, cmake(3.20+), make(4.0+) in the system if not, present.


Check if the following files are present:
1. main.cpp
2. AVL.cpp
3 BST.cpp
4. RST.cpp
2. CMakeLists.txt


1) Instructions to run the code:
-----------------------------------
	1. Windows(To run on command prompt)

		1. Create a build directory.
		2. Open terminal and type following commands:
			 cd build
			 cmake ..
			 make
		3. Run the executable file created in build directory.
		4. Check the output files in build directory. 

	2. Windows(Devcpp)

		1. In devcpp, go to File->Open->double click the "Assignment-3.dev" devcpp project.
		2. Compile and run using shortcut F11 or go to Execute->Compile & run.

		If you face any compile time error due to older version of gcc, do the following:

		1. Make sure that -std=c++11 is added in, while compiler is called and language standard is ISO C++ 11.
		2. How to do this:  tools->compiler options-> add the following command when calling compiler --std=c++11 
		and settings->code Generation->language standard->ISO C++ 11.


	3.Linux

		1. If in linux, cmake can't be used, 
		    please use the following command to compile:

			g++ AVL_Tree.cpp BST.cpp RST.cpp main.cpp

		2.  Use ./a.out to run the program.


2) To run your own test case file:
----------------------------------------

	1. Make sure that the convention for writing the test case is same as that of TestCase.txt which is present in the folder of project or  if you run on command 		prompt, gets generated in build directory.
	2. Save your text file with name "TestCase.txt". 
	3. Choose from menu option 2 which says compare the three tree. Then, using the next menu you can perform operation on any tree.

3) User manual Guide:
----------------------------
	Please choose among the following operation
	1: Go to implementation of Treap data structure:
		This is for checking Treap implementation and gives following submenu:
		
			Choices:
			0: Quit this menu
			1: Insert
			2: Search
			3: Delete
			4: PrintTree
			5: Get a Created tree and print it
			6: Insert item with priority

	2: Do comparison between RST, BST and AVL Tree.
		This is used to create or use a Test Case file and perform operation on AVL,BST,RST(Treap) individually to generate parameters and gives following submenu. You can see the correspoding tree image generated as output.

			---------------------Perform Operations------------------------------
			1: Generate test case file (To use your own testcase file simply copy and paste the test case
			values into TestCase.txt file and perform any of the below operation)
			Also, make sure that the test case file follows the same convention as this assignment has.
			2: Run operations on BST
			3: Run operations on AVL Tree
			4: Run operations on Treaps(RST)
			5: Quit this menu

	3: Get Automatically generated comparison table of three.
			This option creates a table corresponding to various test case file and the parameters calculated for all the three trees in a single table by just pressing 3. The columns are named 1 to 12 and there respective meaning are displayed just above the table.

	
4) Flow of the project:
---------------------------

	1. There is a main.cpp file containing the code for Generating test cases, Menus for:  Treap implementation, Comparing three trees and automatically generating 	table for comparison.
	2. There is a RST.cpp and RST.h that have definition and declaration for Treap.
	3. There is a AVL_Tree.cpp and AVL_Tree.h that have definition and declaration for AVL.
	4. There is a BST.cpp and BST.h that have definition and declaration for BST.






