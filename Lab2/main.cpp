#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iomanip>

using namespace std;

struct contact
{
	char ContactName[20];
	char PhoneNo[20];
	char EmailAddress[20];
};

typedef contact ItemType;
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
		void Delete(TreeNode*&, ItemType);
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
    {
    	tree = new TreeNode;
    	tree->right = NULL;
	    tree->left = NULL;
		tree->info = item;
    }
    else if (item.ContactName < tree->info.ContactName)
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
	else if(item.ContactName < tree->info.ContactName)
		Retrieve(tree->left, item, found);
	else if(item.ContactName > tree->info.ContactName)
		Retrieve(tree->right, item, found);
	else
		found = true;
}

//TODO: deleteItem
void TreeType::DeleteItem(ItemType item)
{
	Delete(root, item);
}

void TreeType::Delete(TreeNode*& tree, ItemType item)
{
	if(tree != NULL)
	{
		if(tree->info.ContactName == item.ContactName)
		{
			if(tree->left == NULL && tree->right == NULL)
			{
				//std::cout<<"case1"<<"\n";
				tree = NULL;
			}
			else if(tree->left != NULL && tree->right == NULL)
			{
				//std::cout<<"case2 takeLEFT"<<"\n";
				tree = tree->left;
			}
			else if(tree->left == NULL && tree->right != NULL)
			{
				//std::cout<<"case2 takeRIGHT"<<"\n";
				tree = tree->right;
			}
			else
			{
				//std::cout<<"case3"<<"\n";
				TreeNode* least = tree;
				ItemType val;
				least = tree->right;
				while(least->left != NULL)
					least = least->left;
				val = least->info;
				tree->info = val;
				Delete(tree->right, val);
			}
		}
		else if(item.ContactName < tree->info.ContactName)
			Delete(tree->left, item);
		else if(item.ContactName > tree->info.ContactName)
			Delete(tree->right, item);
	}
}

void TreeType::PrintTree()
{
	std::cout<<std::setw(20)<<"ContactName"<<std::setw(20)<<"PhoneNumber"<<std::setw(20)<<"EmailAddress\n";
	Print(root);
}

void TreeType::Print(TreeNode* tree)
{
    if (tree != NULL)
    {
		Print(tree->left);
		std::cout<<std::setw(20)<<tree->info.ContactName<<std::setw(20)<<tree->info.PhoneNo<<std::setw(20)<<tree->info.EmailAddress<<std::endl;
		Print(tree->right);
    }
}


//******************
//** Main Program **
//******************

//constant command numbers
const char cmd_Exit = '0';
const char cmd_InsertItem = '1';
const char cmd_DeleteItem = '2';
const char cmd_RetrieveItem = '3';
const char cmd_IsEmpty = '4';
const char cmd_PrintTree = '5';
const char cmd_Help = '6';

void PrintIntro();

int main()
{
	TreeType myTree;
	bool cont = true;
	
	do
	{
		system("cls");
		PrintIntro();
		
		std::cout<<"\n>>";
		char x = getch();
		
		switch(x)
		{
			case cmd_Exit:
				cont = false;
				break;
			case cmd_InsertItem:
				cout<<"InsertCmd detected"<<"\n\n";
				ItemType newContact;
				cout<<"ContactName: ";
				cin>>newContact.ContactName;
				cout<<"Phone Number: ";
				cin>>newContact.PhoneNo;
				cout<<"EmailAddress: ";
				cin>>newContact.EmailAddress;
				myTree.InsertItem(newContact);
				break;
			case cmd_DeleteItem:
				std::cout<<"DeleteCmd detected"<<"\n";
				//myTree.DeleteItem(myParam[0]);
				break;
			case cmd_RetrieveItem:
				std::cout<<"RetrieveCmd detected"<<"\n";
				bool itemFound;
				//myTree.RetrieveItem(myParam[0], itemFound);
				/*if(itemFound)
					std::cout<<"item '" << myParam[0] << "' is found."<<"\n";
				else
					std::cout<<"item '" << myParam[0] << "' is NOT found."<<"\n";*/
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
				std::cout<<"PrintTreeCmd detected"<<"\n\n";
				myTree.PrintTree();
				break;
			case cmd_Help:
				PrintIntro();
				break;
			default:
				std::cout<<"unknown command"<<"\n";
				break;
		}
		
		std::cout<<"\n\nPress any key to continue...\n";
		getch();
	}while(cont);
	
    return 0;
}

void PrintIntro()
{
	std::cout<<"=-=-=-=-= LAB2 - Information System For Car Selling Company =-=-=-=-=\n";
	std::cout<<"Select the number of the operation you want to perform\n";
	std::cout<<"1  InsertItem\n";
	std::cout<<"2  DeleteItem\n";
	std::cout<<"3  RetrieveItem\n";
	std::cout<<"4  IsEmpty\n";
	std::cout<<"5  PrintTree\n";
	std::cout<<"6  Help\n";
	std::cout<<"0  Exit\n";
}





