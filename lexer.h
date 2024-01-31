#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    KEYWORD,
    RESERVED_WORD,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    ASSIGNMENT_OP,
    ARITHMETIC_OP,
    UNARY_OP,
    BOOLEAN_OP,
    LOGICAL_OP,
    LEFT_CURLY,
    RIGHT_CURLY,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    SEMICOLON,
    SINGLE_COMM,
    MULTI_COMM,
    CHAR,
    STRING,
    COMMA,
    AMP,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    UNKNOWN,
    EOF_TOKEN
} TokenType;

typedef enum { BOOL_TYPE } ValueType;

typedef struct {
    TokenType type;
    char lexeme[100];
} Token;

const char* tokenTypeToString(TokenType type);

int classifyKeyword(const char* keyword);

int classifyReservedWord(const char* keyword);

bool isincharset(char character);

void lexer(FILE* inputFile, FILE* outputFile, Token* tokens, int* tokenIndex);

#endif  // LEXER_H