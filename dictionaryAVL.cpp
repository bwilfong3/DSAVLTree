// Name: Ben Wilfong
// File Name: dictionaryAVL.cpp
// Date: 5 Dec, 2014
// Program description:
//    This driver program contains a system
// for parsing a specially formatted text
// file in order to switch the latin-to-english
// translations to english-to-latin translations
// in the style of a dictionary entry. After the
// words are split into their appropriate strings,
// they are packaged off and put into an AVL tree
// until there are no more words left to read.
// Then, the tree is displayed in the same format,
// having reversed the translations.



#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "tree.h"


/*
   AN EXPLANATION FOR THE ALGORITHM IN MAIN:

   Since we have command line arguments and function
   calls to make, I figured it might be simpler to
   just do the partitioning of the file in main().

   It got a little uglier than I anticipated, but
   the way the while loop works is by using the
   punctuation of the file to determine which
   word is which. If a colon ':' character is reached,
   we know that there is no more characters of a latin
   word to read (which are being concatenated into a string
   initially). If the colon character is reached, a flag
   is toggled to indicate that we now want to concatenate
   our characters onto the other string for the english
   word. Once a comma ',' character or a newline '\n'
   character is reached, we know that we have finished
   our english word and are ready to send it off. We
   first check if the english word is already in the tree.
   If so, the latin word is appended to that node's linked
   list. If not, a new node is created with the english and
   corresponding latin word. Note that if a '\n' character
   is reached, we know that it is time for a new latin word
   and the flag is again toggled. This is repeated until
   the end of the file, then the tree is displayed and deleted.

*/


int main(int argc, char* argv[])
{
    AVLNode* root = NULL;

    string latinWord   = "",
           englishWord = "";

    char   buffer;

    bool   isLatinWord = true,
           taller;

    ifstream vocabFile;
    vocabFile.open(argv[1]);

    if (!vocabFile)
       cout << "File open failed." << endl;

    while(vocabFile.get(buffer))
    {

        if (isLatinWord)
        {
            if (buffer == ':')
                isLatinWord = false;

            else
                latinWord+= buffer;
        }

        else
        {
            if (buffer == ',')
            {
                if(!AVLSearchAdd(root, englishWord, latinWord))
                    root = AVLInsert(root, englishWord, latinWord, taller);


                englishWord = "";
            }

            else if (buffer == '\n')
            {
                if(!AVLSearchAdd(root, englishWord, latinWord))
                    root = AVLInsert(root, englishWord, latinWord, taller);

                isLatinWord = true;
                englishWord = latinWord = ""; // reset both strings
            }

            else
            {
                if(englishWord == "")
                {
                    if (buffer >= 'a' && buffer <= 'z')
                        englishWord+= buffer;
                }

                else
                {
                    if ((buffer >= 'a' && buffer <= 'z') ||
                        (buffer == ' '))
                        englishWord+= buffer;
                }
            }
        }
    }

    displayInOrder(root); // display tree
    deleteTree(root);     // delete tree
}
