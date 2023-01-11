#ifndef RESULT
#define RESULT

enum Result
{
    //define Result enum
    Success = 0,

    CommandFileNotExist = 1,
    LoadFileNotExist = 100,
    AddFileNotExist = 200,
    ModifyNodeNotExist = 300,
    //VertexKeyNotExist = 200,
    LoadListNotExist = 400,
    BSTNotExist = 500,
    SearchFail = 600,
    NoSelectFile = 700,
    CommandIsNotExit=777,
    EditFail = 800,

};

#endif