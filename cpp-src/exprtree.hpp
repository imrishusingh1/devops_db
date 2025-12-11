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
#include<unordered_map>
#include<vector>
#include<stack>
#include<deque>
#include "ttypes.hpp"
#include "lexer.hpp"
// #include "parse.hpp"
#include "operatorValid.hpp"

namespace expretree{


    namespace _operator{
        class InfoOptr{
            public:
            int presedence;
            string associativity;
            string ctgry;
            InfoOptr(){

            }
            InfoOptr(int pre,string ass,string cat):presedence(pre),associativity(ass),ctgry(cat){

            }
            InfoOptr(const InfoOptr& obj){
                this->presedence=obj.presedence;
                this->associativity=obj.associativity;
                this->ctgry=obj.ctgry;
            }
            InfoOptr& operator=(const InfoOptr& obj){
                this->presedence=obj.presedence;
                this->associativity=obj.associativity;
                this->ctgry=obj.ctgry;
                return *this;
            }
        };

        unordered_map<string, InfoOptr> _operators={
            {"OR",InfoOptr(0,"L->R","LOGIC")},

            {"AND",InfoOptr(1,"L->R","LOGIC")},

            {"BETWEEN",InfoOptr(2,"L->R","CMP")},

            {"LIKE",InfoOptr(3,"L->R","CMP")},
            {"IN",InfoOptr(3,"L->R","CMP")},
            {"IS NULL",InfoOptr(3,"L->R","CMP")},

            {"=",InfoOptr(4,"L->R","CMP")},
            {"!=",InfoOptr(4,"L->R","CMP")},
            {"<>",InfoOptr(4,"L->R","CMP")},
            {"<",InfoOptr(4,"L->R","CMP")},
            {">",InfoOptr(4,"L->R","CMP")},
            {"<=",InfoOptr(4,"L->R","CMP")},
            {">=",InfoOptr(4,"L->R","CMP")},

            {"+",InfoOptr(5,"L->R","ARITH")},
            {"-",InfoOptr(5,"L->R","ARITH")},

            {"*",InfoOptr(6,"L->R","ARITH")},
            {"/",InfoOptr(6,"L->R","ARITH")},
            {"%",InfoOptr(6,"L->R","ARITH")},

            {"NOT",InfoOptr(7,"R->L","LOGIC")}
        };
        bool is_operator(string str){
            return _operator::_operators.count(str)!=0;
        }

        int preseOf(string str){
            return _operator::_operators[str].presedence;
        }
        string assocOf(string str){
            return _operator::_operators[str].associativity;
        }
        string ctgryOf(string str){
            return _operator::_operators[str].ctgry;
        }
    };
    // namespace CmpLgcalOperators{
    //     using namespace lexers;
    //     vector<string> cmp_list={
    //         "=",">","<","<=",">=","<>","!="
    //     };
    //     vector<string> logic_list{
    //         "AND","OR"
    //     };


    //     void check_ends(int current){
    //         if(current==tokens.size()){
    //             string message="Query incomplete ending at "+to_string(tokens[current-1].toke_position)+" column";
    //             throw runtime_error(message);
    //         }
    //     }

    //     pair<string,bool> is_valid_operator(int& current){
    //         // this funtion will check if operator is < AND
    //         string temp;
    //         temp.append(tokens[current].token_value);
    //         current++;
    //         // Parser::check_ends(current);
    //         check_ends(current);
    //         if((tokens[current].token_type==OPERATOR)){
    //             temp.append(tokens[current].token_value);
    //         }else{
    //             current--;
    //         }

    //         bool flag=false;
    //         for(string s:cmp_list){
    //             if(s==temp){
    //                 flag=true;
    //             }
    //         }
    //         for(string s:logic_list){
    //             if(s==temp){
    //                 flag=true;
    //             }
    //         }

    //         return pair<string,bool>(temp,flag);
    //     }
    // };
    namespace expEvaluation{
        // class node{
        //     public:
        //     node* left=nullptr;
        //     string valueAtnode;
        //     node* right=nullptr;
        //     node(){

        //     }
        //     node(string value):valueAtnode(value){
                
        //     }
        // };


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






