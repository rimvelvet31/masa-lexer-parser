#include "parser.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LEXEME_SIZE 256
#define MAX_CHILDREN 100

TreeNode* createProgramNode() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = PROGRAM_NODE;
    node->childCount = 0;
    return node;
}

TreeNode* createDeclarationNode() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = DECLARATION_NODE;
    node->childCount = 0;
    return node;
}

TreeNode* createDataTypeNode(const char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = DATA_TYPE_NODE;
    strcpy(node->value, value);
    node->childCount = 0;
    return node;
}

TreeNode* createIdentifierListNode() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = IDENTIFIER_LIST_NODE;
    node->childCount = 0;
    return node;
}

TreeNode* createIdentifierNode(const char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = IDENTIFIER_NODE;
    strcpy(node->value, value);
    node->childCount = 0;
    return node;
}

TreeNode* createAssignmentNode(const char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = ASSIGNMENT_NODE;
    strcpy(node->value, value);
    node->childCount = 0;
    return node;
}

TreeNode* createValueNode(const char* value, ValueType type) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = VALUE_NODE;
    node->valueType = type;
    strcpy(node->value, value);
    node->childCount = 0;
    return node;
}

TreeNode* createInputNode(TreeNode* identifierNode, TreeNode* dataTypeNode) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = INPUT_NODE;
    node->childCount = 0;

    // Create an ASSIGNMENT_NODE and add children
    TreeNode* assignmentNode = createAssignmentNode("=");
    addChild(assignmentNode, identifierNode);
    addChild(assignmentNode, dataTypeNode);

    // Add the ASSIGNMENT_NODE as a child to the INPUT_NODE
    addChild(node, assignmentNode);

    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->childCount <
        sizeof(parent->children) / sizeof(parent->children[0])) {
        parent->children[parent->childCount++] = child;
    }
}

void printSyntaxTree(TreeNode* root, int depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }

    switch (root->type) {
        case PROGRAM_NODE:
            printf("Program\n");
            break;
        case DECLARATION_NODE:
            printf("Declaration\n");
            break;
        case DATA_TYPE_NODE:
            printf("Data Type: %s\n", root->value);
            break;
        case IDENTIFIER_LIST_NODE:
            printf("Identifier List\n");
            break;
        case IDENTIFIER_NODE:
            printf("Identifier: %s\n", root->value);
            break;
        case ASSIGNMENT_NODE:
            printf("Assignment Operator: %s\n", root->value);
            break;
        case VALUE_NODE:
            printf("Value: %s\n", root->value);
            break;
        case OUTPUT_NODE:
            printf("Output Statement\n");
            break;
        case STRING_NODE:
            printf("String: %s\n", root->value);
            break;
        case INPUT_NODE:
            printf("Input Statement\n", root->value);
            break;

        default:
            fprintf(stderr, "Error: Unknown node type\n");
    }

    for (size_t i = 0; i < root->childCount; ++i) {
        printSyntaxTree(root->children[i], depth + 1);
    }
}

void freeSyntaxTree(TreeNode* root) {
    for (size_t i = 0; i < root->childCount; ++i) {
        freeSyntaxTree(root->children[i]);
    }

    free(root);
}

TreeNode* parseProgram(Token tokens[], int* currentIndex) {
    TreeNode* programNode = createProgramNode();

    while (tokens[*currentIndex].type != END_OF_INPUT) {
        TreeNode* statementNode = NULL;

        switch (tokens[*currentIndex].type) {
            case RESERVED_WORD:
                if (strcmp(tokens[*currentIndex].lexeme, "int") == 0 ||
                    strcmp(tokens[*currentIndex].lexeme, "des") == 0 ||
                    strcmp(tokens[*currentIndex].lexeme, "kar") == 0 ||
                    strcmp(tokens[*currentIndex].lexeme, "bool") == 0) {
                    statementNode = parseDeclaration(tokens, currentIndex);
                }
                break;
            case KEYWORD:
                if (strcmp(tokens[*currentIndex].lexeme, "ipakita") == 0) {
                    statementNode = parseOutputStatement(tokens, currentIndex);
                } else if (strcmp(tokens[*currentIndex].lexeme, "pasok") == 0) {
                    statementNode = parseInputStatement(tokens, currentIndex);
                }
                break;
            case IDENTIFIER:
                statementNode = parseAssignmentStatement(tokens, currentIndex);
                break;
            default:
                printError("Invalid statement", *currentIndex);
                break;
        }

        if (statementNode != NULL) {
            addChild(programNode, statementNode);
        } else {
            printf("Invalid statement");
            break;
        }
    }
    return programNode;
}

