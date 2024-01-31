#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H

#define MAX_LEXEME_SIZE 256
#define MAX_CHILDREN 100

typedef enum {
    PROGRAM_NODE,
    DECLARATION_NODE,
    DATA_TYPE_NODE,
    IDENTIFIER_LIST_NODE,
    IDENTIFIER_NODE,
    ASSIGNMENT_NODE,
    VALUE_NODE,
    OUTPUT_NODE,
    STRING_NODE,
    INPUT_NODE,
    END_OF_INPUT
} NodeType;

typedef struct TreeNode {
    NodeType type;
    char value[MAX_LEXEME_SIZE];
    ValueType valueType;
    struct TreeNode* children[MAX_CHILDREN];
    size_t childCount;
} TreeNode;

TreeNode* parseProgram(Token tokens[], int* currentIndex);
TreeNode* parseDeclaration(Token tokens[], int* currentIndex);
TreeNode* parseDataType(Token tokens[], int* currentIndex);
TreeNode* parseIdentifierList(Token tokens[], int* currentIndex);
TreeNode* parseIdentifier(Token tokens[], int* currentIndex);
TreeNode* parseValue(Token tokens[], int* currentIndex,
                     const char* expectedType);

void addChild(TreeNode* parent, TreeNode* child);
void printSyntaxTree(TreeNode* root, int depth);
void freeSyntaxTree(TreeNode* root);
void printError(const char* message, int index);

TreeNode* parseOutputStatement(Token tokens[], int* currentIndex);
TreeNode* parseAssignmentStatement(Token tokens[], int* currentIndex);
TreeNode* parseString(Token tokens[], int* currentIndex);
TreeNode* createOutputNode();
TreeNode* parseOutputStatement(Token tokens[], int* currentIndex);
TreeNode* parseInputStatement(Token tokens[], int* currentIndex);
TreeNode* parseNextTokenAsValue(Token tokens[], int* currentIndex);
TreeNode* createStringNode(const char* value);

// TreeNode* syntaxTreeRoot = NULL;

#endif  // PARSER_H