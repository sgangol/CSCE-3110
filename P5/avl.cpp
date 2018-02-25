/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 5                                         **
                  Program reads the input file provide by the user
				  through the argument and constructs an AVL Tree
 ********************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

// Get the height of a tree
int height(AvlNode * root)
{
	if (root == NULL)
		return -1;

	return root->height;
}

// Get which of the two values is larger
int max(int val1, int val2)
{
	if (val1 > val2)
		return val1;
	
	return val2;
}

// Do a single left rotation
void rotateLeft(AvlNode * & k2)
{
	AvlNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

// Do a single right rotation
void rotateRight(AvlNode * & k1)
{
	AvlNode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

// Do a double left rotation
void doubleLeftRotation(AvlNode * & k)
{
	rotateRight(k->left);
	rotateLeft(k);
}

// Do a double right rotation
void doubleRightRotation(AvlNode * & k)
{
	rotateLeft(k->right);
	rotateRight(k);
}

// Balance the tree
void balance(AvlNode * & root)
{
	if (root == NULL)
		return;

	if (height(root->left) - height(root->right) > 1)
		if (height(root->left->left) >= height(root->left->right))
			rotateLeft(root);
		else
			doubleLeftRotation(root);
	else if (height(root->right) - height(root->left) > 1)
		if (height(root->right->right) >= height(root->right->left))
			rotateRight(root);
		else
			doubleRightRotation(root);

	root->height = max(height(root->left), height(root->right)) + 1;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert( const int & info, AvlNode * & root )
{
	if (root == nullptr)
		root = new AvlNode(info, nullptr, nullptr);
	else if (info < root->element)
		insert( info, root->left );
	else  if (info > root->element)
		insert( info, root->right );

	balance(root);
}

// Find the smallest node from the root
AvlNode * findMin(AvlNode *root)
{
	if (root == NULL)
		return NULL;

	if (root->left == NULL)
		return root;

	return findMin(root->left);
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int & info, AvlNode * & root ) 
{
	if (root == NULL)
		return;

	if (info < root->element)
	{
		remove(info, root->left);
	}
	else if (root->element < info)
	{
		remove(info, root->right);
	}
	else if (root->left != NULL && root->right != NULL)
	{
		root->element = findMin(root->right)->element;
		remove(root->element, root->right);
	}
	else
	{
		AvlNode *prevNode = root;

		if (root->left != NULL)
			root = root->left;
		else
			root = root->right;

		delete prevNode;
	}

	balance(root);
}

/*
 * You will probably neesd auxiliary mathods to 
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance am AVL  tree
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