TreeNode* parseDeclaration(Token tokens[], int* currentIndex) {
    TreeNode* dataTypeNode = parseDataType(tokens, currentIndex);

    if (dataTypeNode) {
        TreeNode* identifierNode = parseIdentifier(tokens, currentIndex);

        if (tokens[*currentIndex].type == ASSIGNMENT_OP) {
            (*currentIndex)++;  // Consume the ASSIGNMENT_OP token

            const char* expectedType = NULL;

            if (strcmp(dataTypeNode->value, "kar") == 0) {
                expectedType = "CHAR";
            } else if (strcmp(dataTypeNode->value, "int") == 0) {
                expectedType = "INTEGER";
            } else if (strcmp(dataTypeNode->value, "des") == 0) {
                expectedType = "FLOAT";
            } else if (strcmp(dataTypeNode->value, "bool") == 0) {
                expectedType = "BOOL";
            }

            TreeNode* valueNode =
                parseValue(tokens, currentIndex, expectedType);

            if (valueNode) {
                TreeNode* assignmentNode = createAssignmentNode("=");
                addChild(assignmentNode, dataTypeNode);
                addChild(assignmentNode, identifierNode);
                addChild(assignmentNode, valueNode);

                if (tokens[*currentIndex].type == SEMICOLON) {
                    (*currentIndex)++;  // Consume the SEMICOLON token
                    return assignmentNode;
                } else {
                    printError("Missing semicolon", *currentIndex);
                    freeSyntaxTree(assignmentNode);
                    return NULL;
                }
            } else {
                printError("Invalid value", *currentIndex);
                freeSyntaxTree(dataTypeNode);
                freeSyntaxTree(identifierNode);
                return NULL;
            }
        } else {
            TreeNode* declarationNode = createDeclarationNode();
            addChild(declarationNode, dataTypeNode);
            addChild(declarationNode, identifierNode);

            while (tokens[*currentIndex].type == COMMA) {
                (*currentIndex)++;  // Consume the COMMA token
                TreeNode* nextIdentifierNode =
                    parseIdentifier(tokens, currentIndex);

                if (nextIdentifierNode) {
                    addChild(declarationNode, nextIdentifierNode);
                } else {
                    printError("Invalid identifier", *currentIndex);
                    freeSyntaxTree(declarationNode);
                    return NULL;
                }
            }

            if (tokens[*currentIndex].type == SEMICOLON) {
                (*currentIndex)++;  // Consume the SEMICOLON token
                return declarationNode;
            } else {
                printError("Missing semicolon", *currentIndex);
                freeSyntaxTree(declarationNode);
                return NULL;
            }
        }
    }
    return NULL;
}

TreeNode* parseAssignmentStatement(Token tokens[], int* currentIndex) {
    TreeNode* identifierNode = parseIdentifier(tokens, currentIndex);

    if (identifierNode) {
        if (tokens[*currentIndex].type == ASSIGNMENT_OP) {
            (*currentIndex)++;  // Consume the ASSIGNMENT_OP token

            TreeNode* valueNode = parseNextTokenAsValue(tokens, currentIndex);

            if (valueNode) {
                if (tokens[*currentIndex].type == SEMICOLON) {
                    (*currentIndex)++;  // Consume the SEMICOLON token
                    TreeNode* assignmentNode = createAssignmentNode("=");
                    addChild(assignmentNode, identifierNode);
                    addChild(assignmentNode, valueNode);
                    return assignmentNode;
                } else {
                    printError("Missing semicolon", *currentIndex);
                    freeSyntaxTree(identifierNode);
                    freeSyntaxTree(valueNode);
                    return NULL;
                }
            } else {
                printError("Invalid value", *currentIndex);
                freeSyntaxTree(identifierNode);
                return NULL;
            }
        } else {
            printError("Missing assignment operator", *currentIndex);
            freeSyntaxTree(identifierNode);
            return NULL;
        }
    }
    return NULL;
}

