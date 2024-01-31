#include <stdlib.h>

// main.c
#include "lexer.h"
#include "parser.h"

// prototype
void processInputFile(const char* filename, FILE* outputFile);

int main() {
    FILE* outputFile = fopen("symbol_table.txt", "w");

    if (outputFile == NULL) {
        fprintf(stderr,
                "Error: Unable to open symbol_table.txt for writing.\n");
        return 1;
    }
    processInputFile("test.ms", outputFile);
    fclose(outputFile);
    return 0;
}

void processInputFile(const char* filename, FILE* outputFile) {
    FILE* inputFile = fopen(filename, "r");

    if (inputFile == NULL) {
        fprintf(stderr, "Error: Unable to open %s for reading.\n", filename);
        exit(1);
    }

    Token tokens[1000];

    int tokenIndex = 0;

    lexer(inputFile, outputFile, tokens, &tokenIndex);
    fclose(inputFile);

    int currentIndex = 0;

    TreeNode* syntaxTreeRoot = parseProgram(tokens, &currentIndex);
    printSyntaxTree(syntaxTreeRoot, 0);
    freeSyntaxTree(syntaxTreeRoot);
}