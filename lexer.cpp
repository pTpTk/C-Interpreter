#include "lexer.h"

#define KEYWORD(X, Y) if(*idfrPtr == X) { \
                        tokens.emplace_back(Y, (long)idfrPtr); \
                        break; \
                    }

void Lexer::run(char* filename) {
    FILE* fd = fopen(filename, "r");

    if (!fd) {
        std::cerr << "unable to open file " << filename 
            << std::endl;
        assert(false);
    }

    char* token;

    char *line = (char*)calloc(256, sizeof(char));
    size_t size = 255;
    
    int len;

    while(len = getdelim(&line, &size, ' ', fd) > 0) {
        token = line;
        while(*token != ' ' && *token != '\0') {
            switch(*token) {
                case '\n':
                    ++token;
                    break;
                // symbols
                case '{':
                    PUSH_TOKEN(Type::symbol_brace_l);
                case '}': 
                    PUSH_TOKEN(Type::symbol_brace_r);
                case '(':
                    PUSH_TOKEN(Type::symbol_parenthesis_l);
                case ')':
                    PUSH_TOKEN(Type::symbol_parenthesis_r);
                case ';':
                    PUSH_TOKEN(Type::symbol_semicolon);
                case '=':
                {
                    if(*(token+1) == '=') {
                        tokens.emplace_back(Type::symbol_equal);
                        token += 2;
                        break;
                    }
                    PUSH_TOKEN(Type::symbol_assign);
                }
                case '-':
                    PUSH_TOKEN(Type::symbol_negation);
                case '~':
                    PUSH_TOKEN(Type::symbol_bit_complement);
                case '!':
                {
                    if(*(token+1) == '=') {
                        tokens.emplace_back(Type::symbol_not_equal);
                        token += 2;
                        break;
                    }
                    PUSH_TOKEN(Type::symbol_logical_negation);
                }
                    PUSH_TOKEN(Type::symbol_logical_negation);
                case '+':
                    PUSH_TOKEN(Type::symbol_addition);
                case '*':
                    PUSH_TOKEN(Type::symbol_multiplication);
                case '/':
                    PUSH_TOKEN(Type::symbol_division);
                case '&':
                {
                    if(*(token+1) == '&') {
                        tokens.emplace_back(Type::symbol_logical_and);
                        token += 2;
                        break;
                    }
                }
                case '|':
                {
                    if(*(token+1) == '|') {
                        tokens.emplace_back(Type::symbol_logical_or);
                        token += 2;
                        break;
                    }
                }
                case '<':
                {
                    if(*(token+1) == '=') {
                        tokens.emplace_back(Type::symbol_less_equal);
                        token += 2;
                        break;
                    }
                    PUSH_TOKEN(Type::symbol_less);
                }
                case '>':
                {
                    if(*(token+1) == '=') {
                        tokens.emplace_back(Type::symbol_greater_equal);
                        token += 2;
                        break;
                    }
                    PUSH_TOKEN(Type::symbol_greater);
                }
                case ':':
                    PUSH_TOKEN(Type::symbol_colon);
                case '?':
                    PUSH_TOKEN(Type::symbol_question_mark);
                case ',':
                    PUSH_TOKEN(Type::symbol_comma);

                // identifier
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
                case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
                case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
                case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q':
                case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
                case '_':
                {
                    int idfrLen = 0;
                    char* idfrStart = token;
                    while(isalpha(*token) || isdigit(*token) || (*token == '_')) {
                        ++idfrLen;
                        ++token;
                    }
                    std::string* idfrPtr = new std::string(idfrStart, idfrLen);
                    
                    KEYWORD("int", Type::keyword_int);
                    KEYWORD("return", Type::keyword_return);
                    KEYWORD("if", Type::keyword_if);
                    KEYWORD("else", Type::keyword_else);
                    KEYWORD("for", Type::keyword_for);
                    KEYWORD("do", Type::keyword_do);
                    KEYWORD("while", Type::keyword_while);
                    KEYWORD("break", Type::keyword_break);
                    KEYWORD("continue", Type::keyword_continue);

                    tokens.emplace_back(Type::identifier, (long)idfrPtr);
                    break;
                }
                // integer
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                {
                    int numLen = 0;
                    char* numStart = token;
                    while(isdigit(*token)) {
                        ++numLen;
                        ++token;
                    }
                    char* numStr = (char*)calloc(numLen+1, sizeof(char));
                    memcpy(numStr, numStart, numLen);
                    long num = atol(numStr);
                    free(numStr);
                    tokens.emplace_back(Type::integer, num);
                    break;
                }
                default:
                    printf("unrecongnized token \"%s\"\n", token);
                    assert(false);
            }
        }
    }

    free(line);
    fclose(fd);
}