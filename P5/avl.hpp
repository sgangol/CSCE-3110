/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 5                                         **
                  Program reads the input file provide by the user
				  through the argument and constructs an AVL Tree
 ********************************************************************/

struct AvlNode {
    int element;
    AvlNode *left;
    AvlNode *right;
    int height;

    AvlNode (const int & ele, AvlNode *lt, AvlNode *rt, int h = 0) {
        element = ele;
        left = lt;
        right = rt; 
    }
};
