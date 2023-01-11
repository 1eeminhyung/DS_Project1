#ifndef LOADED_LIST
#define LOADED_LIST

#include "ImageNode.h"
#include <iostream>
#include <fstream>

using namespace std;

//declare Loaded_List class
class Loaded_List {
public:

    //function declaration
    Loaded_List();
    void LoadInsert(string dir, int num, string name);
    void AddInsert(string dir, int num, string name);
    void DeleteandReplace(string dir, int newnum, string name);
    void DeleteFirstNode();

    void DeleteLoadList();

    bool FindNode(string dir, string name);
    void PrintLoadList(ofstream& fout);
    void PrintAddList(int n);

    int getnumofnode() { return numofnode; }

    ImageNode* retlastNode();

    int numofdir;
private:
    ImageNode* head;
    int numofnode;

};

#endif