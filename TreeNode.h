#ifndef TREENODE_H
#define TREENODE_H

#include "ImageNode.h"
#include <iostream>

using namespace std;
 
 //define Treenode
class TreeNode {
    friend class BinarySearchTree;
    friend class ImageNode;
private:
    //declare member variable 
    ImageNode* node;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode() {        //decalre constructor
        left = nullptr;
        right = nullptr;
        node = nullptr;

    }
    //declare member function and define.
    TreeNode* Getleft() const { return this->left; }
    TreeNode* Getright() const { return this->right; }
    ImageNode* GetNode() const { return this->node; }

    void Setleft(TreeNode* left) { this->left = left; }
    void Setright(TreeNode* right) { this->right = right; }
    void SetNode(ImageNode* nodedata) {
        node = nodedata;
    }

};
#endif
