#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

string editfile = "";       //declare global variable

Manager::~Manager()         //Destructor
{
    if (fout.is_open())     //if file open, file close
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const string filepath)
{
    ifstream fin;
    fout.open(RESULT_LOG_PATH);
    ferr.open(ERROR_LOG_PATH);
    Result result;

    fin.open(filepath);
    if (!fin)
    {
        PrintErrorCode(CommandFileNotExist);
        return;
    }

    char cmd[256];
    while (!fin.eof())
    {
        fin.getline(cmd, 256);              //getline command.txt
        char *ptr = strtok(cmd, " ");
        if (ptr == nullptr)                 //Except Handling
        {
            continue;
        }
        if (ptr[0] == '/' && ptr[1] == '/')     //Except Handling
        {
            continue;
        }
        if (strcmp(ptr,"LOAD") == 0)            //if commnad is LOAD
        {
            while(ptr != NULL) {
                ptr = strtok(NULL, " ");
            }
            result = Load("filesnumbers.csv");    
            if (result == Success)
            {
                fout << "=======LOAD==========" << endl;
                List.PrintLoadList(fout);
                fout << "=====================" << endl;
                List.numofdir++;                    //Increase the number of directories after LOAD
            }
            else if (result == LoadFileNotExist)
            {
                PrintErrorCode(LoadFileNotExist);      //Print Error code 100
            }
        }
        else if (strcmp(ptr, "ADD") == 0)
        {
            ptr = strtok(NULL, " ");
            if(ptr == nullptr) {
                PrintErrorCode(AddFileNotExist);
                continue;
            }
            string dir = (string)ptr;
            ptr = strtok(NULL, " ");
            if(ptr == nullptr) {
                PrintErrorCode(AddFileNotExist);    //no factor.
                continue;
            }
            string filename = (string)ptr;

            while (ptr != NULL)
            { // call strtok function to the end
                ptr = strtok(NULL, " ");
            }

            if(dir == "img_files") {    //if add directory is img_files, load file.
                List.DeleteLoadList();
                result = Load(filename);
            }
            else {
                result = Add(dir, filename);    //add directory is not img_files
            }

            if (result == Success)
            {
                fout << "==========ADD==========" << endl;
                fout << "SUCCESS" << endl;
                ++List.numofdir;                            //if Add Success is complete numofdir++
                
                fout << "=======================" << endl;
            }
            else
            {
                PrintErrorCode(AddFileNotExist);            //PrintErrorcode 200
            }
        }

        else if (strcmp(ptr, "MODIFY") == 0)
        {
            ptr = strtok(NULL, " ");
            if(ptr == nullptr) {
                PrintErrorCode(ModifyNodeNotExist);     //no factor
                continue;
            }
            string dir = (string)ptr;
            
            ptr = strtok(NULL, "\"");
            if(ptr == nullptr) {
                PrintErrorCode(ModifyNodeNotExist);     //no factor
                continue;
            }
            string name = (string)ptr;
            
            ptr = strtok(NULL, " "); 
            int num = atoi(ptr);
            result = Modify(dir, name, num);            //operate modify function

            if (result == Success)
            {
                fout << "=======MODIFY=======" << endl;
                fout << "SUCCESS" << endl;
                fout << "====================" << endl;
            }

            else if (result == ModifyNodeNotExist)
            {
                PrintErrorCode(ModifyNodeNotExist);         //Print errorcode 300
            }
        }

        else if(strcmp(ptr, "MOVE") == 0) {
            result = Move();
            if(result == Success) {
                fout << "=======MOVE========" << endl;
                fout << "SUCCESS" << endl;
                fout << "===================" << endl;
            }
            else if(result == LoadListNotExist) {
                PrintErrorCode(LoadListNotExist);           //print Errorcode 400
            }
        }

        else if(strcmp(ptr, "PRINT") == 0) {
            if(Tree.Getroot() != nullptr) {
                fout << "========PRINT========" << endl;
                Print();                                       //Operate Print function
                fout << "=====================" << endl;
            }
            else {
                PrintErrorCode(BSTNotExist);                //PrintErrorcode 500
            }
        }

        else if(strcmp(ptr, "SEARCH") == 0) {
            ptr = strtok(NULL, "\"");
            if(ptr == nullptr) {
                PrintErrorCode(SearchFail);
                continue;
            }
            string name = (string)ptr;
            
            if(Tree.Getroot() != nullptr) {
                fout << "=======SEARCH========" << endl;
                fout << "Search word is \"" << name << "\""<< endl << endl;
                result = Search(name);                                      //Operate Search function
                fout << "=======================" << endl;
            }

            else {
                PrintErrorCode(SearchFail);     //Print Errorcode 600
            }

        }

        else if(strcmp(ptr, "SELECT") == 0) {
            ptr = strtok(NULL, " ");
            if(ptr == nullptr) {
                PrintErrorCode(NoSelectFile);       //if have no mercy
                continue;
            }
            int num = atoi(ptr);

            result = Select(num);                   //Operate Select function
            if(result == Success) {
                fout << "=======SELECT========" << endl;
                fout << "SUCCESS" << endl;
                fout << "=====================" << endl;
            }
            else {
                PrintErrorCode(NoSelectFile);               //Printerrorcode 
            }
        }

        else if(strcmp(ptr, "EDIT") == 0) {
            ptr = strtok(NULL, " ");
            if(ptr == nullptr) {            //if have no mercy
                PrintErrorCode(EditFail);
                continue;
            }
            if(strcmp(ptr, "-f") == 0) {
                result = EditSymmertry();       //Operate EditSymmertry to point reverse (x,y)
                if(result == Success) {
                    fout << "=========EDIT==========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=======================" << endl;
                }
                else {
                    PrintErrorCode(EditFail);           //print Errorcode 800
                }
            }
            else if(strcmp(ptr, "-l") == 0) {
                ptr = strtok(NULL, " ");
                if(ptr == nullptr) {
                    PrintErrorCode(EditFail);       //no factor, PrintErrorCode
                    continue;
                }
                int num = atoi(ptr);                //array to int function
                result = EditBrightness(num);       //Operate EditBrightness function to change image brightness 
                if(result == Success) {
                    fout << "=========EDIT==========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=======================" << endl;
                }
                else {
                    PrintErrorCode(EditFail);               //Print Errorcode 800
                }
            }

            else if(strcmp(ptr, "-r") == 0) {
                result = EditImageSize();           //operate EditImageSize fuction to edit image size
                if(result == Success) {
                    fout << "=========EDIT==========" << endl;
                    fout << "SUCCESS" << endl;
                    fout << "=======================" << endl;
                }
                else {
                    PrintErrorCode(EditFail);               //printErrorcode 800
                }
            }
        }

        else if(strcmp(ptr, "EXIT") == 0) {
            Tree.freememory(Tree.Getroot());                //freememory in the tree

            fout << "==========EXIT=========" << endl;
            fout << "SUCCESS" << endl;
            fout << "=======================" << endl;            

            return;
        }

        else {
            PrintErrorCode(CommandIsNotExit);           //printErrorCode 777
        }

    }
    fin.close();
}
void Manager::PrintErrorCode(Result result)
{
    fout << "============ERROR=========" << endl;
    fout << result << endl;
    fout << "==========================" << endl;
}

