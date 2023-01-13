//------------------------------------------------------------------------------------------------------
// Name: Sudheer Daniel Meghavaram
// Project Name: Project4.cpp
// 
//----------------------------------------------------------






#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define COUNT 10

class AVLTreeNode           //Class Declaration
{
    public:
        int key, height;
        string value;
        AVLTreeNode *left, *right, *parent;

        AVLTreeNode();                            // Methods Declaration.
        AVLTreeNode(int key, string value);
        AVLTreeNode(int key, string value, int height, AVLTreeNode* left, AVLTreeNode* right, AVLTreeNode* parent);
};

class AVLTree
{
    private:
        int size;
        AVLTreeNode   *root;

    public:
        AVLTree();            // Constructor
        AVLTree(AVLTree& rhs);
        ~AVLTree();           // Destructor
        void ClearTree(AVLTreeNode *n);
        int getHeight();
        int getSize();
        AVLTreeNode* getRoot();
        int max(int a, int b);
        int getHeightDif(AVLTreeNode *n);
        bool insert(int key, string value);
        bool find(int key, string& value);
        vector<string> findRange(int lowkey, int highkey);
        void insertAllInRange(AVLTreeNode *n, int lowkey, int highkey, vector<string>& vect);
        AVLTreeNode* newNode(int key, string value);
        AVLTreeNode* rotateLeft(AVLTreeNode *n);
        AVLTreeNode* rotateRight(AVLTreeNode *n);
        friend ostream& operator<<(ostream& os, AVLTree& me);
        void printInOrder(ostream& os, AVLTreeNode *n, int space);
        AVLTreeNode* copyNodes(AVLTreeNode *n);
        AVLTree& operator=(AVLTree& rhs);
};