TreeNode* parseInputStatement(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == KEYWORD &&
        strcmp(tokens[*currentIndex].lexeme, "pasok") == 0) {
        (*currentIndex)++;  // Consume the 'pasok' token
        if (tokens[*currentIndex].type == LEFT_PAREN) {
            (*currentIndex)++;  // Consume the OPEN_PAREN token
            TreeNode* identifierNode = parseIdentifier(tokens, currentIndex);
            if (identifierNode) {
                if (tokens[*currentIndex].type == RIGHT_PAREN) {
                    (*currentIndex)++;  // Consume the CLOSE_PAREN token
                    if (tokens[*currentIndex].type == ASSIGNMENT_OP) {
                        (*currentIndex)++;  // Consume the ASSIGNMENT_OP
                        TreeNode* dataTypeNode =
                            parseDataType(tokens, currentIndex);
                        if (dataTypeNode) {
                            if (tokens[*currentIndex].type == SEMICOLON) {
                                (*currentIndex)++;  // Consume the SEMICOLON
                                                    // token
                                TreeNode* inputNode = createInputNode(
                                    identifierNode, dataTypeNode);
                                return inputNode;
                            } else {
                                printError("Missing semicolon", *currentIndex);
                                freeSyntaxTree(identifierNode);
                                freeSyntaxTree(dataTypeNode);
                                return NULL;
                            }
                        } else {
                            printError("Invalid data type", *currentIndex);
                            freeSyntaxTree(identifierNode);
                            return NULL;
                        }
                    } else {
                        printError("Missing assignment operator",
                                   *currentIndex);
                        freeSyntaxTree(identifierNode);
                        return NULL;
                    }
                } else {
                    printError("Missing closing parenthesis", *currentIndex);
                    freeSyntaxTree(identifierNode);
                    return NULL;
                }
            } else {
                printError("Invalid identifier", *currentIndex);
                return NULL;
            }
        } else {
            printError("Missing opening parenthesis", *currentIndex);
            return NULL;
        }
    }
    return NULL;
}

TreeNode* parseNextTokenAsValue(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == SINGLE_QUOTE) {
        (*currentIndex)++;  // Consume the SINGLE_QUOTE token

        if (tokens[*currentIndex].type == CHAR) {
            const char* charValue = tokens[*currentIndex].lexeme;
            (*currentIndex)++;  // Consume the CHAR token

            if (strlen(charValue) == 1) {
                TreeNode* valueNode = createValueNode(charValue, CHAR);

                if (tokens[*currentIndex].type == SINGLE_QUOTE) {
                    (*currentIndex)++;  // Consume the closing SINGLE_QUOTE
                                        // token
                    return valueNode;
                } else {
                    printError("Missing closing single quote", *currentIndex);
                    freeSyntaxTree(valueNode);
                    return NULL;
                }
            } else {
                printError("Invalid character value", *currentIndex);
                return NULL;
            }
        } else {
            printError("Invalid character value", *currentIndex);
            return NULL;
        }
    } else if (tokens[*currentIndex].type == CHAR) {
        const char* charValue = tokens[*currentIndex].lexeme;
        if (strlen(charValue) == 1) {
            TreeNode* valueNode = createValueNode(charValue, CHAR);
            (*currentIndex)++;  // Consume the CHAR token
            return valueNode;
        } else {
            printError("Invalid character value", *currentIndex);
            return NULL;
        }
    } else if (tokens[*currentIndex].type == INTEGER ||
               tokens[*currentIndex].type == FLOAT ||
               tokens[*currentIndex].type == RESERVED_WORD) {
        const char* valueLexeme = tokens[*currentIndex].lexeme;
        TreeNode* valueNode = createValueNode(
            valueLexeme, UNKNOWN);  // Use an UNKNOWN_TYPE or adjust as
        (*currentIndex)++;          // Consume the token
        return valueNode;
    } else {
        printError("Invalid value", *currentIndex);
        return NULL;
    }
}