Result Manager::Load(const string filepath)
{
    // TODO: implement
    vector<pair<int, string>> files;
    ifstream fload(filepath);

    if (!fload)
    {
        //fout << "Cannot Load File" << endl;
        return LoadFileNotExist;
    }
    char buf[256];
    while (!fload.eof())
    {
        fload.getline(buf, 256);

        char *ptr = strtok(buf, ",");
        if (ptr == nullptr) continue; // except

        int num = atoi(ptr);
        ptr = strtok(NULL, ".");
        string name = (string)ptr;
        while (ptr != NULL)
        {
            ptr = strtok(NULL, " ");
        }
        files.push_back(make_pair(num, name));
    }
    for (int i = 0; i < files.size(); i++)
    {
        if(List.getnumofnode() >= 100) {
            List.DeleteFirstNode();         //if Loadfile is over 100, delete Firstnode in list
        }
        List.LoadInsert("img_files", files[i].first, files[i].second);
    }
    fload.close();
    return Success;
}

Result Manager::Add(const string dir, const string filepath)
{
    vector<pair<int, string>> files;

    ifstream fadd(filepath);
    if (!fadd)
    {
        fout << "================" << endl;
        fout << "Cannot Add File" << endl;
        fout << "================" << endl;
        return AddFileNotExist;
    }
    char buf[256];
    while (!fadd.eof())
    {
        // char buf[256];
        fadd.getline(buf, 256);

        char *ptr = strtok(buf, ",");
        if (ptr == nullptr) continue; // except file error
        
        int num = atoi(ptr);
        ptr = strtok(NULL, ".");
        string name = (string)ptr;

        while (ptr != NULL)
        {
            ptr = strtok(NULL, " ");
        }
        files.push_back(make_pair(num, name));
    }
    for (int i = 0; i < files.size(); i++)
    {
        if(List.getnumofnode() >= 100) {         //if node is over 100, delete first node
            //exception handling
            List.DeleteFirstNode();
        }
        List.AddInsert(dir, files[i].first, files[i].second);   //add node
    }

    fadd.close();
    return Success;
}

