// =============================================================================
// File: html.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <iostream>
#include <filesystem>
#include <pthread.h>

#include "./regex.h"

using namespace std;

typedef struct {
    int start, end;
    vector<string> test_code;
} Block;

const string DIR_1 = "sequential";
const string DIR_2 = "parallel";
const string DIR_TESTS = "./tests";

const string HTML_HEADER =
    "<!DOCTYPE html>"
    "    <html lang='en'>"
    "    <head>"
    "        <meta charset='UTF-8'>"
    "        <meta http-equiv='X-UA-Compatible' content='IE=edge'>"
    "        <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "        <link rel='stylesheet' href='styles.css'>"
    "        <title>C# code editor</title>"
    "    </head>"
    "    <body>"
    "       <pre>";

const string HTML_FOOTER =
    "       </pre>"
    "    </body>"
    "</html>";

const string STYLES = 
    "body {"
    "    font-family: 'Anuphan', sans-serif;"
    "    background: #25292E;"
    "}"
    ".keyword {"
    "    color: #E87D85;"
    "}"
    ".operator {"
    "    color: #D3747C;"
    "    margin: 0 1px;"
    "    display: inline-block;"
    "}"
    ".delimitador {"
    "    color: #F3AF7A;"
    "    margin: 0 1px;"
    "    display: inline-block;"
    "}"
    ".comment {"
    "    color: #6C737C;"
    "}"
    ".literal {"
    "    color: #A7CAFA;"
    "    margin-right: 1px;"
    "    display: inline-block;"
    "}"
    ".System {"
    "    color: #87B6F9;"
    "}"
    ".identifier {"
    "    color: #c3acf7;"
    "}";

// ===================================================================
// This function creates the CSS file corresponding to the execution type
//
// Parameters:
//  string dir: The directory in which the CSS file is going to be created
// ===================================================================
void create_css_file(const string dir) {
    ofstream output_styles;
    mkdir(dir.c_str(), 0777);

    output_styles.open("./" + dir + "/styles.css", ios::out);
    output_styles << STYLES; 
    output_styles.close();
};

// ===================================================================
// This function creates the HTML file corresponding to the execution type
//
// Parameters:
//  string filename: The corresponding CS filename code
//  int index: This index corresponds to the number of the HTML file, so it can be named that way
//  string dir: The directory in which the HTML file is going to be created
// ===================================================================
void create_html_file(string filename, int index, string dir) {
    ofstream output_HTML;
    ifstream input_file;

    input_file.open(filename, ios::in);

    string name, html;

    html = HTML_HEADER;
    string aux;
    string* cs = new string[100];
    int counter = 0;

    while(!input_file.eof()) {
        getline(input_file, aux);
        cs[counter] += aux; 
        counter++;
    }

    string tokenized_code = tokenize_code(cs, counter);

    html += tokenized_code;
    html += HTML_FOOTER;

    name = "./" + dir + "/html";
    name += to_string(index);
    name += ".html";

    output_HTML.open(name, ios::out);
    output_HTML << html;

    output_HTML.close();
    input_file.close();    
};

// ===================================================================
// This function calls create_html_file() but it splits the job to its corresponding 
// block
//
// Parameters:
//  void* params: The Block of the thread distribution
// ===================================================================
void* create_html_file_parallel(void* params) {
    Block* b;
    b = (Block*) params;
    
    create_css_file(DIR_2);
    for(int i = b->start; i < b->end; i++){
        create_html_file(b->test_code[i], i, DIR_2);
    };

    pthread_exit(NULL);
};