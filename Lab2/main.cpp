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
        void DeleteItem(const char*);
        void RetrieveItem(const char*,bool& found);
        void PrintTree();
        
    private:
        TreeNode* root;
        
		void Destroy(TreeNode*&);
		void Insert(TreeNode*&,ItemType);
		void Retrieve(TreeNode* tree, const char* item, bool& found);
		void Delete(TreeNode*&, const char*);
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
    else if(strcmp(item.ContactName, tree->info.ContactName) == -1)
    	Insert(tree->left, item);
    else
    	Insert(tree->right, item);
}

void TreeType::RetrieveItem(const char* item, bool& found)
{
	Retrieve(root, item, found);
}

void TreeType::Retrieve(TreeNode* tree, const char* name, bool& found)
{
	if(tree == NULL)
		found = false;
	else if(strcmp(name, tree->info.ContactName) == -1)
		Retrieve(tree->left, name, found);
	else if(strcmp(name, tree->info.ContactName) == 1)
		Retrieve(tree->right, name, found);
	else
		found = true;
}

void TreeType::DeleteItem(const char* name)
{
	//cout<<endl<<"deleteitem: "<<name<<endl;
	Delete(root, name);
}

void TreeType::Delete(TreeNode*& tree, const char* name)
{
	if(tree != NULL)
	{
		//cout<<endl<<"delete: "<<name<<endl;
		if(strcmp(name, tree->info.ContactName) == 0)
		{
			if(tree->left == NULL && tree->right == NULL)
			{
				//cout<<"case1"<<"\n";
				tree = NULL;
			}
			else if(tree->left != NULL && tree->right == NULL)
			{
				//cout<<"case2 takeLEFT"<<"\n";
				tree = tree->left;
			}
			else if(tree->left == NULL && tree->right != NULL)
			{
				//cout<<"case2 takeRIGHT"<<"\n";
				tree = tree->right;
			}
			else
			{
				//cout<<"case3"<<"\n";
				TreeNode* least = tree;
				ItemType val;
				least = tree->right;
				while(least->left != NULL)
					least = least->left;
				val = least->info;
				tree->info = val;
				Delete(tree->right, val.ContactName);
			}
		}
		else if(strcmp(name, tree->info.ContactName) == -1)
			Delete(tree->left, name);
		else if(strcmp(name, tree->info.ContactName) == 1)
			Delete(tree->right, name);
	}
}

void TreeType::PrintTree()
{
	cout<<left<<setw(20)<<setfill(' ')<<"ContactName"
		<<left<<setw(20)<<setfill(' ')<<"PhoneNumber"
		<<left<<setw(20)<<setfill(' ')<<"EmailAddress"<<endl;
	Print(root);
}

void TreeType::Print(TreeNode* tree)
{
    if (tree != NULL)
    {
		Print(tree->left);
		cout<<left<<setw(20)<<setfill(' ')<<tree->info.ContactName
			<<left<<setw(20)<<setfill(' ')<<tree->info.PhoneNo
			<<left<<setw(20)<<setfill(' ')<<tree->info.EmailAddress<<endl;
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
				std::cout<<"DeleteCmd detected"<<"\n\n";
				char theName[20];
				cout<<"ContactName: ";
				cin>>theName;
				myTree.DeleteItem(theName);
				break;
			case cmd_RetrieveItem:
				std::cout<<"RetrieveCmd detected"<<"\n";
				char theName2[20];
				cout<<"ContactName: ";
				cin>>theName2;
				bool itemFound;
				myTree.RetrieveItem(theName2, itemFound);
				if(itemFound)
					std::cout<<"item '" << theName2 << "' is found."<<"\n";
				else
					std::cout<<"item '" << theName2 << "' is NOT found."<<"\n";
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
	std::cout<<"0  Exit\n";
}



