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
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<map>
// #include "ExpressionTree.cpp"
#include "ttypes.hpp"


// enum tokentype{
//     KEYWORD,//0
//     IDENTIFIER,//1
//     OPERATOR,//2
//     NUMBER,//3
//     STRINGLITERAL,//4
//     PUNCTUATION,//5
//     WHITESPACE,//6
//     TERMINATOR,//7
//     UNKNOW//8
// };
// class token{
//     public:
//     string token_value; // where select, insert etc.
//     tokentype token_type; // whther it is identifier or keyword
//     int toke_position;
// };
namespace lexers{

    namespace mathsConvoter{
        map<char,int> _digits={
            {'0',0},{'1',1},{'2',2},
            {'3',3},{'4',4},{'5',5},
            {'6',6},{'7',7},{'8',8},
            {'9',9}
        };
        auto power=[](int x, int y){
            int temp=x;
            if(y==0){
                return 1;
            }
            for(int i=1; i<y; i++){
                temp=temp*x;
            }
            return temp;
        };

        pair<float,bool> toDigit(string str){
            if(str.find(".")==string::npos){
                if(str[0]=='-'){
                    // negative value
                    int num=0;
                    int pos=str.size()-2;
                    for(int i=1; i<str.size(); i++,pos--){
                        num+=_digits[str[i]]*(power(10,pos));
                    }

                    return pair<float,bool>((float)(-num),true);
                }else{
                    // positive value
                    int num=0;
                    int pos=str.size()-1;
                    for(int i=0; i<str.size(); i++,pos--){
                        num+=_digits[str[i]]*(power(10,pos));
                    }

                    return pair<float,bool>((float)num,true);

                }
            }else{
                // means it is a floating value
                if(str[0]=='-'){
                    // negative value
                    stringstream ss(str);
                    string temp;
                    string str1;

                    int i=0;
                    int digit_dec=0;
                    while(getline(ss,temp,'.')){
                        if(i==0){
                            str1.append(temp);
                            i++;
                        }else{
                            str1.append(temp);
                            digit_dec=temp.size();
                        }
                    }

                    int num1=0;
                    int pos1=str1.size()-2;
                    for(int i=1; i<str1.size(); i++,pos1--){
                        // cnt1++;
                        num1+=_digits[str1[i]]*(power(10,pos1));
                    }

                    float finalnum=(-((float)num1/(float)power(10,digit_dec)));

                    return pair<float,bool>(finalnum,true);
                }else{
                    // positive value
                    stringstream ss(str);
                    string temp;
                    string str1;

                    int i=0;
                    int digit_dec=0;
                    while(getline(ss,temp,'.')){
                        if(i==0){
                            str1.append(temp);
                            i++;
                        }else{
                            str1.append(temp);
                            digit_dec=temp.size();
                        }
                    }
                    
                    int num1=0;
                    int pos1=str1.size()-1;
                    for(int i=0; i<str1.size(); i++,pos1--){
                        // cnt1++;
                        num1+=_digits[str1[i]]*(power(10,pos1));
                    }

                    float finalnum=(((float)num1/(float)power(10,digit_dec)));

                    return pair<float,bool>(finalnum,true);

                }
            }
            return pair<float,bool>((float)0,false);
        }
    };

    namespace checkList{
        vector<string> __keywords={
            "CREATE","DATABASE","TABLE","INSERT",
            "INTO","SELECT","UPDATE","DELETE","ALTER","DROP","TRUNCATE","RENAME",
            "WHERE","ORDER","BY","VALUES","PRIMARY","KEY","VARCHAR",
            "FLOAT","BOOL","IMAGE","NUMBER","INT","DECIMAL","VIDEO","AUDIO",
            "FROM","GET","PUT",
            "REPLACE","SORT","ASC","DESC","SET","USE"
        };

        vector<string> __operators={
            "+","-","*","/","=",
            "<",">",
            "!","%"
            "NOT",
            "AND","OR","IN","BETWEEN"
        };

        vector<string> __punctuation={
            "(",")",",","\"","\'"
        };
        bool is_Keyword(string str){
            for(const string& str1:__keywords){
                if(str1==str){
                    return true;
                }
            }        
            return false;
        }
        bool is_operator(string str){
            for(const string& str1:__operators){
                if(str1==str){
                    return true;
                }
            }
            return false;
        }
        bool is_number(string str){
            for(const char ch:str){
                if(isalpha(ch)){
                    return false;
                }
            }
            return mathsConvoter::toDigit(str).second;
        }
        bool is_number(char ch){
            string str;
            str.push_back(ch);
            for(const char ch:str){
                if(isalpha(ch)){
                    return false;
                }
            }
            return mathsConvoter::toDigit(str).second;
        }
        bool is_operator(char ch){
            string str;
            str.push_back(ch);
            for(const string& str1:__operators){
                if(str1==str){
                    return true;
                }
            }
            return false;
        }
        bool is_punctuation(string str){
            for(const string& str1:__punctuation){
                if(str==str1){
                    return true;
                }
            }
            return false;
        }
        bool is_punctuation(char ch){
            string str;
            str.push_back(ch);
            for(const string& str1:__punctuation){
                if(str==str1){
                    return true;
                }
            }
            return false;
        }
        bool is_identifier(string str){
            if(str.empty()){
                return false;
            }
            if(!(str[0]=='_' || isalpha(str[0]))){
                return false;
            }
            for(int i=1; i<str.size(); i++){
                if(!(isalpha(str[i]) || isdigit(str[i]) || str[i]=='_')){
                    return false;
                }
            }
            return true;
        }
        bool is_identifier(char ch){
            string str;
            str.push_back(ch);
            if(!(str[0]=='_' || isalpha(str[0]))){
                return false;
            }
            for(int i=1; i<str.size(); i++){
                if(!(isalpha(str[i]) || isdigit(str[i]) || str[i]=='_')){
                    return false;
                }
            }
            return true;
        }
    };


