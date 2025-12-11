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
#include "lexer.hpp"

namespace CmpLgcalOperators{
    using namespace lexers;
    vector<string> cmp_list={
        "=",">","<","<=",">=","<>","!="
    };
    vector<string> logic_list={
        "AND","OR"
    };
    vector<string> arith_list={
        "+","-","*",R"(/)","%"
    };


    void check_ends(int current){
        if(current==tokens.size()){
            string message="Query incomplete ending at "+to_string(tokens[current-1].toke_position)+" column";
            throw runtime_error(message);
        }
    }

    pair<string,bool> is_valid_operator(int& current){
        // this funtion will check if operator is < AND
        string temp;
        temp.append(tokens[current].token_value);
        current++;
        // Parser::check_ends(current);
        check_ends(current);
        if((tokens[current].token_type==OPERATOR)){
            temp.append(tokens[current].token_value);
        }else{
            current--;
        }

        bool flag=false;
        for(string s:cmp_list){
            if(s==temp){
                flag=true;
            }
        }
        for(string s:logic_list){
            if(s==temp){
                flag=true;
            }
        }
        for(string s:arith_list){
            if(s==temp){
                flag=true;
            }
        }

        return pair<string,bool>(temp,flag);
    }
};
