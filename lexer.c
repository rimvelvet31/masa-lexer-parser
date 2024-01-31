#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case KEYWORD:
            return "KEYWORD";
        case RESERVED_WORD:
            return "RESERVED WORD";
        case IDENTIFIER:
            return "IDENTIFIER";
        case INTEGER:
            return "INTEGER";
        case FLOAT:
            return "FLOAT";
        case ASSIGNMENT_OP:
            return "ASSIGNMENT OPERATOR";
        case ARITHMETIC_OP:
            return "ARITHMETIC OPERATOR";
        case UNARY_OP:
            return "UNARY OPERATOR";
        case BOOLEAN_OP:
            return "BOOLEAN OPERATOR";
        case LOGICAL_OP:
            return "LOGICAL OPERATOR";
        case LEFT_CURLY:
            return "LEFT CURLY BRACES";
        case RIGHT_CURLY:
            return "RIGHT CURLY BRACES";
        case LEFT_PAREN:
            return "LEFT PARENTHESIS";
        case RIGHT_PAREN:
            return "RIGHT PARENTHESIS";
        case LEFT_BRACKET:
            return "LEFT BRACKET";
        case RIGHT_BRACKET:
            return "RIGHT BRACKET";
        case SEMICOLON:
            return "SEMICOLON";
        case SINGLE_COMM:
            return "SINGLE LINE COMMENT";
        case MULTI_COMM:
            return "MULTI LINE COMMENT";
        case CHAR:
            return "CHARACTER";
        case STRING:
            return "STRING";
        case COMMA:
            return "COMMA";
        case AMP:
            return "AMPERSAND";
        case SINGLE_QUOTE:
            return "SINGLE QUOTE";
        case DOUBLE_QUOTE:
            return "DOUBLE QUOTE";
        case UNKNOWN:
            return "UNKNOWN";
        case EOF_TOKEN:
            return "EOF";
        default:
            return "INVALID";
    }
}

enum KW_State {
    KW_STATE_0,
    KW_STATE_1,
    KW_STATE_2,
    KW_STATE_3,
    KW_STATE_4,
    KW_STATE_6,
    KW_STATE_7,
    KW_STATE_8,
    KW_STATE_9,
    KW_STATE_10,
    KW_STATE_11,
    KW_STATE_13,
    KW_STATE_14,
    KW_STATE_15,
    KW_STATE_16,
    KW_STATE_17,
    KW_STATE_18,
    KW_STATE_19,
    KW_STATE_20,
    KW_STATE_21,
    KW_STATE_22,
    KW_STATE_23,
    KW_STATE_24,
    KW_STATE_25,
    KW_STATE_27,
    KW_STATE_28,
    KW_STATE_29,
    KW_STATE_30,
    KW_STATE_31,
    KW_STATE_32,
    KW_STATE_33,
    KW_STATE_34,
    KW_STATE_35,
    KW_STATE_37,
    KW_STATE_39,
    KW_STATE_40,
    KW_STATE_41,
    KW_STATE_42,
    KW_STATE_ACCEPTED
};

