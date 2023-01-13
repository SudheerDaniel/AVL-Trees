//---------------------------------------------------------
// Name: Sudheer Daniel Meghavaram
// Project Name: Project4.cpp
// Here we have intialized an AVLTreeNode() to create a tree and we have given some variables key and value and after the we have added some more variables such as
// height and also given two pointers such as left and right, to insert new elements into the tree, so finally we need to use the recursion method to create the  AVL Tree 
//----------------------------------------------------------





#include "AVLTree.h"
using namespace std;

AVLTreeNode::AVLTreeNode()
{
   this->height = 0;
   this->key = -1;
   this->parent = NULL;
   this->left = NULL;
   this->right = NULL;
}

AVLTreeNode::AVLTreeNode(int key, string value)
{
   this->height = 0;
   this->key = key;
   this->value = value;
   this->parent = NULL;
   this->left = NULL;
   this->right = NULL;
}

AVLTreeNode::AVLTreeNode(int key, string value, int height, AVLTreeNode* left, AVLTreeNode* right, AVLTreeNode* parent)
{
   this->height = height;
   this->key = key;
   this->value = value;
   this->parent = parent;
   this->left = left;
   this->right = right;
}

AVLTree::AVLTree()
{
   this->root = NULL;
   this->size = 0;
}

AVLTree::AVLTree(AVLTree& rhs)
{
   root = copyNodes(rhs.getRoot());
}

AVLTree::~AVLTree()
{
    ClearTree(root);
}

AVLTree& AVLTree::operator=(AVLTree& rhs)
{
   ClearTree(root);
   root = copyNodes(rhs.getRoot());
   return *this;
}

AVLTreeNode* AVLTree::copyNodes(AVLTreeNode* node)
{
   if(node != NULL)
   {
      AVLTreeNode* left = copyNodes(node->left);
      AVLTreeNode* right = copyNodes(node->right);
      AVLTreeNode* parent = copyNodes(node->parent);
      return new AVLTreeNode(node->key, node->value, node->height, left, right, parent);  
   }
   else
      return NULL;
}

void AVLTree::ClearTree(AVLTreeNode *n)
{
   if(n != NULL)
   {
      ClearTree(n->left);
      ClearTree(n->right);
      delete n;
   }
}

int AVLTree::getSize()
{
   return this->size;
}

int AVLTree::getHeight()
{
    if (root == NULL)
        return 0;
    return root->height;
}

int AVLTree::max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int AVLTree::getHeightDif(AVLTreeNode *e)
{
	if(e == NULL)
		return 0;
	else if( e->left == NULL && e->right == NULL)
		return 0;
	else if(e->left == NULL)
		return (-1-(e->right->height));
	else if(e->right == NULL)
		return (e->left->height+1);
	else
		return (e->left->height - e->right->height);
}

AVLTreeNode*  AVLTree::getRoot()
{
	return this->root;
}

AVLTreeNode* AVLTree::newNode(int key, string value)
{
	AVLTreeNode *ptr = new AVLTreeNode(key, value);
	return ptr;
}

AVLTreeNode* AVLTree::rotateRight(AVLTreeNode* y)
{
	AVLTreeNode *x = y->left; 
	AVLTreeNode *T2 = x->right; 

   x->right = y; 
   y->left = T2;
	if(T2!=NULL)
		T2->parent = y;
	y->parent = x;
  
	if(y->left != NULL && y->right != NULL)
			y->height = 1 + max(y->left->height, y->right->height);
	else if(y->left != NULL)
			y->height = 1 + y->left->height;
	else if(y->right !=NULL)
			y->height = 1 + y->right->height;
	else
			y->height = 0;
   if(x->left != NULL && x->right != NULL)
			x->height = 1 + max(x->left->height, x->right->height);
	else if(x->left != NULL)
			x->height = 1 + x->left->height;
	else if(x->right != NULL)
			x->height = 1 + x->right->height;
	else
			x->height = 0;
  
   return x; 
}

AVLTreeNode* AVLTree::rotateLeft(AVLTreeNode* y)
{
	AVLTreeNode *x = y->right; 
   AVLTreeNode *T2 = x->left; 
  
   x->left = y; 
   y->right = T2;
   if(T2!=NULL)
      T2->parent = y;
   y->parent = x;
  
	if(y->left != NULL && y->right != NULL)
			y->height = 1 + max(y->left->height, y->right->height);
	else if(y->left != NULL)
			y->height = 1 + y->left->height;
	else if(y->right !=NULL)
			y->height = 1 + y->right->height;
	else
			y->height = 0;
   if(x->left != NULL && x->right != NULL)
			x->height = 1 + max(x->left->height, x->right->height);
	else if(x->left != NULL)
			x->height = 1 + x->left->height;
	else if(x->right !=NULL)
			x->height = 1 + x->right->height;
	else
			x->height = 0;
  
   return x; 
}

