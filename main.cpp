// Implement code on Manager.c file (recommandation)

#include "Manager.h"

using namespace std;

int main(int argc, char* argv[]) {
    const string commandFilePath = "command.txt";

    Manager m;
    m.Run(commandFilePath);

    return 0;
}