TreeNode* parseDataType(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == RESERVED_WORD) {
        const char* dataTypeLexeme = tokens[*currentIndex].lexeme;
        if (strcmp(dataTypeLexeme, "int") == 0 ||
            strcmp(dataTypeLexeme, "des") == 0 ||
            strcmp(dataTypeLexeme, "kar") == 0 ||
            strcmp(dataTypeLexeme, "bool") == 0) {
            (*currentIndex)++;  // Consume the KEYWORD token
            TreeNode* dataTypeNode = createDataTypeNode(dataTypeLexeme);
            return dataTypeNode;
        } else {
            printError("Invalid data type", *currentIndex);
            return NULL;
        }
    }
}

TreeNode* parseIdentifierList(Token tokens[], int* currentIndex) {
    TreeNode* identifierListNode = createIdentifierListNode();
    TreeNode* identifierNode = parseIdentifier(tokens, currentIndex);
    if (identifierNode != NULL) {
        addChild(identifierListNode, identifierNode);
        while (tokens[*currentIndex].type == COMMA) {
            (*currentIndex)++;
            identifierNode = parseIdentifier(tokens, currentIndex);
            if (identifierNode != NULL) {
                addChild(identifierListNode, identifierNode);
            } else {
                printError("Invalid identifier", *currentIndex);
                break;
            }
        }
        return identifierListNode;
    }
    return NULL;
}

TreeNode* parseIdentifier(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == IDENTIFIER) {
        TreeNode* identifierNode =
            createIdentifierNode(tokens[*currentIndex].lexeme);
        (*currentIndex)++;
        return identifierNode;
    }
    return NULL;
}

TreeNode* parseValue(Token tokens[], int* currentIndex,
                     const char* expectedType) {
    if (tokens[*currentIndex].type == IDENTIFIER) {
        const char* identifierLexeme = tokens[*currentIndex].lexeme;
        TreeNode* valueNode =
            createValueNode(identifierLexeme, IDENTIFIER_NODE);
        (*currentIndex)++;
        return valueNode;
    } else if (tokens[*currentIndex].type == INTEGER ||
               tokens[*currentIndex].type == FLOAT ||
               tokens[*currentIndex].type == RESERVED_WORD) {
        const char* valueLexeme = tokens[*currentIndex].lexeme;
        if (strcmp(expectedType, "CHAR") == 0 &&
            tokens[*currentIndex].type == CHAR) {
            TreeNode* valueNode = createValueNode(valueLexeme, CHAR);
            (*currentIndex)++;
            return valueNode;
        } else if (strcmp(expectedType, "INTEGER") == 0 &&
                   tokens[*currentIndex].type == INTEGER) {
            TreeNode* valueNode = createValueNode(valueLexeme, INTEGER);
            (*currentIndex)++;
            return valueNode;
        } else if (strcmp(expectedType, "FLOAT") == 0 &&
                   tokens[*currentIndex].type == FLOAT) {
            TreeNode* valueNode = createValueNode(valueLexeme, FLOAT);
            (*currentIndex)++;
            return valueNode;
        } else if (strcmp(expectedType, "BOOL") == 0 &&
                   tokens[*currentIndex].type == RESERVED_WORD) {
            const char* boolValue = tokens[*currentIndex].lexeme;
            if (strcmp(boolValue, "tama") == 0 ||
                strcmp(boolValue, "mali") == 0) {
                TreeNode* valueNode = createValueNode(boolValue, BOOL_TYPE);
                (*currentIndex)++;
                return valueNode;
            } else {
                printError("Invalid boolean value", *currentIndex);
                return NULL;
            }
        } else {
            printError("Invalid value", *currentIndex);
            return NULL;
        }
    } else if (strcmp(expectedType, "CHAR") == 0 &&
               tokens[*currentIndex].type == SINGLE_QUOTE) {
        (*currentIndex)++;  // Consume the SINGLE_QUOTE token
        const char* charValue = tokens[*currentIndex].lexeme;
        if (strlen(charValue) == 1) {
            TreeNode* valueNode = createValueNode(charValue, CHAR);
            (*currentIndex)++;  // Consume the CHAR token
            if (tokens[*currentIndex].type == SINGLE_QUOTE) {
                (*currentIndex)++;  // Consume the closing SINGLE_QUOTE token
                return valueNode;
            } else {
                printError("Missing closing single quote", *currentIndex);
                freeSyntaxTree(valueNode);
                return NULL;
            }
        } else {
            printError("Invalid character value", *currentIndex);
            return NULL;
        }
    }
    return NULL;
}