        bool is_operator(string str){
            return _operator::_operators.count(str)!=0;
        }
        int preseOf(string str){
            return _operator::_operators[str].presedence;
        }
        string assocOf(string str){
            return _operator::_operators[str].associativity;
        }
        string ctgryOf(string str){
            return _operator::_operators[str].ctgry;
        }
        bool is_parathasis(string str){
            return str=="(" || str==")";
        }
        string string_type(char ch){
            string temp;
            temp.push_back(ch);
            return temp;
        }
        // void infixTopostfix(string str){
        //     stack<string> buffer;
        //     stack<string> output;


        //     int curr_index=0;

        //     while(curr_index< str.length()){
        //         if(str[curr_index]!=' '){

        //             if(is_operator(string_type(str[curr_index]))){
        //                 if( buffer.empty() || buffer.top()=="("){
        //                     buffer.push(string_type(str[curr_index]));
        //                 }else if(preseOf(buffer.top()) < preseOf(string_type(str[curr_index]))){
        //                     buffer.push(string_type(str[curr_index]));
        //                 }else{
        //                     while(!buffer.empty() && buffer.top()!="("){
        //                         if(preseOf(buffer.top()) > preseOf(string_type(str[curr_index]))){
        //                             output.push(buffer.top());
        //                             buffer.pop();
        //                         }else if( preseOf(buffer.top())==preseOf(string_type(str[curr_index])) && assocOf(string_type(str[curr_index]))=="L->R"){
        //                             output.push(buffer.top());
        //                             buffer.pop();
        //                         }else{
        //                             break;
        //                         }
        //                     }
        //                     buffer.push(string_type(str[curr_index]));
        //                 }
        //             }else if(is_parathasis(string_type(str[curr_index]))){
        //                 if(str[curr_index]=='('){
        //                     buffer.push(string_type(str[curr_index]));
        //                 }else{
        //                     while(!buffer.empty() && buffer.top()!="("){
        //                         output.push(buffer.top());
        //                         buffer.pop();
        //                     }
        //                 }
        //             }else{
        //                 // Identifer case
        //                 output.push(string_type(str[curr_index]));
        //             }
        //         }else if(str[curr_index]==' '){
        //             output.push(" ");
        //         }
        //         curr_index++;
        //     }
        //     string temp;
        //     while(!buffer.empty()){
        //         if(buffer.top()!="("){
        //             output.push(buffer.top());
        //         }
        //         buffer.pop();
        //     }
        //     while(!output.empty()){
        //         temp.append(output.top());
        //         output.pop();
        //     }

        //     for(int i=0, j=temp.size()-1; i<j; i++,j--){
            //         swap(temp[i],temp[j]);
            //     }
            //     cout<<temp<<endl;
        // }
        node* expTree=nullptr;
        deque<node*> tree_nodes;
        void buildTree(node* ptr){
            if(is_operator(ptr->valueAtnode)){
                node* leftchild=nullptr;
                node* rightchild=nullptr;

                // pop back last two node to merge
                rightchild=tree_nodes.back();
                tree_nodes.pop_back();
                leftchild=tree_nodes.back();
                tree_nodes.pop_back();

                ptr->right=rightchild;
                ptr->left=leftchild;

                tree_nodes.push_back(ptr);
            }else{
                tree_nodes.push_back(ptr);
            }
            expTree=tree_nodes.front();
        }

