#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef char ItemType;
struct TreeNode
{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
};

class TreeType
{
    public:
        TreeType();
        ~TreeType();

		bool IsEmpty()const;
		//int NumberOfNodes()const;
        void InsertItem(ItemType);
        void DeleteItem(ItemType);
        void RetrieveItem(ItemType&,bool& found);
        void PrintTree();
        
    private:
        TreeNode* root;
        
		void Destroy(TreeNode*&);
		void Insert(TreeNode*&,ItemType);
		void Retrieve(TreeNode* tree, ItemType& item, bool& found);
		//delete
		void Print(TreeNode* tree);
};

TreeType::TreeType()
{
   root = NULL;
}

TreeType::~TreeType()
{
	Destroy(root);
}

void TreeType::Destroy(TreeNode*& tree)
{
    if(tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}

bool TreeType::IsEmpty() const
{
	if(root == NULL)
		return true;
	else
		return false;
}

void TreeType::InsertItem(ItemType item)
{
	Insert(root, item);
}

void TreeType::Insert(TreeNode*& tree, ItemType item)
{
    if (tree == NULL)
    { // base case
    	tree = new TreeNode;
    	tree->right = NULL;
	    tree->left = NULL;
		tree->info = item;
    	//std::cout<<ID<<item<<"\n";
    }
    else if (item < tree->info)
    	Insert(tree->left, item);
    else
    	Insert(tree->right, item);
}

void TreeType::RetrieveItem(ItemType& item, bool& found)
{
	Retrieve(root, item, found);
}

void TreeType::Retrieve(TreeNode* tree, ItemType& item, bool& found)
{
	if(tree == NULL)
		found = false;
	else if(item < tree->info)
		Retrieve(tree->left, item, found);
	else if(item > tree->info)
		Retrieve(tree->right, item, found);
	else
		found = true;
}

//TODO: deleteItem

void TreeType::PrintTree()
{
	Print(root);
}

void TreeType::Print(TreeNode* tree)
{
    if (tree != NULL)
    {
		//std::cout<<"L";
		Print(tree->left);
		std::cout<<tree->info;
		//std::cout<<"R";
		Print(tree->right);
    }
}


//******************
//** Main Program **
//******************

//constant command numbers
const int cmd_ERROR = -1;
const int cmd_Exit = 0;
const int cmd_InsertItem = 1;
const int cmd_DeleteItem = 2;
const int cmd_RetrieveItem = 3;
const int cmd_IsEmpty = 4;
const int cmd_PrintTree = 5;
const int cmd_Help = 6;

void PrintIntro();
int ParseCommand(const char* args, char* outCmd, char* outVal);
int NumerizeCommand(char cmdString[]);
void ClearChar(char* args);

int main()
{
	PrintIntro();
	
    TreeType myTree;
	int asd = 0;
	char myinput[100];
	char myParam[100];
	char cmdString[100];
	int retInt;
	do
	{
		//clean up the variables
		ClearChar(cmdString);
		ClearChar(myParam);
		
		std::cout<<"\n>>";
		std::cin>>myinput;
		retInt = ParseCommand(myinput, cmdString, myParam);
		std::cout<<"Parsed: "<<cmdString<<"\n";
		if (retInt > 0)
		{//must verify that myParam is single character
			std::cout<<"Value: "<<myParam<<"\n";
		}
		
		retInt = NumerizeCommand(cmdString);
		switch(retInt)
		{
			case cmd_Exit:
				break;
			case cmd_InsertItem:
				std::cout<<"InsertCmd detected"<<"\n";
				myTree.InsertItem(myParam[0]);
				break;
			case cmd_DeleteItem:
				std::cout<<"DeleteCmd detected"<<"\n";
				break;
			case cmd_RetrieveItem:
				std::cout<<"RetrieveCmd detected"<<"\n";
				bool itemFound;
				myTree.RetrieveItem(myParam[0], itemFound);
				if(itemFound)
					std::cout<<"item '" << myParam[0] << "' is found."<<"\n";
				else
					std::cout<<"item '" << myParam[0] << "' is NOT found."<<"\n";
				break;
			case cmd_IsEmpty:
				std::cout<<"IsEmptyCmd detected"<<"\n";
				bool isEmpty;
				isEmpty = myTree.IsEmpty();
				if(isEmpty)
					std::cout<<"The tree is EMPTY."<<"\n";
				else
					std::cout<<"The tree is NOT EMPTY."<<"\n";
				break;
			case cmd_PrintTree:
				std::cout<<"PrintTreeCmd detected"<<"\n";
				myTree.PrintTree();
				break;
			case cmd_Help:
				PrintIntro();
				break;
			default:
				std::cout<<"unknown command"<<"\n";
				break;
		}
		
		std::cout<<"\n";
	}while(strcmp(myinput, "exit") != 0);
	
    return 0;
}

void PrintIntro()
{
	std::cout<<"=-=-=-=-= LAB1 - BinarySearchTree =-=-=-=-=\n";
	std::cout<<"                                 \n";
	std::cout<<"  InsertItem -> -insert(value)\n";
	std::cout<<"  DeleteItem -> -delete(value)\n";
	std::cout<<"  RetrieveItem -> -get(value)\n";
	std::cout<<"  IsEmpty -> -empty\n";
	std::cout<<"  PrintTree -> -print\n";
	std::cout<<"                                 \n";
	std::cout<<"  Help -> -help\n";
	std::cout<<"  Exit -> exit\n";
	std::cout<<"                                 \n";
}

int ParseCommand(const char* args, char* outCmd, char* outVal)
{
	while(*args != '\0' && *args != '(')
	{
		*outCmd = *args;
		++args;
		++outCmd;
	}
	if (*args == '\0')
	{
		return 0;
	}
	++args;
	while(*args != '\0' && *args != ')')
	{
		*outVal = *args;
		++args;
		++outVal;
	}
	return 1;
}

int NumerizeCommand(char cmdString[])
{
	if(strcmp(cmdString, "exit") == 0)
		return cmd_Exit;
	else if(strcmp(cmdString, "-insert") == 0)
		return cmd_InsertItem;
	else if(strcmp(cmdString, "-delete") == 0)
		return cmd_DeleteItem;
	else if(strcmp(cmdString, "-get") == 0)
		return cmd_RetrieveItem;
	else if(strcmp(cmdString, "-empty") == 0)
		return cmd_IsEmpty;
	else if(strcmp(cmdString, "-print") == 0)
		return cmd_PrintTree;
	else if(strcmp(cmdString, "-help") == 0)
		return cmd_Help;
	else
		return cmd_ERROR;
}

void ClearChar(char* args)
{
	char* begin = args;
	char* end = begin + sizeof(args);
	std::fill(begin, end, 0);
}