Result Manager::Modify(const string dir, const string name, const int num) {
    if(!List.FindNode(dir, name)) {
        //if can't find node, return ModifyNodeNotExist
        return ModifyNodeNotExist;
    }
    else {
        //else Delete and Replace in Linked List
        List.DeleteandReplace(dir, num, name);
        return Success;
    }

}

Result Manager::Move() {
    ImageNode* temp = List.retlastNode();
    //temp is last node in List.
    //if temp == nullptr List is not Exist
    if(temp == nullptr) {                   //if Loaded list is not Exist
        return LoadListNotExist;
    }
    bool b = Tree.Insert(temp);             //insert first Treenode & set root
    if(b == false) return LoadListNotExist;

    //while list is not empty, return lastnode in linkedlist & insert in the Tree
    while(temp != nullptr) {
        temp = List.retlastNode();
        if(temp != nullptr) {
            if(Tree.GetnumofTreenode() >= 300) {    //if Tree node is over 300, Delete first node and insert.
                Tree.DeleteFirstNode();
            }
            b = Tree.Insert(temp);
        }
    }
    return Success;
}

void Manager::Print() {
    Tree.PrintInorder(Tree.Getroot(), fout);    //operate PrintInorder function
    return;
}

Result Manager::Search(string word) {
    //Operate PostorderIter function to search command
    bool b = Tree.PostorderIter(Tree.Getroot(), word, fout);
    //If bool is false, it mean can't search pattern.
    if(b != true) return SearchFail;    
    else        //if bool is true, it mean find pattern.
        return Success;
}

Result Manager::Select(int num) {
    //Define editfile(global variable) as the file name received as return value using unique number.
    editfile = Tree.Preorder(Tree.Getroot(), num);
    if(editfile == "") {    //if file name not found with unique number return NoSelectFile.
        return NoSelectFile;
    }
    else {
        RawReader(editfile);    //else Operte editfileFunction
        return Success;
    }

}

void Manager::RawReader(string filename) {
    //define RawReader function
    int width = 256, height = 256;
    //images width is 256, height is 256

    FILE* input_file, *output_file;

    string s = filename;
    string fout_filepath;

    s = "./images/" + s;            //Path Setting, s = "./images/filenames.raw"
    s = s + ".RAW";
    fout_filepath = editfile + ".RAW";

    const char* filepath = s.c_str();
    const char* foutfilepath = fout_filepath.c_str();
    unsigned char input_data[256][256];         //array to be read from the image folder.
    unsigned char output_data[256][256];        //array 256*256 to be write.

    input_file = fopen(filepath, "rb");         //read in binary form
    if(input_file == NULL) {                    //input file is null, means that can't read .raw file.
        fout << "file not found" << endl;
        return;
    }
    fread(input_data, sizeof(char), width * height, input_file);    //read .raw file to arry

    for(int i=0 ; i<height ; i++) {
        for(int j=0 ; j<width ; j++) {              //load image.
            output_data[i][j] = input_data[i][j];
        }
    }
    output_file = fopen(foutfilepath, "wb");                        //writee in binary form
    fwrite(output_data, sizeof(char), width * height, output_file);

    fclose(input_file);                 //close input_file.
    fclose(output_file);                //close output_file.
}

