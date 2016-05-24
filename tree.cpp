// Name: Ben Wilfong
// File Name: tree.cpp
// Date: 5 Dec, 2014
// Program Description:
//     This file contains the bodies
// for the functions used in the main
// driver program. Such functions include
// ones given to us to insert nodes while
// maintaining balance on the tree, slightly
// augmented to handle strings. Other functions
// include one to search the tree for a particular
// word and one to display a tree in InOrder
// format.



#include <iostream>
#include <string>

using namespace std;

#include "tree.h"


AVLNode* AVLInsert(AVLNode* root, string engWord, string latinEquiv, bool& taller)
{
    if (root == NULL)
    {
        root = new AVLNode;
        root->englishWord = engWord;
        root->dataList = new LLNode;        // Begin the linked list of Latin-equivalent
       (root->dataList)->latinWord = latinEquiv; // words because a new AVLNode is being inserted
       (root->dataList)->next = NULL;
        root->left = root->right = NULL;
        root->balance = EH;
        taller = true;
        return root;
    }

    if (engWord.compare(root->englishWord) < 0)
    {
        root->left = AVLInsert(root->left, engWord, latinEquiv, taller);

        if (taller)
        {
            switch(root->balance)
            {
                case LH:
                    root = leftBalance(root, taller);
                    break;

                case EH:
                    root->balance = LH;

                case RH:
                    root->balance = EH;
                    taller = false;
                    break;
            }

        }
    }

    else if (engWord.compare(root->englishWord) >= 0)
    {
        root->right = AVLInsert(root->right, engWord, latinEquiv, taller);

        if (taller)
        {
            switch(root->balance)
            {
                case LH:
                    root->balance = EH;
                    taller = false;
                    break;

                case EH:
                    root->balance = RH;
                    break;

                case RH:
                    root = rightBalance(root,taller);
                    break;
            }
        }
    }

    return root;
} // end insertAVL()


/*
   The leftBalance() function will balance and call
   a rotate function for a node. As its name implies,
   it is used in order to preserve the balance of
   the tree. This function is no different than the
   algorithms given out in class.
*/

AVLNode* leftBalance(AVLNode* root, bool& taller)
{
    AVLNode *leftTree, *rightTree;
    leftTree = root->left;

    switch(leftTree->balance)
    {
        case LH: //left-of-left, rotate right
            root->balance = EH;
            leftTree->balance = EH;
            root = rotateRight(root);
            taller = false;
            break;

        case EH: //cannot happen
            break;

        case RH: //right of left
            switch(rightTree->balance)
            {
                case LH:
                    root->balance = RH;
                    leftTree->balance = EH;
                    break;

                case EH:
                    root->balance = EH;
                    leftTree->balance = EH;
                    break;

                case RH:
                    root->balance = EH;
                    leftTree->balance = LH;
                    break;
             }

             rightTree->balance = EH;
             root->left = rotateLeft(leftTree);
             root = rotateRight(root);
             taller = false;
             break;
        }

        return root;

}// end leftBalance()


/*
   The rightBalance() function is merely a
   mirror of the leftBalance() function in every
   way. Each left is replaced with right, each
   LH is replaced with RH and vice versa.
*/

AVLNode* rightBalance(AVLNode* root, bool& taller)
{
    AVLNode *rightTree, *leftTree;
    rightTree = root->right;

    switch(rightTree->balance)
    {
        case RH: //right-of-right, rotate left
            root->balance = EH;
            rightTree->balance = EH;
            root = rotateLeft(root);
            taller = false;
            break;

        case EH: //cannot happen
            break;

        case LH: //left of right
            switch(leftTree->balance)
            {
                case RH:
                    root->balance = LH;
                    rightTree->balance = EH;
                    break;

                case EH:
                    root->balance = EH;
                    rightTree->balance = EH;
                    break;

                case LH:
                    root->balance = EH;
                    rightTree->balance = RH;
                    break;
             }

             leftTree->balance = EH;
             root->right = rotateRight(rightTree);
             root = rotateLeft(root);
             taller = false;
             break;
        }

        return root;
}


/*
   The rotateLeft() function is also one directly
   used from our class notes. Simply, a temporary
   node is created in order to shift the nodes
   in a counterclockwise fashion.
*/

AVLNode* rotateLeft(AVLNode* root)
{
    AVLNode* temp = root->right;
    root->right = temp->left;
    temp->left = root;

    return temp;
}


/*
   Like before, the rotateRight() function is
   just an exact mirror of rotateLeft()
*/

AVLNode* rotateRight(AVLNode* root)
{
    AVLNode* temp = root->left;
    root->left = temp->right;
    temp->right = root;

    return temp;
}


/*
   Now, the AVLSearchAdd function is a little peculiar.
   In regards to the main concept of the program,
   if we are to add an English-Latin combo to our tree,
   we must check to see if the English word is already
   there. Knowing this, I've created an algorithm that will
   perform a recursive binary search with a bool return type. If
   the English word is found in the tree, a function is immediately
   called to add the latin word to the corresponding English
   word's linked list. We also return true in this scenario.
   However, if the search was not succesful, we return false
   without any insertion. This is so that a proper AVL insert
   can be performed in case the English word is not already
   in the tree.
*/

bool AVLSearchAdd(AVLNode* root, string engWord, string latinWord)
{
    if (root == NULL)
        return false;

    else
    {
        if (engWord.compare(root->englishWord) < 0)
            return AVLSearchAdd(root->left, engWord, latinWord);

        else if (engWord.compare(root->englishWord) > 0)
            return AVLSearchAdd(root->right, engWord, latinWord);

        else
        {
            insertWord(root, latinWord);
            return true;
        }
     }
}


/*
   insertWord() takes a root (by reference) and
   appends a latin word to the end of the root's
   linked list.
*/
void insertWord(AVLNode* &root, string latinWord)
{
    LLNode* temp = new LLNode;
    temp->latinWord = latinWord;
    temp->next = NULL;

    if((root->dataList) == NULL)
    {
        root->dataList = temp;
        return;
    }

    else
    {
        LLNode* walker = root->dataList;

        while(walker->next != NULL)
            walker = walker->next;

        walker->next = temp;
    }
}


/*
   displayInOrder() does exactly what it
   claims, it displays the nodes' english
   words in order! The function is augmented
   to also display the node's containing
   linked list in a neatly formatted manner.
*/

void displayInOrder(AVLNode* root)
{
    if (root)
    {
        displayInOrder(root->left);
        cout << root->englishWord << ": ";

        LLNode* temp = root->dataList;

        while (temp != NULL)
        {
            if (temp->next == NULL)
                cout << temp->latinWord; //for formatting

            else
                cout << temp->latinWord << ", ";

            temp = temp->next;
        }

        cout << endl;

        displayInOrder(root->right);
    }
}


/*
   Finally, deleteTree() recursively
   destroys the tree until there
   is nothing left to delete. During
   each deletion, the node's corresponding
   linked list is also obliterated.
*/

void deleteTree(AVLNode* root)
{
    if (root == NULL)
        return;

    else
    {
        deleteTree(root->left);
        deleteTree(root->right);

        while(root->dataList != NULL)
        {
            LLNode* temp = root->dataList;
            root->dataList = temp->next;
            delete temp;
            temp = NULL;
        }

        delete root;
        root = NULL;
    }
}
