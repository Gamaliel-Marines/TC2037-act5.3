// =============================================================================
// File: regex.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <regex>

using namespace std;

typedef struct {
    int start, end;
} Block;

const int THREADS = 8;
const int SIZE = 18;

string TokenizeCode(string* input_arr, int input_size) {

    string result = "";

    // Regular expressions
    const string keywords = "abstract|as|base|bool|break|byte|case|catch|char|checked|class|const|continue|decimal|default|delegate|double|do|else|enum|event|explicit|extern|false|finally|fixed|float|foreach|for|foreach|goto|if|implicit|int|in|interface|internal|is|lock|long|namespace|new|null|object|operator|out|override|params|private|protected|public|readonly|ref|return|sbyte|sealed|short|sizeof|stackalloc|static|string|struct|switch|this|throw|true|try|typeof|uint|ulong|unchecked|unsafe|ushort|using|virtual|void|volatile|while";
    const string identifiers = "[a-zA-Z_][a-zA-Z0-9_]*";
    const string operators = "\\+|-|\\|/|%|\\^|&|\\||~|!|=|<|>|\\?|:|;|,|\\.|\\+\\+|--|&&|\\|\\||==|!=|<=|>=|\\+=|-=|\\=|/=|%\\=|\\^=|&\\=|\\|=|<<=|>>=|=>|\\?\\?";
    const string literals = "[0-9]+(\\.[0-9]+)?|\".*\"|'.*'";
    const string comments = "//.*|/\\*.*\\*/";
    const string system = "System|Console|Program|program";
    const string separators = "[\\(\\)\\{\\}\\[\\];,.]";
    const string lineBreak = "\n";
    const string whiteSpace = "\\s+";
    const regex allTokens(keywords + "|" + identifiers + "|" + operators + "|" + literals + "|" + comments + "|" + system + "|" + separators + "|" + lineBreak + "|" + whiteSpace);

    // Tokenize the code
    for (int i = 0; i < input_size; i++) {
        string input = input_arr[i];
        string tokenizedCode = "";

        auto current = sregex_iterator(input.begin(), input.end(), allTokens);
        const auto end = sregex_iterator();

        while (current != end) {
            const string token = (*current).str();

            if (token == "\n") {
                tokenizedCode += "<br>";
            } else {
                string type;

                if (regex_match(token, regex(lineBreak))) {
                    tokenizedCode += "</pre><pre>";
                } else if (regex_match(token, regex(whiteSpace))) {
                    tokenizedCode += token;
                } else if (regex_match(token, regex(operators))) {
                    type = "operator";
                } else if (regex_match(token, regex(comments))) {
                    type = "comment";
                } else if (regex_match(token, regex(keywords))) {
                    type = "keyword";
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

                tokenizedCode += "<span class=\"" + type + "\">" + token + "</span>";
            };

            ++current;
        };
        result += tokenizedCode += " <br> ";
    };

    return result;
}