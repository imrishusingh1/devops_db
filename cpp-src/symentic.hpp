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
#include "ttypes.hpp"
#include "parse.hpp"
#include "lexer.hpp"
#include<filesystem>
namespace fs=filesystem;
namespace sementics{

    using namespace parsers::AST;

    
    




    // class checkListOfFiles{
    //     public:
    //     static bool is_database_exist(string database_name){

    //         if(fs::exists(root_folder+"/"+database_name)&& fs::is_directory(root_folder+"/"+database_name)){
    //             return true;
    //         }
    //         return false;
    //     }
    //     static bool is_table_exist(string table_name){
    //         string path=root_folder+"/"+data_base+"/"+table_name+".txt";
    //         if(fs::exists(path) && fs::is_regular_file(path)){

    //             return true;
    //         }
    //         return false;
    //     }
    // };
    static string database_path;

    class Analyse{

        public:

        static void CreateDatabaseAnalysis(){///////////////////CHECKED
            //////////////// CHECK if database exist or not/////////////////////
            string root_=R"(./data)";
            string _path=root_+"/"+(ASTs_db_creation.nameOfdatabase);
            if((fs::exists(_path) && fs::is_directory(_path))){
                throw runtime_error("Database "+(ASTs_db_creation.nameOfdatabase) +" Already exist!");
            }
        }
        static void UseDatabaseAnalysis(){//////////////////////CHECKED
            //////////////// CHECK if database exist /////////////////////
            string root_=R"(./data)";
            string _path=root_+"/"+(ASTs_use_db.db_name);
            database_path=_path;
            if(!(fs::exists(_path) && fs::is_directory(_path))){
                throw runtime_error("Database "+(ASTs_db_creation.nameOfdatabase) +" not exist!");
            }
            // cout<<_path<<endl;
            // cout<<(fs::exists(_path)  && fs::is_directory(_path))<<endl;
        }

        static void CreateTableAnalysis(){
            ///////////////////////CHECK IF TABLE EXIST////////////////////////
            
            string _path=database_path+"/"+(ASTs_table_creation.table_name)+".txt";

            if((fs::exists(_path) && fs::is_regular_file(_path))){
                throw runtime_error("Table "+(ASTs_table_creation.table_name) +" Already exist!");
            }

        }

        static void is_type_matching(string column_type, string value){
            if((value[0]=='\'' || value[0]=='\"' ) && (value[value.size()-1]=='\'' || value[value.size()-1]=='\"')){
                // that means it is string value;
                if(column_type.find("VARCHAR")!=string::npos){
                    // VARCHAR(50)

                    int being_index=column_type.find('(');
                    being_index++;

                    int end_index=column_type.find(')');

                    string size_of_varchar=column_type.substr(being_index,(end_index-being_index));
                    int size_=(int)(lexers::mathsConvoter::toDigit(size_of_varchar).first);

                    ////////////////// size of given value string must be less equal to size of varchar of table //////////////////////
                    int size_of_literal=value.size()-2;////////// we will not include ' or " becuse it will get trimmed out while storing FROM BOTH END 
                    if(size_of_literal>size_){
                        string message="Error: "+value+" size is greater than column size "+to_string(size_)+" !";
                        throw runtime_error(message);
                    }

                }else if((column_type.find("IMAGE")!=string::npos )|| (column_type.find("VIDEO")!=string::npos) || (column_type.find("AUDIO")!=string::npos) ){
                    //  then supported format is for image.png, video.mp4, audio.mp3
                    // if(column_type=="IMAGE"){
                    //     // then it must be png file
                    //     if(value.find_last_of(".png")){

                    //     }
                    // }
                    /////////////////////////////////// LEFT IT FOR NOW WE WILLL HANDLE THIS CASE IN UPCOMING VERSION SOON/////////////////////////
                    ///////////////////////// BECAUSE THIGNS IS NOT COMPATIBLE FOR HANDLING THE MULTIMEDIA FILE////////////////////////////

                }else{
                    string message="Error: "+value+" type is not matching with corresponding column type rishu1111 "+column_type;
                    throw runtime_error(message);
                }


            }else if(!((value[0]=='\'' || value[0]=='\"' ) && (value[value.size()-1]=='\'' || value[value.size()-1]=='\"'))){
                // it must be a number value
                // cout<<"Exectuing non string section chcker"<<endl;
                vector<string> list_numberic_type={
                    "INT","FLOAT","NUMBER"
                };
                bool flag=false;
                for(string s:list_numberic_type){
                    if(column_type==s){
                        flag=true;
                    }
                }
                /////////////// here we have to handle the speacial case that is DECIMAL(10,2)///////////////////////////////
                if(column_type.find("DECIMAL")!=string::npos){
                    cout<<"execting decimal section"<<endl;
                    /*

                    now fetch the 10,3 and match with the value non decmal and decimal part
                    
                    */

                    // feth 10,3 from column_type
                    int non_decimal_start=column_type.find("(");
                    non_decimal_start++;
                    int non_decimal_end=column_type.find(",");
                    int non_decimal_size=(int)(lexers::mathsConvoter::toDigit(column_type.substr(non_decimal_start,(non_decimal_end-non_decimal_start)))).first;
                    
                    
                    
                    
                    int decimal_start=(non_decimal_end+1);
                    int decimal_end=column_type.find(")");
                    int decimal_size=(int)(lexers::mathsConvoter::toDigit(column_type.substr(decimal_start,(decimal_end-decimal_start)))).first;

                    //////////////////////// now match the size/////////////////////////////////

                    stringstream strm(value);

                    string non_decimal;
                    string decimal;
                    getline(strm,non_decimal,'.');
                    getline(strm,decimal,' ');

                    cout<<"expected non decimal "<<non_decimal_size<<" getting "<<(non_decimal.size())<<endl;

                    if((non_decimal_size < non_decimal.size())){
                        string message="Error: non decimal type is not matching with column type!"+value;
                        throw runtime_error(message);
                    }
                    cout<<"expected decimal "<<decimal_size<<" getting "<<(decimal.size())<<endl;

                    if((decimal_size<decimal.size())){
                        string message="Error: decimal type is not matching with column type!"+value;
                        throw runtime_error(message);
                    }
                    
                    flag=true;                    
                }else if((column_type.find("INT")!=string::npos) || (column_type.find("NUMBER"))){
                    if(!((int)lexers::mathsConvoter::toDigit(value).first==lexers::mathsConvoter::toDigit(value).first ) ){
                        string message="Error: column expecting INT or NUMBERIC value and getting "+(value);
                        throw runtime_error(message);
                    }
                }

                if(flag==false){
                    string message="Error: "+value+" type is not matching with corresponding column type "+column_type;
                    throw runtime_error(message);
                }







            }
            // cout<<value<<" "<<value[0] <<(value[value.size()-1])<<"        "<<((value[0]=='\'' || value[0]=='\"' ) && (value[value.size()-1]=='\'' || value[value.size()-1]=='\"'))<<endl;
            cout<<"type checked succesfully"<<endl;

        }
        static vector<pair<string,string>> fetch_table_header_info(string table_name){
            string _path=database_path+"/"+(table_name)+".txt";
            ifstream fptr;
            cout<<database_path<<endl;
            fptr.open(_path,ios::in);
            if(!fptr){
                throw runtime_error("unexpected error !");

            }

            string header;
            getline(fptr,header);//////////header of table stored here

            // cout<<"header: "<<header<<endl;


            // unordered_map<string,string> column_details;
            vector<pair<string,string>> column_details;
            stringstream ss1(header);
            
            string word;
            while(getline(ss1,word,'|')){
                // cout<<word<<endl;
                // cout<<"hi";
                stringstream ss2(word);
                string name;
                string typess;
                ss2>>name;
                ss2>>typess;
                // cout<<name<<"=>"<<typess<<endl;
                column_details.push_back(pair<string,string>(name,typess));
            }

            return column_details;
        }


