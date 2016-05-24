// Name: Ben Wilfong
// File Name: tree.h
// Date: 5 Dec, 2014
// Program Description:
//     This header file contains the declarations
// for both types of nodes used in the program,
// one for the AVL tree and another for the
// linked list the AVLNodes hold. This file also
// defines constants for the balance factor
// of the nodes.

#ifndef TREE_H
#define TREE_H

#define LH 1
#define EH 0
#define RH -1

struct LLNode
{
    LLNode *next;
    string  latinWord;
};
                
struct AVLNode
{
    AVLNode      *left,
                 *right;
       
    LLNode       *dataList;

    string       englishWord;
                   
    int          balance;
};
      
AVLNode* AVLInsert(AVLNode*, string, string, bool&);
AVLNode* leftBalance(AVLNode*, bool&);
AVLNode* rightBalance(AVLNode*, bool&);
AVLNode* rotateLeft(AVLNode*);
AVLNode* rotateRight(AVLNode*);

bool AVLSearchAdd(AVLNode*, string, string);
void insertWord(AVLNode*&, string);
void displayInOrder(AVLNode*); 
void deleteTree(AVLNode*);
#endif