bool AVLTree::insert(int key, string value)
{
   AVLTreeNode *node = root;
   this->size++;

   AVLTreeNode *e = newNode(key, value);

   if(root == NULL)
   {
		root = e;
		return true;
	}
   int f = 1;
	while(f)
   {
			if(node->key < e->key)
         {
				if(node->right == NULL)
            {
					e->parent = node;
					node->right = e;
					f=0;
				}
				else
					node = node->right;
			}
			else if(node->key > e->key)
         {
				if(node->left == NULL)
            {
					e->parent = node;
					node->left = e;
					f=0;
				}
				else
					node = node->left;
			}
			else
         {
				this->size--;
				return false;
			}
	}

   node = e->parent;
	while(node != NULL)
   {
		if(node->left != NULL && node->right != NULL)
			node->height = 1 + max(node->left->height, node->right->height);
		else if(node->left != NULL)
			node->height = 1 + node->left->height;
		else if(node->right != NULL)
			node->height = 1 + node->right->height;
		else
			node->height = 0;
		node = node->parent;
	}

   AVLTreeNode *z,*y,*x,*p;
	z = e->parent;
	y = e;
	x = NULL;
	int heightDiff;
	while(z != NULL)
   {
		heightDiff = getHeightDif(z);
		if((heightDiff > 1) || (heightDiff<(-1)))
      {
			p = z->parent;
			if(z->left == y && y->left == x)
         {
				node = rotateRight(z);
			}
			else if(z->left == y && y->right == x)
         {
				node = rotateLeft(y);
				node->parent = z;
				z->left = node;
				node = rotateRight(z);
			}
			else if(z->right == y && y->right == x)
         {
				node = rotateLeft(z);
			}
			else
         {
				node = rotateRight(y);
				node->parent = z;
				z->right = node;
				node = rotateLeft(z);
			}
			if(p!=NULL)
         {
				node->parent = p;
				if(p->right == z)
					p->right = node;
				else
					p->left = node;
			}
			else
         {
				root = node;
				node->parent = NULL;
			}
			node = node->parent;
			while(node != NULL)
         {
				if(node->left != NULL && node->right != NULL)
					node->height = 1 + max(node->left->height, node->right->height);
				else if(node->left != NULL)
					node->height = 1 + node->left->height;
				else if(node->right != NULL)
					node->height = 1 + node->right->height;
				else
					node->height = 0;
				node = node->parent;
			}
		}
		x=y;
		y=z;
		z=z->parent;
	}

   return true;
}

bool AVLTree::find(int key, string& value)
{
	if(root == NULL)
		return false;
	AVLTreeNode *node = root;
	while(1)
   {
      if(node == NULL)
         return false;
      else if(node->key == key)
      {
         value = node->value;
			return true;
      }
		else if(node->key < key)
			node = node->right;
		else if(node->key > key)
			node = node->left;
	}
}

vector<string> AVLTree::findRange(int lowkey,int highkey)
{
   vector<string> result;
	insertAllInRange(root, lowkey, highkey, result);
   return result;
}

void AVLTree::insertAllInRange(AVLTreeNode *e, int lowkey, int highkey, vector<string>& vect)
{
	if(e==NULL)
		return;
	if(e->key > lowkey)
		insertAllInRange(e->left, lowkey, highkey, vect);
	if((e->key >= lowkey) && (e->key <= highkey))
		vect.push_back(e->value);
	if(e->key < highkey)	
		insertAllInRange(e->right, lowkey, highkey, vect);
}

ostream& operator<<(ostream& os, AVLTree& me)
{
   AVLTreeNode *e = me.getRoot();
   me.printInOrder(os, e, 0);
   return os;
}

void AVLTree::printInOrder(ostream& os, AVLTreeNode *e, int space)
{
	if(e == NULL)
		return;
   
   space += COUNT;

	printInOrder(os, e->right, space);
   for (int i = COUNT; i < space; i++)
        os << " ";
	os << e->key << ", " << e->value << endl;
	printInOrder(os, e->left, space);	
}
