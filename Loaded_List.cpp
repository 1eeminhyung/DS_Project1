#define _CRT_SECURE_NO_WARNINGS
#include "Loaded_List.h"

using namespace std;

Loaded_List::Loaded_List()    //Define constructor  
{
    head = nullptr;
    numofdir = 0;
    numofnode = 0;
}

void Loaded_List::LoadInsert(string dir, int num, string name)
{
    //define LoadInsert to perform the load command
    ImageNode *New = new ImageNode(dir, num, name);
    ImageNode *Cur = head;
    if (head == nullptr)
    {
        ImageNode *dirNode = new ImageNode; // Make First Node(dirNode)
        dirNode->Setdir(dir);
        head = dirNode;
        dirNode->Setnext(New);
        numofnode++;                        //To expect handling, count numofnode
        return;
    }
    else
    {
        ImageNode *Prev = head;
        while (Cur)
        {
            Prev = Cur; // move prevNode to LastNode
            Cur = Cur->Getnext();
        }
        Prev->Setnext(New);
        numofnode++;                    //To expect handling, count numofnode
    }
    return;
}

void Loaded_List::AddInsert(string dir, int num, string name)
{
    //Define AddInsert to perform the load command
    ImageNode *New = new ImageNode(dir, num, name);
    ImageNode *Cur = head;
    if (head == nullptr)
        return; // Call Add before road

    for (int i = 0; i < numofdir - 1; i++)  //getdown to dirnode
        Cur = Cur->Getdown();

    if (Cur->Getdown() == nullptr)
    {
        ImageNode *dirNode = new ImageNode;     //declare dirnode 
        dirNode->Setdir(dir);
        Cur->Setdown(dirNode);
        dirNode->Setnext(New);
        numofnode++;                //increase num of node
        return;
    }
    else
    {
        Cur = Cur->Getdown();       //insert node
        ImageNode *Prev = Cur;
        while (Cur)
        {
            Prev = Cur;
            Cur = Cur->Getnext();
        }
        Prev->Setnext(New);
        numofnode++;            //increase num of node
        return;
    }
}

void Loaded_List::PrintLoadList(ofstream& fout)
{
    //Define PrintLoadList to perform print
    ImageNode *Cur = head->Getnext();
    if (head == nullptr)
    {
        return; // NoLoadList
    }
    while (Cur)
    {
        //print in log.txt
        fout << Cur->Getname() << "/" << Cur->Getnum() << endl;
        Cur = Cur->Getnext();
    }
}

void Loaded_List::PrintAddList(int n)       //To verify that add is well done.
{                                           //cout AddList
    ImageNode *Cur = head;
    if (n > numofdir)
    {
        cout << "There is no dir" << endl;
        return;
    }
    if (Cur->Getdown() == nullptr)
    {
        cout << "No Add data" << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++)
    {
        Cur = Cur->Getdown();
    }
    cout << Cur->Getdir() << endl << endl;
    while (Cur)
    {
        if (Cur->Getnum() == 0)
        {
            Cur = Cur->Getnext();
            continue;
        }
        cout << Cur->Getname() << "/" << Cur->Getnum() << endl;
        Cur = Cur->Getnext();
    }
}

void Loaded_List::DeleteandReplace(string dir, int newnum, string name)
{
    //Define DeleteandReplace to perform MODIFY command
    ImageNode *Cur = head;
    ImageNode *Prev = nullptr;
    while (Cur)
    {
        if (Cur->Getdir() == dir)
            break;
        Cur = Cur->Getdown();
    }
    while (Cur)
    {
        if (Cur->Getnum() == 0 && Cur != nullptr)
        {
            Prev = Cur;
            Cur = Cur->Getnext();
            continue;
        }
        else if (Cur->Getname() == name)
        { // deleteNode & Replace
            ImageNode *New = new ImageNode(dir, newnum, name);
            if (Cur->Getnext() == nullptr)
            { // deleteNode is last node
                Prev->Setnext(New);
                New->Setnext(nullptr);
                delete Cur;
                return;
            }
            else
            { // DeleteNode is linked prev & next
                Prev->Setnext(New);
                New->Setnext(Cur->Getnext());
                delete Cur;
                return;
            }
        }
        Prev = Cur;
        Cur = Cur->Getnext();        
    }

}

bool Loaded_List::FindNode(string dir, string name)     //find node using dir,name
{
    //Define findnode function to perform MODIFY command
    ImageNode *Cur = head;
    while (Cur)
    {
        if (Cur->Getdir() == dir)
        {
            break;
        }
        Cur = Cur->Getdown();
    }
    while (Cur)
    {
        if (Cur->Getnum() == 0)
        {
            Cur = Cur->Getnext();
            continue;
        }
        if (Cur->Getname() == name)
        {
            return true;
        }
        Cur = Cur->Getnext();
    }
    return false;
}

ImageNode *Loaded_List::retlastNode()
{
    //define retlastNode function to perform MOVE
    if(head == nullptr) return nullptr;
    ImageNode *Cur = head;
    ImageNode *Prev = nullptr;
    for (int i = 0; i < numofdir - 1; i++)
    {   
        Prev = Cur;
        Cur = Cur->Getdown();
    }
    while (Cur->Getnext() != nullptr)
    {
        Prev = Cur;        
        Cur = Cur->Getnext();
    }
    if (Cur->Getnum() == 0 && Cur != nullptr)             //delete before dirNode
    {
        if(Cur == head) {
            delete Cur;
            numofdir = 0;
            return nullptr;
        }
        Prev->Setdown(nullptr);
        delete Cur;
        numofdir--;                                         //if delete dirnode, numofdir=numofdir-1

        Cur = head;
        Prev = nullptr;
        for(int i=0 ; i < numofdir-1 ; i++) {
            Prev = Cur;
            Cur = Cur->Getdown();
        }
        while(Cur->Getnext() != nullptr) {
            Prev = Cur;
            Cur = Cur->Getnext();
        }
        ImageNode* temp = new ImageNode(Cur->Getdir(), Cur->Getnum(), Cur->Getname());
        Prev->Setnext(nullptr);
        delete Cur;
        return temp;
    }
    ImageNode* temp = new ImageNode(Cur->Getdir(), Cur->Getnum(), Cur->Getname());
    Prev->Setnext(nullptr);
    delete Cur;
    return temp; 
}

void Loaded_List::DeleteFirstNode() {       //if node num over 100 
    //Expect handling for load, add command
    ImageNode* Cur = head->Getnext();

    if(Cur->Getnext() == nullptr) {     //delete dirnode
        ImageNode* temp = head;
        head = temp->Getdown();
        delete Cur;
        delete temp;
        numofnode--;
        return;
    }
    ImageNode* temp = head;         //else
    temp->Setnext(Cur->Getnext());
    Cur->Setnext(nullptr);
    numofnode--;
    delete Cur;
    return;
}

void Loaded_List::DeleteLoadList() {        //expect handling when add directory is img_files
    ImageNode* Cur = head;
    ImageNode* Prev = nullptr;
    while(1) {
        while(Cur->Getnext() != nullptr) {
            Prev = Cur;
            Cur = Cur->Getnext();       //move Cur = lastnode
        }
        if(Prev->Getnum() != 0) {    //if Prev is not dirnode
            Prev->Setnext(nullptr);
            delete Cur;
            numofnode--;
            Cur = head;
            continue;
        }
        else {                      //if Prev is dirnode
            delete Prev;
            head = nullptr;
            numofdir--;
            break;
        }
    }
}