Result Manager::EditSymmertry() {
    //define EditSymmerty to be point-symmetric
    FILE* fin_editSym, * fout_editSym;

    string fin_filepath = editfile + ".RAW";

    const char* c1 = fin_filepath.c_str();
    fin_editSym = fopen(c1, "rb");

    if(fin_editSym == NULL) return EditFail;

    unsigned char in_editSym[256][256];     //array to read file called frem the Select function
    unsigned char out_editSym[256][256];    //array to write

    fread(in_editSym, sizeof(char), 256*256, fin_editSym);
    stack<unsigned char> s;             //stack to be point-symmetric

    for(int i=0 ; i<256 ; i++) {
        for(int j=0 ; j<256 ; j++) {
            s.push(in_editSym[i][j]);
        }
    }

    string fout_filepath = editfile + "_flipped.RAW";   //FIle name to create
    const char* c2 = fout_filepath.c_str();
    fout_editSym = fopen(c2, "wb");

    if(s.size() != 256*256) return EditFail;    //Exception handling

    unsigned char temp;
    //The value of the file pixel is stored as a point symmetric value in the stack.
    //Spin double repeat statements and store the value of the stack in output data.
    for(int i=0 ; i<256 ; i++) {
        for(int j=0 ; j<256 ; j++) {
            temp = s.top();
            s.pop();
            out_editSym[i][j] = temp;
        }
    }    

    //fwrite 
    fwrite(out_editSym, sizeof(char), 256*256, fout_editSym);

    fclose(fin_editSym);
    fclose(fout_editSym);
    return Success;
}


Result Manager::EditBrightness(int num) {
    FILE* fin_editBright, *fout_editBright;

    string fin_filepath = editfile + ".RAW";
    const char* c1 = fin_filepath.c_str();

    fin_editBright = fopen(c1, "rb");

    if(fin_editBright == NULL) return EditFail;

    unsigned char in_editBright[256][256];
    unsigned char out_editBright[256][256];

    fread(in_editBright, sizeof(char), 256*256, fin_editBright);
    queue<unsigned char> q;

    for(int i=0 ; i<256 ; i++) {
        for(int j=0 ; j<256 ; j++) {
            q.push(in_editBright[i][j]);
        }
    }

    string fout_filepath = editfile + "_adjusted.RAW";
    const char* c2 = fout_filepath.c_str();
    fout_editBright = fopen(c2, "wb");
    if(q.size() != 256*256) return EditFail;

    unsigned char temp;
    for(int i=0 ; i<256 ; i++) {
        for(int j=0 ; j<256 ; j++) {
            temp = q.front();
            q.pop();
            if(temp + num >= 256) {
                out_editBright[i][j] = 255;
                continue;
            }
            out_editBright[i][j] = temp + num;
        }
    }

    //fwrite outputfile.
    fwrite(out_editBright, sizeof(char), 256*256, fout_editBright);

    fclose(fin_editBright);
    fclose(fout_editBright);

    return Success;
}

Result Manager::EditImageSize() {
    //Define EditImageSize to edit Image size.
    FILE* fin_editImageSize, *fout_editImageSize;

    string fin_filepath = editfile + ".RAW";

    const char* c1 = fin_filepath.c_str();
    fin_editImageSize = fopen(c1, "rb");    //read binary form

    if(fin_editImageSize == NULL) return EditFail;

    unsigned char in_editImageSize[256][256];   //array to read
    //resize image to 1/4 size
    unsigned char out_editImageSize[128][128];  //array to write.

    fread(in_editImageSize, sizeof(char), 256*256, fin_editImageSize);

    string fout_filepath = editfile + "_resized.RAW";
    const char* c2 = fout_filepath.c_str();

    fout_editImageSize = fopen(c2, "wb");           //write binary form

    unsigned char temp;
    //Spin the double repetition and calculate average the cell size and store it in output data
    for(int i=0 ; i<256 ; i+=2) {
        for(int j=0 ; j<256 ; j+=2) {
            temp = ceil((in_editImageSize[i][j] + in_editImageSize[i][j+1] + in_editImageSize[i+1][j] + in_editImageSize[i+1][j+1]) / 4);
            out_editImageSize[i/2][j/2] = temp;
        }
    } 

    //write output_file.
    fwrite(out_editImageSize, sizeof(char), 128*128, fout_editImageSize);

    //file close
    fclose(fin_editImageSize);
    fclose(fout_editImageSize);

    return Success;
}