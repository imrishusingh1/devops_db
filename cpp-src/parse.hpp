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
#include<vector>
#include "ttypes.hpp"
#include "lexer.hpp"
#include<string>
#include<unordered_map>
#include<stack>
#include "operatorValid.hpp"
#include "exprtree.hpp"




namespace parsers{
    using namespace lexers;

    static string message;


    namespace AST{
        class Base_AST{
            public:
            virtual void fun()=0;
            virtual ~Base_AST(){}
        };

        class DataBaseCreationstmt:Base_AST{
            void fun(){

            }
            public:
            string nameOfdatabase;
        };

        class TableColumnInfo{
            private:
            string column_name;
            string data_type;
            bool is_primary=false;

            public:
            TableColumnInfo(){

            }
            TableColumnInfo(const TableColumnInfo& t1){
                column_name=t1.column_name;
                data_type=t1.data_type;
                is_primary=t1.is_primary;
            }
            TableColumnInfo& operator=(const TableColumnInfo& t1){
                column_name=t1.column_name;
                data_type=t1.data_type;
                is_primary=t1.is_primary;

                return *this;
            }
            TableColumnInfo(TableColumnInfo&& t1){
                column_name=t1.column_name;
                data_type=t1.data_type;
                is_primary=t1.is_primary;

                t1.column_name.clear();
                t1.data_type.clear();
                t1.is_primary=false;
            }

            TableColumnInfo& operator=(TableColumnInfo&& t1){
                column_name=t1.column_name;
                data_type=t1.data_type;
                is_primary=t1.is_primary;

                t1.column_name.clear();
                t1.data_type.clear();
                t1.is_primary=false;
                return *this;
            }
            
            void setColumn_name(string column_name){
                this->column_name=column_name;
            }
            void setData_type(string data_type){
                this->data_type=data_type;
            }
            void setPrimary_key(bool flag){
                is_primary=flag;
            }
            const string& getColumn_name()const{
                return this->column_name;
            }
            const string& getData_type()const{
                return this->data_type;
            }
            bool is_primary_key()const{
                return this->is_primary;
            }
            void printInfo(){
                cout<<"Column Name: "<<getColumn_name()<<" | Data Type: "<<getData_type()<<" | is_Primary_key: "<<(is_primary)<<endl;
            }
        };

        class TableCreationstmt:Base_AST{
            void fun(){}
            public:
            string table_name;
            vector<TableColumnInfo> column_list_Info;
        };

        class Dropstmt:Base_AST{
            void fun(){}
            public:
            string _name;
            bool is_table=false;
        };

        class DataInsertstmt:Base_AST{
            void fun(){}
            public:
            string table_name;
            vector<string> column_list;
            map<int, vector<string>> value_list;
        };


        class DeleteTablestmt:Base_AST{
            void fun(){}
            public:
            string table_name;
            node* expressionTreess=nullptr;
        };

        class SelectTablestmt:Base_AST{
            void fun(){}
            public:
            string table_name;
            vector<string> column_list;
            bool to_select_all=false;
            node* expressionTreess=nullptr;
            map<string,string> column_for_sorting;
        };

        class UpdateTablestmt:Base_AST{
            void fun(){}
            public:
            string table_name;
            vector<pair<string,string>> columns_and_values;//////////
            node* expressionTreess=nullptr;
        };
        class UseDataBasestmt:Base_AST{
            void fun(){}
            public:
            string db_name;
        };









        static DataBaseCreationstmt ASTs_db_creation;
        static TableCreationstmt ASTs_table_creation;
        static Dropstmt ASTs_drop;
        static DataInsertstmt ASTs_insert_data;
        static DeleteTablestmt ASTs_delete_data;
        static SelectTablestmt ASTs_select_data;
        static UpdateTablestmt ASTs_update_data;
        static UseDataBasestmt ASTs_use_db;

        void flush_ASTS(){
            /////////////////  DatabaseCreationastm
            ASTs_db_creation.nameOfdatabase.clear();

            //////////////////// ASTs_table_creation//////
            ASTs_table_creation.column_list_Info.clear();
            ASTs_table_creation.table_name.clear();
            ////////////////// ASts_drop//////////////
            ASTs_drop.is_table=false;
            ASTs_drop._name.clear();
            ////////////// ASTs_insert_data/////
            ASTs_insert_data.column_list.clear();
            ASTs_insert_data.table_name.clear();
            ASTs_insert_data.value_list.clear();
            //////////// ASTs_delete_data////////////////////
            ASTs_delete_data.expressionTreess=nullptr;
            ASTs_delete_data.table_name.clear();
            /////////////// ASTs_select_data ////////////////////////
            ASTs_select_data.column_for_sorting.clear();
            ASTs_select_data.column_list.clear();
            ASTs_select_data.expressionTreess=nullptr;
            ASTs_select_data.table_name.clear();
            ASTs_select_data.to_select_all=false;
            /////////////////// ASTs_update_data////////
            ASTs_update_data.columns_and_values.clear();
            ASTs_update_data.expressionTreess=nullptr;
            ASTs_update_data.table_name.clear();
            ////////////ASTs_update_data;////////
            ASTs_use_db.db_name.clear();
        }
        

    };  

