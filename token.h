#pragma once

#include <cstdio>
#include <iostream>
#include <string>

enum class Type
{
    symbol_brace_l,
    symbol_brace_r,
    symbol_parenthesis_l,
    symbol_parenthesis_r,
    symbol_bracket_l,
    symbol_bracket_r,
    symbol_semicolon,
    symbol_equal,

    keyword_int,
    keyword_return,

    identifier,
    integer
};

enum class Keyword
{
    INT, RETURN
};

class Token
{
  public:
    Type type;
    long val;

    Token(Type _type, long _val = 0): type(_type), val(_val) {}
    
    void print()
    {
        switch(type) {
            case Type::symbol_brace_l:
                printf("{");
                break;
            case Type::symbol_brace_r: 
                printf("}");
                break;
            case Type::symbol_parenthesis_l: 
                printf("(");
                break;
            case Type::symbol_parenthesis_r: 
                printf(")");
                break;
            case Type::symbol_bracket_l: 
                printf("[");
                break;
            case Type::symbol_bracket_r: 
                printf("]");
                break;
            case Type::symbol_semicolon: 
                printf(";");
                break;
            case Type::symbol_equal: 
                printf("=");
                break;
            case Type::keyword_int:
                printf("int");
                break;
            case Type::keyword_return:
                printf("return");
                break;
            case Type::identifier:
            {
                std::string* strPtr = (std::string*)val;
                std::cout << *strPtr;
                break;
            }
            case Type::integer:
                printf("%ld", val);
                break;
        }
    }

};