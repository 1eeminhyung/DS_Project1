#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include "TreeNode.h"
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

//Declare BinarySearchTree class
class BinarySearchTree {
private:
    //declare member variable
    TreeNode* root;             //root node
    int numofTreenode;          //numofnode to expect handling for move command
public:

    //declare memeber function
    TreeNode* Getroot() { return root; }
    int GetnumofTreenode() { return numofTreenode; }

    BinarySearchTree() { root = nullptr; numofTreenode = 0; }
    bool Insert(ImageNode* node);
    void PrintInorder(TreeNode* node, ofstream& fout);
    bool PostorderIter(TreeNode* root, string name, ofstream& fout);
    string Preorder(TreeNode* node, int num);
    void DeleteFirstNode();

    bool BoyerMooreSearch(string name, string pat);
    TreeNode* FindNode(int num, string name);


    void freememory(TreeNode* node);

};

#endif