        void infixTopostfix(string str){
            stack<string> buffer;
            deque<string> output;


            int curr_index=0;

            while(curr_index< str.length()){
                if(str[curr_index]!=' '){

                    if(is_operator(string_type(str[curr_index]))){
                        if( buffer.empty() || buffer.top()=="("){
                            buffer.push(string_type(str[curr_index]));
                        }else if(preseOf(buffer.top()) < preseOf(string_type(str[curr_index]))){
                            buffer.push(string_type(str[curr_index]));
                        }else{
                            while(!buffer.empty() && buffer.top()!="("){
                                if(preseOf(buffer.top()) > preseOf(string_type(str[curr_index]))){
                                    output.push_back(buffer.top());
                                    buildTree(new node(buffer.top()));
                                    buffer.pop();
                                }else if( preseOf(buffer.top())==preseOf(string_type(str[curr_index])) && assocOf(string_type(str[curr_index]))=="L->R"){
                                    output.push_back(buffer.top());
                                    buildTree(new node(buffer.top()));
                                    buffer.pop();
                                }else{
                                    break;
                                }
                            }
                            buffer.push(string_type(str[curr_index]));
                        }
                    }else if(is_parathasis(string_type(str[curr_index]))){
                        if(str[curr_index]=='('){
                            buffer.push(string_type(str[curr_index]));
                        }else{
                            while(!buffer.empty() && buffer.top()!="("){
                                output.push_back(buffer.top());
                                buildTree(new node(buffer.top()));
                                buffer.pop();
                            }
                        }
                    }else{
                        // Identifer case
                        output.push_back(string_type(str[curr_index]));
                        buildTree(new node(string_type(str[curr_index])));
                    }
                }
                curr_index++;
            }
            string temp;
            while(!buffer.empty()){
                if(buffer.top()!="("){
                    output.push_back(buffer.top());
                    buildTree(new node(buffer.top()));
                }
                buffer.pop();
            }

            for(const string str1:output){
                cout<<str1<<" ";
            }
        }

        void infixTopostfix(int begin, int end){
            using lexers::tokens;
            stack<string> buffer;
            deque<string> output;

            int curr_index=begin;

            while(curr_index< end){
                if(!(tokens[curr_index].token_type==tokentype::WHITESPACE)){

                    if(tokens[curr_index].token_type==OPERATOR){
                        string tmp_optr=CmpLgcalOperators::is_valid_operator(curr_index).first;
                        // string tmp_optr;

                        if( buffer.empty() || buffer.top()=="("){
                            buffer.push(tmp_optr);
                        }else if(preseOf(buffer.top()) < preseOf(tmp_optr)){
                            buffer.push(tmp_optr);
                        }else{
                            while(!buffer.empty() && buffer.top()!="("){
                                if(preseOf(buffer.top()) > preseOf(tmp_optr)){
                                    output.push_back(buffer.top());
                                    buildTree(new node(buffer.top()));
                                    buffer.pop();
                                }else if( preseOf(buffer.top())==preseOf(tmp_optr) && assocOf(tmp_optr)=="L->R"){
                                    output.push_back(buffer.top());
                                    buildTree(new node(buffer.top()));
                                    buffer.pop();
                                }else{
                                    break;
                                }
                            }
                            if((!buffer.empty()) && (buffer.top()=="(")){
                                buffer.pop();
                            }
                            buffer.push(tmp_optr);
                        }
                    }else if(is_parathasis(tokens[curr_index].token_value)){
                        if(tokens[curr_index].token_value=="("){
                            buffer.push(tokens[curr_index].token_value);
                        }else{
                            while(!buffer.empty() && buffer.top()!="("){
                                output.push_back(buffer.top());
                                buildTree(new node(buffer.top()));
                                buffer.pop();
                            }
                        }
                    }else{
                        // Identifer case
                        if(tokens[curr_index].token_value=="\"" || tokens[curr_index].token_value=="'"){
                            string temp_data;
                            temp_data.append(tokens[curr_index].token_value);
                            curr_index++;
                            while(tokens[curr_index].token_type==WHITESPACE){
                                curr_index++;
                            }
                            if(tokens[curr_index].token_type==STRINGLITERAL){
                                temp_data.append(tokens[curr_index].token_value);
                            }
                            curr_index++;
                            while(tokens[curr_index].token_type==WHITESPACE){
                                curr_index++;
                            }
                            temp_data.append(tokens[curr_index].token_value);
                            output.push_back(temp_data);
                            buildTree(new node(temp_data));
                        }else{
                            output.push_back(tokens[curr_index].token_value);
                            buildTree(new node(tokens[curr_index].token_value));
                        }
                    }
                }
                curr_index++;
            }
            string temp;
            while(!buffer.empty()){
                if(buffer.top()!="("){
                    output.push_back(buffer.top());
                    buildTree(new node(buffer.top()));
                }
                buffer.pop();
            }

            for(const string str1:output){
                cout<<str1<<" ";
            }
        }
        


        void postOrder(node* root){
            if(root==nullptr){
                return;
            }
            postOrder(root->left);
            postOrder(root->right);
            cout<<root->valueAtnode<<" ";
        }

    }; 
};