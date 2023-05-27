// =============================================================================
// File: regex.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <regex>

using namespace std;

// ===================================================================
// This function takes the lines of code, runs the regex expressions
// and tokenize the lines into understandable and separated html code
//
// Parameters:
//  string* input_arr: The array containing all the lines of code
//  int input_size: The size of the total lines of code
//
// Returns:
// string result: The tokenized code
// ===================================================================
string tokenize_code(string* input_arr, int input_size) {

    string result = "";
    
    const string keywords = "abstract|as|base|bool|break|byte|case|catch|char|checked|class|const|continue|decimal|default|delegate|double|do|else|enum|event|explicit|extern|false|finally|fixed|float|foreach|for|foreach|goto|if|implicit|int|in|interface|internal|is|lock|long|namespace|new|null|object|operator|out|override|params|private|protected|public|readonly|ref|return|sbyte|sealed|short|sizeof|stackalloc|static|string|struct|switch|this|throw|true|try|typeof|uint|ulong|unchecked|unsafe|ushort|using|virtual|void|volatile|while";
    const string identifiers = "[a-zA-Z_][a-zA-Z0-9_]*";
    const string operators = "\\+|-|\\|/|%|\\^|&|\\||~|!|=|<|>|\\?|:|;|,|\\.|\\+\\+|--|&&|\\|\\||==|!=|<=|>=|\\+=|-=|\\=|/=|%\\=|\\^=|&\\=|\\|=|<<=|>>=|=>|\\?\\?";
    const string literals = "[0-9]+(\\.[0-9]+)?|\".*\"|'.*'";
    const string comments = "//.*|/\\*.*\\*/";
    const string system = "System|Console|Program|program";
    const string separators = "[\\(\\)\\{\\}\\[\\];,.]";
    const string line_break = "\n";
    const string delimitadors = "[(]|[)]|[[]|[\\]]|[{]|[}]";
    const string white_space = "\\s+";

    // Regular expressions
    const regex all_tokens(keywords + "|" + identifiers + "|" + operators + "|" + literals + "|" + comments + "|" + system + "|" + separators + "|" + line_break + "|" + white_space + "|" + delimitadors);

    // Tokenize the code
    for (int i = 0; i < input_size; i++) {
        string input = input_arr[i];
        string tokenized_code = "";

        auto current = sregex_iterator(input.begin(), input.end(), all_tokens);
        const auto end = sregex_iterator();

        while (current != end) {
            const string token = (*current).str();

            if (token == "\n") {
                tokenized_code += "<br>";
            } else {
                string type;

                if (regex_match(token, regex(line_break))) {
                    tokenized_code += "</pre><pre>";
                } else if (regex_match(token, regex(white_space))) {
                    tokenized_code += token;
                } else if (regex_match(token, regex(operators))) {
                    type = "operator";
                } else if (regex_match(token, regex(comments))) {
                    type = "comment";
                } else if (regex_match(token, regex(keywords))) {
                    type = "keyword";
                } else if (regex_match(token, regex(delimitadors))) {
                    type = "delimitador";
                } else if (regex_match(token, regex(literals))) {
                    type = "literal";
                } else if (regex_match(token, regex(system))) {
                    type = "System";
                } else if (regex_match(token, regex(separators))) {
                    type = "separator";
                } else if (regex_match(token, regex(identifiers))) {
                    type = "identifier";
                } else {
                    type = "error";
                };

                tokenized_code += "<span class=\"" + type + "\">" + token + "</span>";
            };

            ++current;
        };
        result += tokenized_code += " <br> ";
    };

    return result;
}