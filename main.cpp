// =============================================================================
// File: lexer.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "libs/lexer.h"

using namespace std;

vector<string> TEST_CODE;
int main(int argc, char* argv[]) {

    for(auto &p:filesystem::directory_iterator(DIR_TESTS)){
        TEST_CODE.push_back(p.path());
    };

    double seq_time = run_seq(TEST_CODE);
    double parallel_time = run_parallel(TEST_CODE);

    cout << "El paralelo es: " << seq_time / parallel_time << " veces más rápido" << endl;

    return 0;
}