        static void InsertAnalysis(){
            /*
                check:
                if table exist////////////////////DONE
                if privided rows data matching the type of column of table//////////////////
                if match the number of column present in table and number of value provided by the user
                if not matching the throw error
            */
            string _path=database_path+"/"+(ASTs_insert_data.table_name)+".txt";

            cout<<_path<<endl;

            if(!(fs::exists(_path) && fs::is_regular_file(_path))){
                throw runtime_error("Table "+(ASTs_insert_data.table_name) +" not exist!");
            }

            // ifstream fptr;
            // fptr.open(_path,ios::in);
            // if(!fptr){
            //     throw runtime_error("unexpected error !");
            // }

            // string header;
            // getline(fptr,header);//////////header of table stored here


            
            // stringstream ss1(header);
            
            // string word;
            // while(getline(ss1,word,'|')){
            //     stringstream ss2(word);
            //     string name;
            //     string typess;
            //     ss1>>name;
            //     ss1>>typess;
            //     column_details[name]=typess;
            // }
            
            vector<pair<string,string>> column_details=fetch_table_header_info(ASTs_insert_data.table_name);

            ////// NUMER MATCHING STARTING HERE ///////////

            // if number column is provided then it must match with then number of row in table
            if(ASTs_insert_data.column_list.size()==0){
                // THEN MATCH THE NUMBER OF COLUMN IN TABLE AND NUMBER OF data per row
                for(int i=0; i<(ASTs_insert_data.value_list.size()); i++){
                    if(ASTs_insert_data.value_list[i].size()!=(column_details.size())){
                        string message="Error: number of value must match with number of column in table!";
                        throw runtime_error(message);
                    }
                }

            }else if(ASTs_insert_data.column_list.size()!=0){
                if(ASTs_insert_data.column_list.size()!=(column_details.size())){
                    string message="Error: number of column in query must match with number of column in table!";
                    throw runtime_error(message);
                }
                for(int i=0; i<(ASTs_insert_data.value_list.size()); i++){
                    if(ASTs_insert_data.value_list[i].size()!=(column_details.size())){
                        string message="Error: number of value must match with number of column in table!";
                        throw runtime_error(message);
                    }
                }
            }
            ////////////// NUNBER MATCHING DONE HERE////////////////////


            /*
            are column name matching or not


            
            */
            
            ////////////////////////////////////// column matching done below///////////////////////////////////////
            if(ASTs_insert_data.column_list.size()!=0){
                // now check whether column name matching exacly or not
                for(int i=0; i<(ASTs_insert_data.column_list.size()); i++){
                    if(ASTs_insert_data.column_list[i]!=(column_details[i].first)){
                        string message="Error: column name mismatch expecting "+(column_details[i].first)+" getting "+(ASTs_insert_data.column_list[i]);
                        throw runtime_error(message);
                    }
                }
            }

            ///////// TYPE MATCHING STARTING HERE//////////////////////
            //////////// match the data type of value and data type of table column////////////////////
            for(int i=0; i<(ASTs_insert_data.value_list.size()); i++){
                int j=0;
                is_type_matching(column_details[j].second, ASTs_insert_data.value_list[i][j]);
            }



















        }




    };
};