TreeNode* parseOutputStatement(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == KEYWORD &&
        strcmp(tokens[*currentIndex].lexeme, "ipakita") == 0) {
        (*currentIndex)++;  // Consume the 'ipakita' token
        if (tokens[*currentIndex].type == LEFT_PAREN) {
            (*currentIndex)++;  // Consume the OPEN_PAREN token
            TreeNode* outputNode = createOutputNode();  // create output node
            TreeNode* firstNode = parseString(
                tokens, currentIndex);  // Parse the first string or identifier

            // If it's not a string, try parsing as an identifier
            if (!firstNode) {
                firstNode = parseIdentifier(tokens, currentIndex);
            }
            if (firstNode) {
                addChild(outputNode, firstNode);
                // Parse additional strings or identifiers separated by commas
                while (tokens[*currentIndex].type == COMMA) {
                    (*currentIndex)++;  // Consume the COMMA token
                    // Parse the next string or identifier
                    TreeNode* nextNode = parseString(tokens, currentIndex);
                    if (!nextNode) {
                        // If it's not a string, try parsing as an identifier
                        nextNode = parseIdentifier(tokens, currentIndex);
                    }
                    if (nextNode) {
                        addChild(outputNode, nextNode);
                    } else {
                        printError("Invalid string or identifier after comma",
                                   *currentIndex);
                        freeSyntaxTree(outputNode);
                        return NULL;
                    }
                }

                // Check for the closing parenthesis
                if (tokens[*currentIndex].type == RIGHT_PAREN) {
                    (*currentIndex)++;  // Consume the CLOSE_PAREN token
                    // Check for the semicolon
                    if (tokens[*currentIndex].type == SEMICOLON) {
                        (*currentIndex)++;  // Consume the SEMICOLON token
                        return outputNode;
                    } else {
                        printError("Missing semicolon", *currentIndex);
                        freeSyntaxTree(outputNode);
                        return NULL;
                    }
                } else {
                    printError("Missing closing parenthesis", *currentIndex);
                    freeSyntaxTree(outputNode);
                    return NULL;
                }
            } else {
                // Handle error or recovery logic if needed
                freeSyntaxTree(outputNode);
                return NULL;
            }
        } else {
            printError("Missing opening parenthesis", *currentIndex);
            return NULL;
        }
    }
    return NULL;  // Unable to parse an output statement
}

TreeNode* parseString(Token tokens[], int* currentIndex) {
    if (tokens[*currentIndex].type == DOUBLE_QUOTE) {
        (*currentIndex)++;  // Consume the DOUBLE_QUOTE token
        const char* stringLexeme = tokens[*currentIndex].lexeme;
        TreeNode* stringNode = createStringNode(stringLexeme);
        (*currentIndex)++;  // Consume the string token
        if (tokens[*currentIndex].type == DOUBLE_QUOTE) {
            (*currentIndex)++;  // Consume the closing DOUBLE_QUOTE token
            return stringNode;
        } else {
            printError("Missing closing double quote", *currentIndex);
            freeSyntaxTree(stringNode);
            return NULL;
        }
    } else {
        return NULL;
    }
}

TreeNode* createOutputNode() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = OUTPUT_NODE;
    node->childCount = 0;
    return node;
}

TreeNode* createStringNode(const char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = STRING_NODE;
    strcpy(node->value, value);
    node->childCount = 0;
    return node;
}

void printError(const char* message, int index) {
    printf("Error at index %d: %s\n", index, message);
}