int classifyKeyword(const char* keyword) {
    enum KW_State currentState = KW_STATE_0;
    int idx;
    for (idx = 0; idx < strlen(keyword); idx++) {
        char c = keyword[idx];
        switch (currentState) {
            case KW_STATE_0:
                switch (c) {
                    case 'b':
                        currentState = KW_STATE_1;
                        break;
                    case 'i':
                        currentState = KW_STATE_6;
                        break;
                    case 'p':
                        currentState = KW_STATE_13;
                        break;
                    case 't':
                        currentState = KW_STATE_39;
                        break;
                    case 'w':
                        currentState = KW_STATE_27;
                        break;
                    case 'k':
                        currentState = KW_STATE_33;
                        break;
                    default:
                        return 0;
                }
                break;
            // balik branch
            case KW_STATE_1:
                if (c == 'a') {
                    currentState = KW_STATE_2;
                } else
                    return 0;
                break;
            case KW_STATE_2:
                if (c == 'l') {
                    currentState = KW_STATE_3;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_3:
                if (c == 'i') {
                    currentState = KW_STATE_4;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_4:
                if (c == 'k') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // ipakita branch
            case KW_STATE_6:
                if (c == 'p') {
                    currentState = KW_STATE_7;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_7:
                if (c == 'a') {
                    currentState = KW_STATE_8;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_8:
                if (c == 'k') {
                    currentState = KW_STATE_9;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_9:
                if (c == 'i') {
                    currentState = KW_STATE_10;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_10:
                if (c == 't') {
                    currentState = KW_STATE_11;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_11:
                if (c == 'a') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // para branch
            case KW_STATE_13:
                if (c == 'a') {
                    currentState = KW_STATE_14;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_14:
                if (c == 'r') {
                    currentState = KW_STATE_15;
                } else if (c == 's') {
                    currentState = KW_STATE_16;
                } else if (c == 'n') {
                    currentState = KW_STATE_18;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_15:
                if (c == 'a') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // pasok branch
            case KW_STATE_16:
                if (c == 'o') {
                    currentState = KW_STATE_17;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_17:
                if (c == 'k') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // pangungusap branch
            case KW_STATE_18:
                if (c == 'g') {
                    currentState = KW_STATE_19;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_19:
                if (c == 'u') {
                    currentState = KW_STATE_20;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_20:
                if (c == 'n') {
                    currentState = KW_STATE_21;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_21:
                if (c == 'g') {
                    currentState = KW_STATE_22;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_22:
                if (c == 'u') {
                    currentState = KW_STATE_23;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_23:
                if (c == 's') {
                    currentState = KW_STATE_24;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_24:
                if (c == 'a') {
                    currentState = KW_STATE_25;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_25:
                if (c == 'p') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // walangbalik branch
            case KW_STATE_27:
                if (c == 'a') {
                    currentState = KW_STATE_28;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_28:
                if (c == 'l') {
                    currentState = KW_STATE_29;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_29:
                if (c == 'a') {
                    currentState = KW_STATE_30;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_30:
                if (c == 'n') {
                    currentState = KW_STATE_31;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_31:
                if (c == 'g') {
                    currentState = KW_STATE_32;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_32:
                if (c == 'b') {
                    currentState = KW_STATE_1;
                } else {
                    return 0;
                }
                break;
            // kung branch
            case KW_STATE_33:
                if (c == 'u') {
                    currentState = KW_STATE_34;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_34:
                if (c == 'n') {
                    currentState = KW_STATE_35;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_35:
                if (c == 'g') {
                    currentState = KW_STATE_ACCEPTED;
                } else if (c == 'd') {
                    currentState = KW_STATE_37;
                } else {
                    return 0;
                }
                break;
            // kundi branch
            case KW_STATE_37:
                if (c == 'i') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            // tigil branch
            case KW_STATE_39:
                if (c == 'i') {
                    currentState = KW_STATE_40;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_40:
                if (c == 'g') {
                    currentState = KW_STATE_41;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_41:
                if (c == 'i') {
                    currentState = KW_STATE_42;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_42:
                if (c == 'l') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;
            case KW_STATE_ACCEPTED:
                return 1;
        }
    }
    return currentState == KW_STATE_ACCEPTED ? 1 : 0;
}

enum RW_State {
    RW_STATE_0,
    RW_STATE_1,
    RW_STATE_2,
    RW_STATE_3,
    RW_STATE_4,
    RW_STATE_5,
    RW_STATE_6,
    RW_STATE_7,
    RW_STATE_8,
    RW_STATE_9,
    RW_STATE_10,
    RW_STATE_11,
    RW_STATE_12,
    RW_STATE_13,
    RW_STATE_14,
    RW_STATE_15,
    RW_STATE_16,
    RW_STATE_17,
    RW_STATE_18,
    RW_STATE_19,
    RW_STATE_20,
    RW_STATE_21,
    RW_STATE_22,
    RW_STATE_23,
    RW_STATE_24,
    RW_STATE_25,
    RW_STATE_26,
    RW_STATE_27,
    RW_STATE_28,
    RW_STATE_29,
    RW_STATE_30,
    RW_STATE_31,
    RW_STATE_32,
    RW_STATE_33,
    RW_STATE_34,
    RW_STATE_35,
    RW_STATE_ACCEPTED
};

int classifyReservedWord(const char* keyword) {
    enum RW_State currentState = RW_STATE_0;
    int idx;
    for (idx = 0; idx < strlen(keyword); idx++) {
        char c = keyword[idx];
        switch (currentState) {
            case RW_STATE_0:
                switch (c) {
                    case 'b':
                        currentState = RW_STATE_1;
                        break;
                    case 'd':
                        currentState = RW_STATE_4;
                        break;
                    case 'i':
                        currentState = RW_STATE_6;
                        break;
                    case 'k':
                        currentState = RW_STATE_8;
                        break;
                    case 'm':
                        currentState = RW_STATE_10;
                        break;
                    case 'p':
                        currentState = RW_STATE_20;
                        break;
                    case 's':
                        currentState = RW_STATE_28;
                        break;
                    case 't':
                        currentState = RW_STATE_33;
                        break;
                    default:
                        return 0;
                }
                break;
            // bool branch
            case RW_STATE_1:
                if (c == 'o') {
                    currentState = RW_STATE_2;
                } else
                    return 0;
                break;
            case RW_STATE_2:
                if (c == 'o') {
                    currentState = RW_STATE_3;
                } else
                    return 0;
                break;
            case RW_STATE_3:
                if (c == 'l') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // des branch
            case RW_STATE_4:
                if (c == 'e') {
                    currentState = RW_STATE_5;
                } else
                    return 0;
                break;
            case RW_STATE_5:
                if (c == 's') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // int branch
            case RW_STATE_6:
                if (c == 'n') {
                    currentState = RW_STATE_7;
                } else
                    return 0;
                break;
            case RW_STATE_7:
                if (c == 't') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // kar branch
            case RW_STATE_8:
                if (c == 'a') {
                    currentState = RW_STATE_9;
                } else
                    return 0;
                break;
            case RW_STATE_9:
                if (c == 'r') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // mali branch
            case RW_STATE_10:
                if (c == 'a') {
                    currentState = RW_STATE_11;
                } else
                    return 0;
                break;
            case RW_STATE_11:
                if (c == 'l') {
                    currentState = RW_STATE_12;
                } else if (c == 'g') {
                    currentState = RW_STATE_13;
                } else
                    return 0;
                break;
            case RW_STATE_12:
                if (c == 'i') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // magpatuloy branch
            case RW_STATE_13:
                if (c == 'p') {
                    currentState = RW_STATE_14;
                } else
                    return 0;
                break;
            case RW_STATE_14:
                if (c == 'a') {
                    currentState = RW_STATE_15;
                } else
                    return 0;
                break;
            case RW_STATE_15:
                if (c == 't') {
                    currentState = RW_STATE_16;
                } else
                    return 0;
                break;
            case RW_STATE_16:
                if (c == 'u') {
                    currentState = RW_STATE_17;
                } else
                    return 0;
                break;
            case RW_STATE_17:
                if (c == 'l') {
                    currentState = RW_STATE_18;
                } else
                    return 0;
                break;
            case RW_STATE_18:
                if (c == 'o') {
                    currentState = RW_STATE_19;
                } else
                    return 0;
                break;
            case RW_STATE_19:
                if (c == 'y') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // pumuntasa branch
            case RW_STATE_20:
                if (c == 'u') {
                    currentState = RW_STATE_21;
                } else
                    return 0;
                break;
            case RW_STATE_21:
                if (c == 'm') {
                    currentState = RW_STATE_22;
                } else
                    return 0;
                break;
            case RW_STATE_22:
                if (c == 'u') {
                    currentState = RW_STATE_23;
                } else
                    return 0;
                break;
            case RW_STATE_23:
                if (c == 'n') {
                    currentState = RW_STATE_24;
                } else
                    return 0;
                break;
            case RW_STATE_24:
                if (c == 't') {
                    currentState = RW_STATE_25;
                } else
                    return 0;
                break;
            case RW_STATE_25:
                if (c == 'a') {
                    currentState = RW_STATE_26;
                } else
                    return 0;
                break;
            case RW_STATE_26:
                if (c == 's') {
                    currentState = RW_STATE_27;
                } else
                    return 0;
                break;
            case RW_STATE_27:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // simula branch
            case RW_STATE_28:
                if (c == 'i') {
                    currentState = RW_STATE_29;
                } else
                    return 0;
                break;
            case RW_STATE_29:
                if (c == 'm') {
                    currentState = RW_STATE_30;
                } else
                    return 0;
                break;
            case RW_STATE_30:
                if (c == 'u') {
                    currentState = RW_STATE_31;
                } else
                    return 0;
                break;
            case RW_STATE_31:
                if (c == 'l') {
                    currentState = RW_STATE_32;
                } else
                    return 0;
                break;
            case RW_STATE_32:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            // tama branch
            case RW_STATE_33:
                if (c == 'a') {
                    currentState = RW_STATE_34;
                } else
                    return 0;
                break;
            case RW_STATE_34:
                if (c == 'm') {
                    currentState = RW_STATE_35;
                } else
                    return 0;
                break;
            case RW_STATE_35:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;
            case RW_STATE_ACCEPTED:
                return keyword[idx] == '\0' ? 1 : 0;
        }
    }
    return currentState == RW_STATE_ACCEPTED ? 1 : 0;
}

bool isincharset(char character) {
    const char collection[] = "<>?/\\:;\'\"|[]{}!@#$%^&*)(+-=~,.";
    int collectionSize = sizeof(collection) - 1;
    for (int i = 0; i < collectionSize; ++i) {
        if (collection[i] == character) {
            return true;
        }
    }
    return false;
}

int peek(FILE* inputFile) {
    int nextChar = fgetc(inputFile);
    ungetc(nextChar, inputFile);  // Put the character back into the stream
    return nextChar;
}

// Lexer function
void lexer(FILE* inputFile, FILE* outputFile, Token* tokensArray,
           int* tokenIndex) {
    char ch;
    Token token;
    int state = 0;
    int i = 0;
    char nc = peek(inputFile);
    fprintf(outputFile, "%-20s%-10s\n", "Lexeme", "Token");
    while ((ch = fgetc(inputFile)) != EOF) {
        token.type = EOF_TOKEN;
        // Lexer logic
        switch (state) {
            case 0:
                token.lexeme[i] = '\0';
                if (isalpha(ch)) {
                    token.lexeme[i++] = ch;
                    state = 2;
                } else if (isspace(ch)) {
                    state = 0;
                } else if (isdigit(ch)) {
                    token.lexeme[i++] = ch;
                    state = 4;
                } else if (ch == '.') {
                    token.lexeme[i++] = ch;
                    state = 5;
                } else if (ch == '*' || ch == '/' || ch == '%' || ch == ':') {
                    state = 8;
                    token.lexeme[i++] = ch;
                } else if (ch == '+') {
                    state = 9;
                    token.lexeme[i++] = ch;
                } else if (ch == '-') {
                    state = 11;
                    token.lexeme[i++] = ch;
                } else if (ch == '!') {
                    state = 12;
                    token.lexeme[i++] = ch;
                } else if (ch == '=') {
                    state = 13;
                    token.lexeme[i++] = ch;
                } else if (ch == '<' || ch == '>') {
                    state = 14;
                    token.lexeme[i++] = ch;
                } else if (ch == '@' || ch == '|' || ch == '~') {
                    state = 16;
                    token.lexeme[i++] = ch;
                } else if (ch == '{') {
                    state = 17;
                    token.lexeme[i++] = ch;
                } else if (ch == '}') {
                    state = 18;
                    token.lexeme[i++] = ch;
                } else if (ch == '(') {
                    state = 19;
                    token.lexeme[i++] = ch;
                } else if (ch == ')') {
                    state = 20;
                    token.lexeme[i++] = ch;
                } else if (ch == '[') {
                    state = 21;
                    token.lexeme[i++] = ch;
                } else if (ch == ']') {
                    state = 22;
                    token.lexeme[i++] = ch;
                } else if (ch == ';') {
                    state = 23;
                    token.lexeme[i++] = ch;
                } else if (ch == '^') {
                    state = 24;
                    token.lexeme[i++] = ch;
                } else if (ch == '\'') {
                    state = 37;
                    token.lexeme[i++] = ch;
                } else if (ch == '"') {
                    state = 38;
                    token.lexeme[i++] = ch;
                } else if (ch == ',') {
                    state = 34;
                    token.lexeme[i++] = ch;
                } else if (ch == '&') {
                    state = 35;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i++] = ch;
                    state = 1;
                }
                break;
            case 1:
                if (!isspace(ch)) {
                    token.lexeme[i++] = ch;
                    state = 1;
                } else {
                    state = 0;
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 2:
                if (isalnum(ch) || ch == '_' || ch == '.') {
                    token.lexeme[i++] = ch;
                    state = 2;
                } else {
                    token.lexeme[i] = '\0';

                    int x = classifyKeyword(token.lexeme);
                    int y = classifyReservedWord(token.lexeme);

                    if (x == 1) {
                        token.type = KEYWORD;
                    } else if (y == 1) {
                        token.type = RESERVED_WORD;
                    } else {
                        token.type = IDENTIFIER;
                    }

                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 3:
                if (ch == '_' || ch == '.') {
                    token.lexeme[i++] = ch;
                    state = 3;
                } else if (isalnum(ch)) {
                    token.lexeme[i++] = ch;
                    state = 2;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    state = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 4:
                if (isdigit(ch)) {
                    token.lexeme[i++] = ch;
                    state = 4;
                } else if (ch == '.') {
                    token.lexeme[i++] = ch;
                    state = 6;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = INTEGER;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 5:
                if (isdigit(ch)) {
                    token.lexeme[i++] = ch;
                    state = 6;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 6:
                if (isdigit(ch)) {
                    token.lexeme[i++] = ch;
                    state = 6;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = FLOAT;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
                // assignment
            case 7:
                token.lexeme[i] = '\0';
                token.type = ASSIGNMENT_OP;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // arithmetic
            case 8:
                if (ch == '=') {
                    state = 7;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = ARITHMETIC_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // arithmetic
            case 9:
                if (ch == '=') {
                    state = 7;
                    token.lexeme[i++] = ch;
                } else if (ch == '+') {
                    state = 10;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = ARITHMETIC_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // unary
            case 10:
                token.lexeme[i] = '\0';
                token.type = UNARY_OP;
                state = 0;
                i = 0;
                break;
                ungetc(ch, inputFile);
            // arithmetic
            case 11:
                if (ch == '=') {
                    state = 7;
                    token.lexeme[i++] = ch;
                } else if (ch == '-') {
                    state = 10;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = ARITHMETIC_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // boolean
            case 12:
                if (ch == '=') {
                    state = 15;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = BOOLEAN_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // assignment
            case 13:
                if (ch == '=') {
                    state = 15;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = ASSIGNMENT_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // boolean
            case 14:
                if (ch == '=') {
                    state = 15;
                    token.lexeme[i++] = ch;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = BOOLEAN_OP;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // boolean
            case 15:
                token.lexeme[i] = '\0';
                token.type = BOOLEAN_OP;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // logical
            case 16:
                token.lexeme[i] = '\0';
                token.type = LOGICAL_OP;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // {
            case 17:
                token.lexeme[i] = '\0';
                token.type = LEFT_CURLY;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // }
            case 18:
                token.lexeme[i] = '\0';
                token.type = RIGHT_CURLY;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // (
            case 19:
                token.lexeme[i] = '\0';
                token.type = LEFT_PAREN;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // )
            case 20:
                token.lexeme[i] = '\0';
                token.type = RIGHT_PAREN;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
                // [
            case 21:
                token.lexeme[i] = '\0';
                token.type = LEFT_BRACKET;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // ]
            case 22:
                token.lexeme[i] = '\0';
                token.type = RIGHT_PAREN;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // ;
            case 23:
                token.lexeme[i] = '\0';
                token.type = SEMICOLON;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // comment
            case 24:
                if (ch == '^') {
                    token.lexeme[i++] = ch;
                    state = 25;
                } else if (ch == '~') {
                    token.lexeme[i++] = ch;
                    state = 26;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // singe line comment
            case 25:
                if (ch != '\n' && (isalnum(ch) || ch == ' ' || ch == '\t' ||
                                   isincharset(ch))) {
                    token.lexeme[i++] = ch;
                    state = 25;
                } else if (ch == '\n') {
                    token.lexeme[i] = '\0';
                    token.type = SINGLE_COMM;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            // multi line comment
            case 26:
                if (ch == '~') {
                    token.lexeme[i++] = ch;
                    state = 27;
                } else if (isalnum(ch) || isspace(ch) ||
                           (isincharset(ch) && ch != '~')) {
                    token.lexeme[i++] = ch;
                    state = 26;
                } else {
                    token.lexeme[i++] = ch;
                    state = 1;
                }
                break;
            case 27:
                if (ch == '^') {
                    state = 28;
                    token.lexeme[i++] = ch;
                } else if (isalnum(ch) || isspace(ch) ||
                           (isincharset(ch) && ch != '^')) {
                    token.lexeme[i++] = ch;
                    state = 26;
                } else {
                    token.lexeme[i++] = ch;
                    state = 1;
                }
                break;
            case 28:
                token.lexeme[i] = '\0';
                token.type = MULTI_COMM;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // character
            case 37:
                token.lexeme[i] = '\0';
                token.type = SINGLE_QUOTE;
                state = 29;
                i = 0;
                ungetc(ch, inputFile);
                break;
            case 29:
                if (ch == ' ' || isalnum(ch) || isincharset(ch)) {
                    token.lexeme[i++] = ch;
                    state = 36;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 30:
                if (ch == '\'') {
                    token.lexeme[i++] = ch;
                    state = 31;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = UNKNOWN;
                    state = 0;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 36:
                token.lexeme[i] = '\0';
                token.type = CHAR;
                state = 30;
                i = 0;
                ungetc(ch, inputFile);
                break;
            case 31:
                token.lexeme[i] = '\0';
                token.type = SINGLE_QUOTE;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            // string
            case 38:
                token.lexeme[i] = '\0';
                token.type = DOUBLE_QUOTE;
                state = 32;
                i = 0;
                ungetc(ch, inputFile);
                break;
            case 32:
                if (isalnum(ch) || (isincharset(ch) && ch != '"') ||
                    ch == ' ' || ch == '\t') {
                    token.lexeme[i++] = ch;
                    state = 32;
                } else {
                    token.lexeme[i] = '\0';
                    token.type = STRING;
                    state = 33;
                    i = 0;
                    ungetc(ch, inputFile);
                }
                break;
            case 33:
                token.lexeme[i] = '\0';
                if (ch == '"') {
                    token.lexeme[i++] = ch;
                    state = 39;
                }
                break;
            case 39:
                token.lexeme[i] = '\0';
                token.type = DOUBLE_QUOTE;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            case 34:
                token.lexeme[i] = '\0';
                token.type = COMMA;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            case 35:
                token.lexeme[i] = '\0';
                token.type = AMP;
                state = 0;
                i = 0;
                ungetc(ch, inputFile);
                break;
            default:
                break;
        }
        if (token.type != EOF_TOKEN && token.type != UNKNOWN) {
            const char* typeString = tokenTypeToString(token.type);
            printf("%-20s%-10s\n", token.lexeme, typeString);
            strcpy(tokensArray[*tokenIndex].lexeme, token.lexeme);
            tokensArray[*tokenIndex].type = token.type;
            (*tokenIndex)++;
            fprintf(outputFile, "%-20s%-10s\n", token.lexeme, typeString);
            fflush(outputFile);
        }
    }
    if (i > 0) {
        token.lexeme[i] = '\0';
        const char* typeString = tokenTypeToString(token.type);
        printf("%-20s%-10s\n", token.lexeme, typeString);
        strcpy(tokensArray[*tokenIndex].lexeme, token.lexeme);
        tokensArray[*tokenIndex].type = token.type;
        (*tokenIndex)++;
        fprintf(outputFile, "%-20s%-10s\n", token.lexeme, typeString);
        fflush(outputFile);
    }
    printf("End of input.\n");
}