    // namespace CmpLgcalOperators{
    //     using namespace lexers;
    //     vector<string> cmp_list={
    //         "=",">","<","<=",">=","<>","!="
    //     };
    //     vector<string> logic_list={
    //         "AND","OR"
    //     };
    //     vector<string> arith_list={
    //         "+","-","*",R"(/)","%"
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
    //         for(string s:arith_list){
    //             if(s==temp){
    //                 flag=true;
    //             }
    //         }

    //         return pair<string,bool>(temp,flag);
    //     }
    // };


    namespace brackets{
        static stack<string> buffer;

        unordered_map<string,string> _bracketlist={
            {"(",")"},
            {"{","}"},
            {"[","]"}
        };
        void flush_buffer(){
            //////////////////////////////////
            while(!buffer.empty()){
                buffer.pop();
            }

        }

        bool is_left_bracket(string str){
            return _bracketlist.count(str);
        }
        bool is_right_bracket(string str){
            for(pair<string,string> p:_bracketlist){
                if(p.second==str){
                    return true;
                }
            }
            return false;
        }

        void is_balanced_bracket(int current){

            if(is_left_bracket(tokens[current].token_value)){
                buffer.push(tokens[current].token_value);
            }else if(is_right_bracket(tokens[current].token_value)){
                
                if(buffer.empty()){
                    message="invalid use of paranthesis ')' "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }else{
                    if(_bracketlist[buffer.top()]==tokens[current].token_value){
                        buffer.pop();
                    }
                }
            }
            
        }
        bool is_buffer_empty(){
            return buffer.empty();
        }
    };  

    namespace data_type_list{
        vector<string> _data_list={
            "INT", "FLOAT", "DECIMAL", "AUDIO",
            "VIDEO", "FLOAT", "BOOL","IMAGE",
            "VARCHAR"
        };
        bool is_data_type(int current){
            for(string s:_data_list){
                if(s==tokens[current].token_value){
                    return true;
                }
            }
            return false;
        }
    };



    
    class Parser{
        public:
        static void check_end(int current){

            if(current==tokens.size()){
                message="query incomplete at "+to_string(tokens[current-1].toke_position)+" column";
                throw runtime_error(message);
            }
        }


