// =============================================================================
// File: html.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <iostream>
#include <filesystem>
#include "./regex.h"

using namespace std;

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
    "     font-family: 'Anuphan', sans-serif;"
    "    background: #25292E;"
    "}"
    ".keyword {"
    "    color: #E87D85;"
    "}"
    ".operator {"
    "    color: #D3747C;"
    "    margin: 0 2px;"
    "    display: inline-block;"
    "}"
    ".delimitador {"
    "    color: #F3AF7A;"
    "    margin: 0 2px;"
    "    display: inline-block;"
    "}"
    ".comment {"
    "    color: #6C737C;"
    "}"
    ".literal {"
    "    color: #A7CAFA;"
    "    margin-right: -7px;"
    "    display: inline-block;"
    "}"
    ".System {"
    "    color: #87B6F9;"
    "}"
    ".identifier {"
    "    color: #c3acf7;"
    "}";

void CreateCSSlFile() {
    ofstream outputStyles;

    string name, html, path;

    mkdir(DIR_1.c_str(), 0777);

    outputStyles.open("./" + DIR_1 + "/styles.css", ios::out);
    outputStyles << STYLES; 
    outputStyles.close();

    mkdir(DIR_2.c_str(), 0777);

    outputStyles.open("./" + DIR_2 + "/styles.css", ios::out);
    outputStyles << STYLES; 
    outputStyles.close(); 
};

void CreateHTMLFile(string filename, int index) {
    CreateCSSlFile();

    ofstream outputHTML;
    ifstream inputFile;

    inputFile.open(filename, ios::in);

    string name, html;

    html = HTML_HEADER;
    string aux;
    string* cs = new string[100];
    int counter = 0;

    while(!inputFile.eof()) {
        getline(inputFile, aux);
        cs[counter] += aux; 
        counter++;
    }

    string tokenized_code = TokenizeCode(cs, counter);

    html += tokenized_code;
    html += HTML_FOOTER;

    name = "./" + DIR_1 + "/html";
    name += to_string(index);
    name += ".html";

    outputHTML.open(name, ios::out);
    outputHTML << html;

    outputHTML.close();
    inputFile.close();    
};