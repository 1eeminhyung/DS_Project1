#include "BinarySearchTree.h"
#include <stack>
#include <queue>

#include <iostream>

using namespace std;

bool BinarySearchTree::Insert(ImageNode* node) {        //insert Node recall from list
    //if Insert Node return true, else unique num is same return false
    
    if(root == nullptr) {
        root = new TreeNode;
        root->SetNode(node);
        numofTreenode++;            //expect handling for move command
        return true;
    }
    TreeNode* New = new TreeNode;
    New->SetNode(node);
    TreeNode* Cur = root;
    TreeNode* temp = nullptr;
    //Insert node in Tree
    while(Cur) {
        if(Cur->GetNode()->Getnum() > node->Getnum()) {
            temp = Cur;
            Cur = Cur->Getleft();
        }
        else if(Cur->GetNode()->Getnum() < node->Getnum()) {
            temp = Cur;
            Cur = Cur->Getright();
        }
        else {
            //cout << "Unique number is same" << endl;      //Except handling that have the same unique number. 
            return false;
        }
    }
    if(temp->GetNode()->Getnum() > node->Getnum()) {
        temp->Setleft(New);
        numofTreenode++;                                    //Expect handling that treenode is over 300
        return true;
    }
    else if(temp->GetNode()->Getnum() < node->Getnum()) {
        temp->Setright(New);
        numofTreenode++;
        return true;
    }
    return true;
} 

void BinarySearchTree::PrintInorder(TreeNode* node, ofstream& fout) {
    //Define PrintInorder to perform Print Command
    if(node) {
        PrintInorder(node->Getleft(), fout);
        fout << node->GetNode()->Getdir() << " / "  << node->GetNode()->Getname() << " / " << node->GetNode()->Getnum() << endl;
        PrintInorder(node->Getright(), fout);
    }
}

 bool BinarySearchTree::PostorderIter(TreeNode* root, string name, ofstream& fout) {
    //findSearchNode and print if find node->return true
    //else return false
    if(root == nullptr) return false;   //if tree is empty
    stack<TreeNode*> s;
    s.push(root);

    queue<pair<int,string>> q;
    //while stack is not empty
    while(!s.empty()) {
        TreeNode* Cur = s.top();
        s.pop();
        q.push(make_pair(Cur->GetNode()->Getnum(), Cur->GetNode()->Getname()));

        if(Cur->Getleft()) {
            s.push(Cur->Getleft());
        }
        if(Cur->Getright()) {
            s.push(Cur->Getright());
        }
    }
    bool b = false;
    while(!q.empty()) {
        if(BoyerMooreSearch(q.front().second, name)) {  //FindNode using BoyerMoore ALgorithm
        //if(q.front().second.find(name) != string::npos) {
            fout << "\"" << q.front().second << "\"" << "  " << q.front().first << endl;
            b = true;
        }
        q.pop();
    }
    return b;
} 
string BinarySearchTree::Preorder(TreeNode* node, int num) {
    //Define Preorder function to find filename using unique number.
    TreeNode* temp;
    string s = "";
    if(root == nullptr) return s;       //if Treenode is not exist, return ""
    stack<TreeNode*> st;
    st.push(node);

    stack<pair<int,string>> out;
    while(!st.empty()) {     //loop while s is empty
        //push all node In tree
        TreeNode* Cur = st.top();
        st.pop();
        out.push(make_pair(Cur->GetNode()->Getnum(), Cur->GetNode()->Getname()));
        if(Cur->Getright()) {
            st.push(Cur->Getright());
        }  
        if(Cur->Getleft()) {
            st.push(Cur->Getleft());
        }            
    }

    while(!out.empty()) {
        if(out.top().first == num) {
            s = out.top().second;
        }
        out.pop();
    }
    return s;
}

bool BinarySearchTree::BoyerMooreSearch(string name, string specific) {
    //BoyerMoore Algorithm search pattern in name
    int lengname = name.length();
    int lengSpe = specific.length();

    int badchar[256] = { -1, };
    for(int i=0 ; i<lengSpe ; i++) {
        badchar[(int)specific[i]] = i;
    }

    int s = 0;
    int j;
    while(s < lengname - lengSpe) {
        j = lengSpe-1;

        while(j >= 0 && name[s+j] == specific[j])
            j--;
        
        if(j < 0) {
            return true;    //find Pat
        }
        else {
            int n = max(1,j-badchar[(int)name[s+j]]);
            s += n;
        }
    }
    return false;       //cannot find Pat
}

void BinarySearchTree::DeleteFirstNode() {
    //Except handling to Insert node in MOVE command when node is over 300
    TreeNode* Cur = root;
    TreeNode* Prev = root;
    TreeNode* PrevPrev = root;
    while(Cur) {
        PrevPrev = Prev;
        Prev = Cur;
        Cur = Cur->Getleft();
    }    
    if(Prev->Getright() == nullptr) {
        delete Prev;
        PrevPrev->Setleft(nullptr);
        numofTreenode--;
        return;
    }
    else {
        Cur = Prev->Getright();
        PrevPrev->Setleft(Cur);
        delete Prev;
        numofTreenode--;
        return;
    }

}


void BinarySearchTree::freememory(TreeNode* node) {
    //Define freememory function to perform EXIT command
    if(node == nullptr) return;

    freememory(node->Getleft());
    freememory(node->Getright());
    delete node;
}