        static void ParseDataBaseCreation(){
            int current=0;
            // CREATE DATABASE company_db;

            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="CREATE")){
                message="expecting keyword-> 'CREATE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="DATABASE")){
                message="expecting keyword->'DATABASE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting identifier at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            AST::ASTs_db_creation.nameOfdatabase=tokens[current].token_value;//////////// database name assinged
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            
            if(!(tokens[current].token_type==TERMINATOR)){
                message="exepcting terminator ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            // check_end(current);
            if(current!=tokens.size()){
                message="Query ending at "+to_string(tokens[current-1].toke_position)+" column";
                throw runtime_error(message);
            }
            cout<<"Verified successfully"<<endl;

        }

        static void ParseUseDataBase(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="USE")){
                message="expecting keyword->'USE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting database name at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            AST::ASTs_use_db.db_name=tokens[current].token_value;
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;

            if(current!=tokens.size()){
                message="Query is ending at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            cout<<"verified successfully"<<endl;
        }

        /*
        CREATE TABLE customers (
            customer_id INT PRIMARY KEY,
            first_name VARCHAR(50),
            last_name VARCHAR(50),
            cgpa DECIMAL(10,2),
            phone_number VARCHAR(15)
        );  
        
        
        
        */

        static void ParseTableCreation(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // CREATE
            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="CREATE")){
                message="expecting keyword->'CREATE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // TABLE
            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="TABLE")){
                message="expecting keyword->'TABLE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // table_name
            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting table name at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            AST::ASTs_table_creation.table_name=tokens[current].token_value;///////////////////TABLE NAME HAS BEEN SET HERE///////////////////////////////
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            /*
            CREATE TABLE customers (
                customer_id INT PRIMARY KEY,
                first_name VARCHAR ( 50 )  PRIMARY KEY,
                marks DECIMAL ( 10 , 2 ),
                cgpa DECIMAL(10,2),
                phone_number VARCHAR(15)
            );  
            
            
            
            */
            //  must be (
            if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // now parse the list of column name along with datatype
            int col_index=0;
            bool is_primary_key_selected=false;
            while(true){
                AST::ASTs_table_creation.column_list_Info.push_back(AST::TableColumnInfo());////////EMPTY ROW INSERTED

                if(!(tokens[current].token_type==IDENTIFIER)){
                    message="expecting identifer at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                // AST::ASTs_table_creation.column_list_Info.push_back({tokens[current].token_value,"N/A"});
                AST::ASTs_table_creation.column_list_Info[col_index].setColumn_name(tokens[current].token_value);///////// COLUMN NAME SET HERE///////////
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                // INT, FLOAT, DECIMAL, AUDIO, VIDEO, FLOAT, BOOL,IMAGE, VARCHAR
                // spacial case varchar decimal to handle
                if(!(tokens[current].token_type==KEYWORD && data_type_list::is_data_type(current))){
                    message="expecting datatype keyword at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                string temp_type=tokens[current].token_value;/////////////////////////////////////////////////////////////////////////////////
                if(tokens[current].token_value=="VARCHAR"){
                    // first_name VARCHAR ( 50 )  PRIMARY KEY,
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }   

                    if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                        message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);//////////////// ( HAS BEEN SET HERE///////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==NUMBER && ((int)mathsConvoter::toDigit(tokens[current].token_value).first==mathsConvoter::toDigit(tokens[current].token_value).first) )){
                        message="expecting a number->integer value at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);///////////////////////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")")){
                        message="expecting ')' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);////////////////////////////////////////////////////////////////////////////////////

                }else if(tokens[current].token_value=="DECIMAL"){
                    // fmarks DECIMAL ( 10 , 2 ) PRIMARY KEY,
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }   

                    if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                        message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);/////////////////////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==NUMBER && ((int)mathsConvoter::toDigit(tokens[current].token_value).first==mathsConvoter::toDigit(tokens[current].token_value).first) )){
                        message="expecting a number->integer value at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);//////////////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==",")){
                        message="expecting a punctuation ',' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);////////////////////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==NUMBER && ((int)mathsConvoter::toDigit(tokens[current].token_value).first==mathsConvoter::toDigit(tokens[current].token_value).first) )){
                        message="expecting a number->integer value at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);//////////////////////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }


                    if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")")){
                        message="expecting ')' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_type.append(tokens[current].token_value);//////////////////////////////////////////////////////////////////////////////////

                }

                AST::ASTs_table_creation.column_list_Info[col_index].setData_type(temp_type);///////////////////DATA TYPE SATED HERE ///////////
                ///////////////////DATA TYPE VERIFICATION DONE TILL HERE//////////////////////
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                // here primary key is optional
                if(tokens[current].token_type==KEYWORD && !(tokens[current].token_value=="PRIMARY")){
                    message="expecting valid keyword 'PRIMARY' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                if(tokens[current].token_type==KEYWORD && tokens[current].token_value=="PRIMARY" && is_primary_key_selected==true){
                    message="primary key cant be more than one Error: at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                
                if(tokens[current].token_type==KEYWORD && tokens[current].token_value=="PRIMARY"){
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                    if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="KEY")){
                        message="expecting valid keyword 'KEY' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    
                    AST::ASTs_table_creation.column_list_Info[col_index].setPrimary_key(true);///////////////////////PRIMARY KEY SETED/////////////
                    is_primary_key_selected=true;
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                }
                






                // here can be pucntuoaiuon ',' or paratheis 
                // if ) then break the loop
                if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="," || tokens[current].token_value==")"))){
                    message="expecting ',' or ')' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")"){
                    break;
                }else if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","){
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                    col_index++;
                }

            }
            // at this point of time we will be at )

            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;

            if(current!=tokens.size()){
                message="Query is ending at "+to_string(tokens[current-1].toke_position)+" column";
                throw runtime_error(message);
            }

            cout<<"varified succesfully"<<endl;

        }

        /*
        DROP TABLE employees;
        DROP DATABASE company_db;
        
        */

        static void ParseDrop(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="DROP")){
                message="expecting keyword->'DROP' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && (tokens[current].token_value=="TABLE" || tokens[current].token_value=="DATABASE"))){
                message="expecting keyword-> 'TABLE'  or 'DATABASE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_value=="TABLE"){
                /////////////////////put into ast
                AST::ASTs_drop.is_table=true;
            }else if(tokens[current].token_value=="DATABASE"){
                /////////////////////put into ast
                AST::ASTs_drop.is_table=false;
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting identifer at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message); 
            }
            AST::ASTs_drop._name=tokens[current].token_value;/////////////////////////table or database name set///////////////////

            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            current++;

            if(current!=tokens.size()){
                message="Query is ending at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            cout<<"verified successfully"<<endl;





            
        }

        static void ParseInsert(){
            /*
            INSERT INTO Employees (employee_id, first_name, last_name, salary)
            VALUES (
            (   ' Rishu  ' , 'Alice', 'Smith', 55000  )  ,
            (3, 'Bob', 'Johnson', 60000),
            (4, 'Eve', 'Davis', 45000));

            INSERT INTO Employees
            VALUES (
            ('Rishu', 'Alice', 'Smith', 55000),
            (3, 'Bob', 'Johnson', 60000),
            (4, 'Eve', 'Davis', 45000));
            

            
            ('Rishu', 'Alice', 'Smith', 55000),
            (3, 'Bob', 'Johnson', 60000),
            (4, 'Eve', 'Davis', 45000);
            
            */

            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="INSERT")){
                message="expecting keyword->'INSERT' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="INTO")){
                message="expecting keyword->'INTO' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting an identifer e.g table name  at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            AST::ASTs_insert_data.table_name=tokens[current].token_value;////////////////////////////TABLE NAME SETED HERE/////////////////////
            
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }


            // user can skip list of column
            ////////////////it is not mendatory section////////////////
            if(!((tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(" ) || (tokens[current].token_type==KEYWORD && tokens[current].token_value=="VALUES") )){
                message="expecting punctuation '(' or keyword->'VALUES' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value=="(")){
                message="expecting punctuation '('  at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message); 
            }
            if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="("){
                // then parse comple column list
                // (   employee_id , first_name, last_name, salary   )
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                // employee_id , first_name, last_name, salary   )
                // breaking condition is ')'
                while(true){
                    if(!(tokens[current].token_type==IDENTIFIER)){
                        message="expecting an identifer e.g column_name at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message); 
                    }
                    AST::ASTs_insert_data.column_list.push_back(tokens[current].token_value);
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    //////// now we can either get , or )
                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value==")" || tokens[current].token_value==","))){
                        message="expecting ',' or ')' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")"){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                        break;
                    }else if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }

                }
            }

            //// here we will be at VALUES
            ////////this is mendatory section
            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="VALUES")){
                message="expecting keyword->'VALUES' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            ///////// VALUES CHECKED DONE///////
            ///// here we can uencouter (
            // this is optional to use external bracket
            bool external_bracket_used=false;
            if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                message="expecting '(' at "+to_string(tokens[current].toke_position)+" column"; 
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }


            /*
            VALUES (
            ('Rishu', 'Alice', 'Smith', 55000),
            (3, 'Bob', 'Johnson', 60000),
            (4, 'Eve', 'Davis', 45000));
                
            */

            if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="("){
                external_bracket_used=true;
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
            }
            int row_index=0;
            while(true){
                // at this point of time we are 
                // in both case we will be at ' Rishu ' , 'Alice', 'Smith', 55000 ) , (  3, 'Bob', 'Johnson', 60000) , (4, 'Eve', 'Davis', 45000 ) ) ;

                // breaking condition of this loop is 

                while(true){
                    // loop breaking contiion is )
                    // 'Rishu' , 'Alice', 'Smith', 55000   inside this we will parse it

                    if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value=="\"" || tokens[current].token_value=="\'")){
                        message="expecting valid punction '\'' or '\"' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\"")){
                        // then parse comple string
                        // ' Rishu ' 
                        string temp_data;
                        temp_data.append(tokens[current].token_value);//////////////////////////////////////////////////
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                        if(!(tokens[current].token_type==STRINGLITERAL)){
                            message="expecting string literal at "+to_string(tokens[current].toke_position)+" column";
                            throw runtime_error(message);
                        }
                        // AST::ASTs_insert_data.value_list[row_index].push_back(tokens[current].token_value);///////////////////////////////
                        temp_data.append(tokens[current].token_value);///////////////////////////////////////
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }

                        if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\""))){
                            message="expecting valid puncation to end string at "+to_string(tokens[current].toke_position)+" column";
                            throw runtime_error(message);
                        }
                        temp_data.append(tokens[current].token_value);///////////////////////////////////////////////////////////////////
                        AST::ASTs_insert_data.value_list[row_index].push_back(temp_data);//////////////////////////////////////////////////////

                    }else if(!(tokens[current].token_type==NUMBER)){
                        message="expecting number at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }else if(tokens[current].token_type==NUMBER){
                        AST::ASTs_insert_data.value_list[row_index].push_back(tokens[current].token_value);
                    }

                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                    

                    // after value parsing we expect , or )
                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="," || tokens[current].token_value==")"))){
                        message="expecting valid punctuation ',' or ')' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_value==")"){
                        break;
                    }else if(tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }
                }
                // at this point of time we will always at )
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                // here we can encounter , or ) or ;
                // if bracket used we expect , or ) and break at )
                // if not used then we expect , or ; and break at ;
                if(external_bracket_used){
                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="," || tokens[current].token_value==")") )){
                        message="expecting ',' or ')' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_value==")"){
                        break;
                    }else if(tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                        if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                            message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                            throw runtime_error(message);
                        }
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }
                }else if(!external_bracket_used){
                    if(!((tokens[current].token_type==PUNCTUATION && tokens[current].token_value==",") || tokens[current].token_type==TERMINATOR) ){
                        message="expecting ',' or ';' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_value==";"){
                        break;
                    }else if(tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                        if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                            message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                            throw runtime_error(message);
                        }
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }
                }
                row_index++;




                // if(!((tokens[current].token_type==PUNCTUATION && ((tokens[current].token_value==")" && external_bracket_used==true) || (tokens[current].token_value==",") )) || (tokens[current].token_type==TERMINATOR) )){
                //     message="expecting valid puncuation or ';' at "+to_string(tokens[current].toke_position)+" column";
                //     throw runtime_error(message);
                // }
                // if((tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")" && external_bracket_used==true) || (tokens[current].token_type==TERMINATOR)){
                //     break;
                // }else if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","){
                //     // parse  till     , (  s
                //     current++;
                //     while(tokens[current].token_type==WHITESPACE){
                //         current++;
                //     }
                //     if(!(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="(")){
                //         message="expecting '(' at "+to_string(tokens[current].toke_position)+" column";
                //         throw runtime_error(message);
                //     }
                //     current++;
                //     while(tokens[current].token_type==WHITESPACE){
                //         current++;
                //     }

                // }
                // loop breaking condition is if->bracket used->) else -> ;
            }
            if(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value==")" && external_bracket_used==true)){
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
            }
            // at this point of time we will alwyas at ;

            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            
            if(current!=tokens.size()){
                message="Query ending at "+to_string(tokens[current-1].toke_position)+" column";
                throw runtime_error(message);
            }

            cout<<"verified succesfully"<<endl;            

        }

        static void parseExpression(int& current, bool is_keyword_allowed_at_end=false){
            // ('country' = 'USA' AND status = 'inactive')
            // OR (country = 'Canada' AND (status = 'inactive' OR status = 'pending'));

            // KEEP IN MIND THAT ON BOTH SIDE OF ANY OPERATOR, IDENTIFER OR VALUE IS ALLOWED
            // THERE IS NOT CONSTRAIN IN THAT
            //////////////////LETS START///////////

            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            while(true){
                if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value=="(" || tokens[current].token_value=="\'" || tokens[current].token_value=="\"" )){
                    message="expecting punctuation e.g '(' or '\'' or '\"' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }

                while(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="("){
                    brackets::is_balanced_bracket(current);
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                }

                if(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\"")){
                    // then parse complete string
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                    if(!(tokens[current].token_type==STRINGLITERAL)){
                        message="expecting string literal at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\""))){
                        message="expecting valid puncation to end string at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }

                }else if(!(tokens[current].token_type==NUMBER || tokens[current].token_type==IDENTIFIER)){
                    message="expecting number or stringliteral or identifier at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value==")")){
                    message="expecting valid punctuation  ')' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                while(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")"){
                    brackets::is_balanced_bracket(current);
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                }

                if(!(tokens[current].token_type==OPERATOR || tokens[current].token_type==TERMINATOR || (tokens[current].token_type==KEYWORD && (is_keyword_allowed_at_end==true) && (tokens[current].token_value=="ORDER" || tokens[current].token_value=="SORT")) )){
                    message="expecting operator or ';' or keyword if allowed... at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                if(tokens[current].token_type==TERMINATOR || (tokens[current].token_type==KEYWORD && (is_keyword_allowed_at_end==true) && (tokens[current].token_value=="ORDER" || tokens[current].token_value=="SORT"))){
                    break;   
                }else if(tokens[current].token_type==OPERATOR){
                    pair<string,bool> optr=CmpLgcalOperators::is_valid_operator(current);
                    if(!(optr.second)){
                        message="expecting valid operator at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                }









                /*
                // now check for operator
                if(!(tokens[current].token_type==OPERATOR)){
                    message="expecting operator at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                pair<string,bool> optr=CmpLgcalOperators::is_valid_operator(current);
                if(!(optr.second)){
                    message="invalid operator at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }

                current++;
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                }

                if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value=="(" || tokens[current].token_value=="\'" || tokens[current].token_value=="\"" )){
                    message="expecting punctuations e.g '(' or '\'' or '\"' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }

                while(tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="("){
                    brackets::is_balanced_bracket(current);
                    current++;
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                    }
                }

                if(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\"")){
                    // then parse complete string
                    current++;
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                    }
                    if(!(tokens[current].token_type==STRINGLITERAL)){
                        message="expecting string literal at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    current++;
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                    }

                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\""))){
                        message="expecting valid puncation to end string at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }

                }else if(!(tokens[current].token_type==NUMBER || tokens[current].token_type==IDENTIFIER)){
                    message="expecting number or stringliteral or identifier at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }


                current++;
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                }

                if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value==")")){
                    message="expecting valid punctuation  ')' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                while(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==")"){
                    brackets::is_balanced_bracket(current);
                    current++;
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                    }
                }

                // after the ) we expect either operator or ;
                if(!(tokens[current].token_type==OPERATOR || tokens[current].token_type==TERMINATOR)){
                    message="expecting operator or ';' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                if(tokens[current].token_type==TERMINATOR){
                    break;   
                }else if(tokens[current].token_type==OPERATOR){
                    pair<string,bool> optr=CmpLgcalOperators::is_valid_operator(current);
                    if(!(optr.second)){
                        message="expecting valid operator at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    current++;
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                    }
                }
                // if(tokens[current].token_type==TERMINATOR){
                //     break;
                // }else if(tokens[current])
                */
            }
            // cout<<brackets::buffer.size()<<endl;
            if(!brackets::buffer.empty()){
                message="expecting ')' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            cout<<"Expression verified successfully"<<endl;


        }


        static void ParseDelete(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            /*
            DELETE FROM employee WHERE (country = 'USA' AND status = 'inactive')
            OR (country = 'Canada' AND (status = 'inactive' OR status = 'pending'));

            DELETE FROM employees;
            */



            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="DELETE")){
                message="expecting keyword->'DELETE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="FROM")){
                message="expecting keyword-> 'FROM' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting identifer e.g table_name at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            AST::ASTs_delete_data.table_name=tokens[current].token_value;///////////////////TABLE NAME SETED HERE///////////////////////
            current++;
            check_end(current);
            
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // HERE TWO POSSIBLITY IS EITHER ; OR WHERE CLAUSE
            if(!((tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE") || (tokens[current].token_type==TERMINATOR) )){
                message="expecting ';' or 'WHERE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE"){
                /*
                DELETE FROM employee WHERE (country = 'USA' AND status = 'inactive')
                OR (country = 'Canada' AND (status = 'inactive' OR status = 'pending'));

                DELETE FROM employees;
                */

                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                // now call expression parser at this place
                /////////////// ///////////////////////////////////////////
                int begin_index=current;
                parseExpression(current);
                int end_index=current;
                //////////////////////////////////NOW CALL THE EXPRESSION TREE BUILDER AT/////////////////
                expretree::expEvaluation::infixTopostfix(begin_index,end_index);
                AST::ASTs_delete_data.expressionTreess=(expretree::expEvaluation::expTree);
            }

            cout<<endl<<"verified successfully"<<endl;            


            
        }
        static void ParseSelect(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            /*
            SELECT * FROM employees;
            
            SELECT first_name, last_name FROM employees;

            SELECT first_name, last_name
            FROM employees
            WHERE department = 'Sales';

            SELECT first_name, last_name, age
            FROM employees WHERE name="rishu"
            ORDER BY last_name ASC;

            SELECT first_name, last_name
            FROM employees
            ORDER BY last_name ASC;
            */

            // MENDATORY
            if(!(tokens[current].token_type==KEYWORD && (tokens[current].token_value=="SELECT" || tokens[current].token_value=="GET"))){
                message="expecting keyword->'SELECT' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // HERE CAN BE * or list_of_column_name

            if(!((tokens[current].token_type==OPERATOR && tokens[current].token_value=="*") || (tokens[current].token_type==IDENTIFIER))){
                message="expecting '*' or column_name at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_type==IDENTIFIER){
                // parse complete identifer list
                /*
                first_name  , last_name, age FROM
                */

                // BREAKING CONDITION IS FROM KEYWORD
                while(true){
                    if(!(tokens[current].token_type==IDENTIFIER)){
                        message="expecting identifer at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }

                    AST::ASTs_select_data.column_list.push_back(tokens[current].token_value);/////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    // here can encounter , or FROM
                    // if from then break the loop
                    if(!((tokens[current].token_type==KEYWORD && tokens[current].token_value=="FROM") || (tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","))){
                        message="expecting 'FROM' or ',' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_type==KEYWORD && tokens[current].token_value=="FROM"){
                        break;
                    }else if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }
                }

            }else if(tokens[current].token_type==OPERATOR){
                AST::ASTs_select_data.to_select_all=true;////////////////////////////////////////////////////
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
            }
            // at this point of time we will be at FROM in any case
            // once verify it
            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="FROM")){
                message="expecting keyword->'FROM' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            /*
            SELECT * FROM employees;
            
            SELECT first_name, last_name FROM employees;

            SELECT first_name, last_name
            FROM employees
            WHERE department = 'Sales';

            SELECT first_name, last_name, age
            FROM employees WHERE name="rishu"
            ORDER BY last_name ASC, first_name DESC;

            SELECT first_name, last_name
            FROM employees
            ORDER BY last_name ASC;
            */

            // now at this point of time we need table name
            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting table_name at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            AST::ASTs_select_data.table_name=tokens[current].token_value;///////////////////////////////////////////////////////////////
            current++;
            // cout<<"hi rishu"<<endl;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            // here we can encounter either ; or where or order
            if(!((tokens[current].token_type==KEYWORD && (tokens[current].token_value=="WHERE" || tokens[current].token_value=="ORDER")) || (tokens[current].token_type==TERMINATOR && tokens[current].token_value==";")    )){
                message="expecting e.g ';' or 'WHERE' or 'ORDER' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_type==TERMINATOR){
                // cout<<"hi rishu"<<endl;

                current++;
                // check_end(current);
                // while(tokens[current].token_type==WHITESPACE){
                //     current++;
                //     check_end(current);
                // }

                if(current!=tokens.size()){
                    message="Query ending at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                
                cout<<"verified successfully"<<endl;
                return;
            
            }else if(tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE"){
                // parse complete conditions
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                

                ///////////////////////// NOW CALL THE EXPRESSION PARSER///////////////////////
                int begin_index=current;
                parseExpression(current,true);
                int end_index=current;
                //////////////// NOW WE WILL CALL EXPRESSION TREE BUILDER HERE /////////////////////////////
                // expEvaluation::infixTopostfix(begin_index,end_index);
                expretree::expEvaluation::infixTopostfix(begin_index,end_index);
                AST::ASTs_select_data.expressionTreess=expretree::expEvaluation::expTree;/////////////////////////////////// tree set///////////
            }

            if((tokens[current].token_type==KEYWORD && !((tokens[current].token_value=="ORDER" || tokens[current].token_value=="SORT")))){
                message="expecting keyword 'ORDER' or 'SORT' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            if(tokens[current].token_type==KEYWORD && ((tokens[current].token_value=="ORDER" || tokens[current].token_value=="SORT"))){

                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                // cout<<"hi rishu"<<endl;

                // BY last_name ASC, first_name DESC;
                if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="BY")){
                    message="expecting keyword 'BY' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                // NOW PARSE THE LIST OF WAY OF SORTING WITH CONDITION
                // WAY OF SORTING IS MENDATORY TO PROVIDE ELSE ERROR
                while(true){
                    if(!(tokens[current].token_type==IDENTIFIER)){
                        message="expecting column name e.g identifer at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message); 
                    }
                    ///////////////////////////////////////////////////////////////
                    string temp_name=tokens[current].token_value; ////////////////////////// ///////////////

                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==KEYWORD && (tokens[current].token_value=="ASC" || tokens[current].token_value=="DESC" ))){
                        message="expecting way sorting e.g ASC OR DESC at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    AST::ASTs_select_data.column_for_sorting[temp_name]=tokens[current].token_value;/////////////////////////////////////// way of sorting set ////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    // HERE WE CAN ENCOUTNER EITHER , OR ;
                    // if ; then break the loop
                    if(!((tokens[current].token_type==PUNCTUATION && tokens[current].token_value=="," ) || (tokens[current].token_type==TERMINATOR) )){
                        message="expecting ',' or ';' at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    if(tokens[current].token_type==TERMINATOR){
                        break;
                    }else if(tokens[current].token_type==PUNCTUATION && tokens[current].token_value==","){
                        current++;
                        check_end(current);
                        while(tokens[current].token_type==WHITESPACE){
                            current++;
                            check_end(current);
                        }
                    }



                }



            }
            // at this point of time we will be at ;
            // verify it
            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;

            if(current!=tokens.size()){
                message="Query is ending at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            cout<<"verified successfully"<<endl;

            


        }

        static void ParseUpdate(){
            int current=0;
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            
            
            
            /*
            
            UPDATE employees
            SET status = 'Active';

            UPDATE table_name
            SET column1 = value1,
                column2 = value2,
                ...
            WHERE condition;

            */

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="UPDATE")){
                message="expecting keyword-> 'UPDATE' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==IDENTIFIER)){
                message="expecting identifier at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            AST::ASTs_update_data.table_name=tokens[current].token_value;///////////////////////////////table name seted here////////////
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }

            if(!(tokens[current].token_type==KEYWORD && tokens[current].token_value=="SET")){
                message="expecting keyword->'SET' at"+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }
            current++;
            check_end(current);
            while(tokens[current].token_type==WHITESPACE){
                current++;
                check_end(current);
            }
            /*
            
            UPDATE employees
            SET status = 'Active';

            UPDATE table_name
            SET column1 = value1,
                column2 = value2,
                ...
            WHERE condition;

            */

            //////////////NOW PARSE THE LIST OF DATA//////////////////
            while(true){
                if(!(tokens[current].token_type==IDENTIFIER)){
                    message="expecting identifier at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                string temp_name=tokens[current].token_value;////////////////////////////////////////////////////////////////////
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                if(!(tokens[current].token_type==OPERATOR && tokens[current].token_value=="=")){
                    message="expecting operator->'=' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                if(tokens[current].token_type==PUNCTUATION && !(tokens[current].token_value=="\"" || tokens[current].token_value=="\'")){
                    message="expecting valid puctuation '\"' '\'' "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }
                if(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\"" || tokens[current].token_value=="\'")){
                    string temp_data;
                    temp_data.append(tokens[current].token_value);///////////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                    if(!(tokens[current].token_type==STRINGLITERAL)){
                        message="expecting string literal at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    // AST::ASTs_update_data.columns_and_values[temp_name]=tokens[current].token_value;///////////////////////////////////////
                    temp_data.append(tokens[current].token_value);///////////////////////////////////////////////////////////////
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }

                    if(!(tokens[current].token_type==PUNCTUATION && (tokens[current].token_value=="\'" || tokens[current].token_value=="\""))){
                        message="expecting valid puncation to end string at "+to_string(tokens[current].toke_position)+" column";
                        throw runtime_error(message);
                    }
                    temp_data.append(tokens[current].token_value);/////////////////////////////////////////////////////////
                    // AST::ASTs_update_data.columns_and_values[temp_name]=temp_data;
                    AST::ASTs_update_data.columns_and_values.push_back(pair<string,string>(temp_name,temp_data));


                }else if(!(tokens[current].token_type==NUMBER)){
                    message="expecting number value at "+to_string(tokens[current].toke_position)+" colum";
                    throw runtime_error(message);
                }else if(tokens[current].token_type==NUMBER){
                    // AST::ASTs_update_data.columns_and_values[temp_name]=tokens[current].token_value;
                    AST::ASTs_update_data.columns_and_values.push_back(pair<string,string>(temp_name,tokens[current].token_value));

                }
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }
                /*
                
                UPDATE employees
                SET status = 'Active';

                UPDATE table_name
                SET column1 = value1,
                    column2 = value2,
                    ...
                WHERE condition;

                */

                ///HERE WE CAN ENCOUNTER , or ; or where
                // if ; or where then break the

                if(!( (tokens[current].token_type==PUNCTUATION && tokens[current].token_value==",") || (tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE") || (tokens[current].token_type==TERMINATOR)   )){
                    message="expecting valid e.g , or ; or keyword->'WHERE' at "+to_string(tokens[current].toke_position)+" column";
                    throw runtime_error(message);
                }

                if((tokens[current].token_type==PUNCTUATION && tokens[current].token_value==",")){
                    current++;
                    check_end(current);
                    while(tokens[current].token_type==WHITESPACE){
                        current++;
                        check_end(current);
                    }
                }else if((tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE") || (tokens[current].token_type==TERMINATOR)){
                    break;
                }


            }

            /////// at this point of time we can be either at where or ;

            if((tokens[current].token_type==KEYWORD && tokens[current].token_value=="WHERE")){
                current++;
                check_end(current);
                while(tokens[current].token_type==WHITESPACE){
                    current++;
                    check_end(current);
                }

                /////////// now send the data for expression parsing/////////
                int begin_index=current;
                parseExpression(current);
                int end_index=current;
                expretree::expEvaluation::infixTopostfix(begin_index,end_index);
                AST::ASTs_update_data.expressionTreess=(expretree::expEvaluation::expTree);/////////////////////////////////////////////////////
            }


            ////////////// HERE WE WILL ALWAYS AT ; //////////////////////////////////
            if(!(tokens[current].token_type==TERMINATOR)){
                message="expecting ';' at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }

            current++;
            if(current!=tokens.size()){
                message="Query is ending at "+to_string(tokens[current].toke_position)+" column";
                throw runtime_error(message);
            }


            cout<<endl<<"verified successfully"<<endl;


















        }
    };
};


