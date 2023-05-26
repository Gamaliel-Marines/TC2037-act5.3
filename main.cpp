// =============================================================================
// File: lexer.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <regex>
#include "utils.h"
#include "libs/html.h"
#include <pthread.h>

using namespace std;

vector<string> TEST_CODE;
int main(int argc, char* argv[]) {

    for(auto &p:filesystem::directory_iterator(DIR_TESTS)){
        TEST_CODE.push_back(p.path());
    };

    // Run multiple times
    for (int i = 0; i < 1; i++) {
        for(int j = 0; j < TEST_CODE.size(); j++) {
            // Get CS Code
            CreateHTMLFile(TEST_CODE[j], j);
        };
    };
    return 0;
}