    namespace strings{
        vector<string> split(string str, char dlmtr){
            stringstream ss(str);
            string word;
            vector<string> temp;
            while(getline(ss,word,dlmtr)){
                temp.push_back(word);
            }
            return temp;
        }

    };


    /*
    CREATE DATABASE mydb;

    */
    static vector<token> tokens;
    void tokenizer(string query){
        using namespace checkList;
        // Covert query to uppercase;
        {
            int i=-1;
            for(const char ch:query){
                query[++i]=toupper(ch);
            }
        }
        int start_token=0;
        int last_token=0;
        string str=query;
        bool literal_start=false;
        char literat_start_punct;
        while(last_token < query.size()){
            // substring before encounter checking
            while(last_token < query.size()  && literal_start==false && str[last_token]!=';' && str[last_token]!=' ' && !is_punctuation(str[last_token]) && !is_operator(str[last_token])){
                last_token++;
            }
            if(literal_start){
                while(str[last_token]!=literat_start_punct && last_token < query.size()){
                    last_token++;
                }
                token t;
                t.toke_position=start_token;
                t.token_type=tokentype::STRINGLITERAL;
                t.token_value=str.substr(start_token,last_token-start_token);
                tokens.push_back(t);
            }

            if(start_token!=last_token && literal_start==false){
                if(is_Keyword(str.substr(start_token,last_token-start_token))){
                    token t;
                    t.toke_position=start_token;
                    t.token_type=tokentype::KEYWORD;
                    t.token_value=str.substr(start_token,last_token-start_token);
                    tokens.push_back(t);
                }else if(is_operator(str.substr(start_token,last_token-start_token))){
                    token t;
                    t.toke_position=start_token;
                    t.token_type=tokentype::OPERATOR;
                    t.token_value=str.substr(start_token,last_token-start_token);
                    tokens.push_back(t);
                }else if(is_identifier(str.substr(start_token,last_token-start_token))){
                    token t;
                    t.toke_position=start_token;
                    t.token_type=tokentype::IDENTIFIER;
                    t.token_value=str.substr(start_token,last_token-start_token);
                    tokens.push_back(t);
                }else if(is_number(str.substr(start_token,last_token-start_token))){
                    token t;
                    t.toke_position=start_token;
                    t.token_type=tokentype::NUMBER;
                    t.token_value=str.substr(start_token,last_token-start_token);
                    tokens.push_back(t);
                }else{
                    token t;
                    t.toke_position=start_token;
                    t.token_type=tokentype::UNKNOW;
                    t.token_value=str.substr(start_token,last_token-start_token);
                    tokens.push_back(t);
                }
            }

            // last_token value checking
            if(last_token!=str.size()){

                if(is_operator(str[last_token])){
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::OPERATOR;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                }else if(is_punctuation(str[last_token])){
                    if((str[last_token]=='"' || str[last_token]=='\'') && literal_start==false){
                        literal_start=true;
                        literat_start_punct=str[last_token];
                    }else{
                        literal_start=false;
                    }
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::PUNCTUATION;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                }else if(str[last_token]==' '){
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::WHITESPACE;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                }else if(is_identifier(str[last_token])){
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::IDENTIFIER;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                }else if(str[last_token]==';'){
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::TERMINATOR;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                    // break;
                }else{
                    token t;
                    t.toke_position=last_token;
                    t.token_type=tokentype::UNKNOW;
                    string temp;
                    temp.push_back(str[last_token]);
                    t.token_value=temp;
                    tokens.push_back(t);
                }
            }

            start_token=(++last_token);
        }
    }
    void flush_tokens(){
        tokens.clear();
    }
    void printToken(){
        for(const token t:tokens){
            cout<<"token position: "<<t.toke_position<<" Token Type "<<t.token_type<<" Token Value: "<<(t.token_value==" "? "whitespace": t.token_value)<<endl;
        }
    }
    namespace sanitization{
        string sanitize(string str){
            
            for(size_t i=0; i<str.size(); i++){
                if(str[i]=='\n' || str[i]=='\t'){
                    str[i]=' ';
                }
            }
            return str;
        }
    };

};