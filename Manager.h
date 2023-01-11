#define _CRT_SECURE_NO_WARNINGS
#ifndef MANAGER
#define MANAGER

#include "Result.h"
#include "Loaded_List.h"
#include "BinarySearchTree.h"

#include <fstream>
#include <string>

using namespace std;

class Manager
{
private:
    // the filepath for the result log
    const string RESULT_LOG_PATH = "log.txt";
    const string ERROR_LOG_PATH = "log.txt";

    ofstream fout;                          //declare ofstream fout to write in log.txt
    ofstream ferr;
    //declare class object.
    Loaded_List List;
    BinarySearchTree Tree;

public:
    ~Manager();
    //Function declaration
    void Run(const string filepath);      
    void PrintErrorCode(Result result);
    void PrintSuccess(char* act);
    void RawReader(string filename);

private:

    //Function declaration
    Result Load(const string filepath);
    Result Add(const string dir, const string filepath);
    Result Modify(const string dir, const string name, const int num);
    Result Move();
    void Print();
    Result Search(string word);
    Result Select(int num);
    Result EditSymmertry();
    Result EditBrightness(int num);
    Result EditImageSize();
};

#endif
