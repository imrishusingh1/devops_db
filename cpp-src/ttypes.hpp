/*
 * myheader.h
 * Copyright (c) 2025 Rishu Kumar Singh
 *
 * This file was created as part of personal projects.
 * All rights reserved.
 *
 * You may not copy, modify, or distribute this file without
 * written permission from the author.
 */
#pragma once
#include<string>
enum tokentype{
    KEYWORD,//0
    IDENTIFIER,//1
    OPERATOR,//2
    NUMBER,//3
    STRINGLITERAL,//4
    PUNCTUATION,//5
    WHITESPACE,//6
    TERMINATOR,//7
    UNKNOW//8
};

class token{
    public:
    string token_value; // where select, insert etc.
    tokentype token_type; // whther it is identifier or keyword
    int toke_position;
};

namespace DataType{
    vector<string> Data_types_list={
        "VARCHAR", "FLOAT","BOOL","IMAGE","NUMBER","INT","DECIMAL","VIDEO","AUDIO"
    };

    bool is_Data_Type(string value){
        for(const string& val:Data_types_list){
            if(val==value){
                return true;
            }
        }
        return false;
    }
};


class node{
    public:
    node* left=nullptr;
    string valueAtnode;
    node* right=nullptr;
    node(){

    }
    node(string value):valueAtnode(value){
        
    }
};

