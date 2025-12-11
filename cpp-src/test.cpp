#include<iostream>
#include "lexer.hpp"
#include "parse.hpp"
#include "exprtree.hpp"
#include<vector>
#include <filesystem>
#include "symentic.hpp"
#include "executer.hpp"
namespace fs=filesystem;


int main(){

    string str="drop student;";
            
        str=lexers::sanitization::sanitize(str);
        lexers::tokenizer(str);
        parsers::Parser::ParseDrop();

    // string str=R"(
    //     void printHello(int x,int y);


    // )";



    // string path="./data/user/rishu";
    // fs::create_directories(path);


    // string str=R"(   CREATE TABLE employeeSSS  (
    //         id INT ,
    //         name VARCHAR(100) ,
    //         salary DECIMAL(10 ,2),
    //         image_value IMAGE PRIMARY KEY,
    //         video_value VIDEO,
    //         position VARCHAR(100)
    //     )     ;)";
    
    // {
    //     string str="CREATE DATABASE MYdb1;";
        
    //     str=lexers::sanitization::sanitize(str);
    //     lexers::tokenizer(str);

    //     lexers::printToken();
    //     parsers::Parser::ParseDataBaseCreation();

    //     cout<<endl;
    //     // sementics::Analyse::CreateDatabaseAnalysis();
    //     executer::createDatabaseExecute();



    // }

    {

        // string str1="USE MYDB;";
        // str1=lexers::sanitization::sanitize(str1);
        // lexers::tokenizer(str1);
        // lexers::printToken();

        // parsers::Parser::ParseUseDataBase();
        // // sementics::Analyse::UseDatabaseAnalysis();
        // executer::useDatabaseExecuter();

        // lexers::flush_tokens();


        // string str=R"(   CREATE TABLE employee  (
        //         id INT ,
        //         name VARCHAR(10) ,
        //         salary DECIMAL(4 ,2),
        //         image_value IMAGE PRIMARY KEY,
        //         video_value VIDEO,
        //         position VARCHAR(10)
        //     )     ;)";
    // string str=R"(            UPDATE employee
    //         SET salary = 60000;)";
    // // string str="SELECT * FROM employee;";
    // string str="DROP DATABASE mydb;";


        // str=lexers::sanitization::sanitize(str);
        // lexers::tokenizer(str);
        // lexers::printToken();

    //     parsers::Parser::ParseDrop();
    //     executer::dropExecuter();
        // parsers::Parser::ParseTableCreation();
        // parsers::Parser::ParseSelect();
        // parsers::Parser::ParseUpdate();
        // sementics::Analyse::CreateTableAnalysis();
        // executer::createTableExecute();
        // executer::selectTableExecuter();
        // executer::updateTableExecuter();

    // string str= R"(        INSERT INTO employee
    //     VALUES (
    //     (2, 'Alice', 'Smith', 55000,13,123),
    //     (3, 'Bob', 'Johnson', 60000,4,2),
    //     (4, 'Eve', 80000, 45000,2,3),
    //     (7, 'Alice', 'Smith', 55000,5,6)
    //     );)";
    //     str=lexers::sanitization::sanitize(str);
    //     lexers::tokenizer(str);
    //     lexers::printToken();

    //     parsers::Parser::ParseInsert();
    //     // sementics::Analyse::InsertAnalysis();
    //     executer::insertTableExecuter();









        
    }







    // string str="DROP TABLE name;";
    // string str="CREATE (2.5)";
    // string str1= R"(        INSERT INTO STUDENT
    //     VALUES (
    //     ('Rishu', 'Alice', 'Smith', 55000),
    //     (3, 'Bob', 'Johnson', 60000),
    //     (4, 'Eve', 80000, 45000),
    //     ('Rishu', 'Alice', 'Smith', 55000)
    //     );)";
    // string str=R"(DELETE FROM employee WHERE (country = 'USA' AND status = 'inactive')
    //             OR (country = 'Canada' AND (status = 'inactive' OR status = 'pending'));)";
    // string str=R"(DELETE FROM employee WHERE ((a <= 5 OR b > 10) AND (x != 15 OR y >= 20)) AND z <> 30;)";
    // string str=R"(            (('country') <> ('USA' AND status = 'inactive')
    //         OR (country = 'Canada' AND (status <= 'inactive' OR status = 'pending')));)";
    // string str=R"((a <= 5 OR b > 10) AND (x != 15 OR y >= 20);)";
    // string str=R"(
    //             SELECT *
    //           FROM table_name
    //         WHERE ((num>=2) AND (num2=0))
    //         ;)";


    // string str=R"(            UPDATE employees
    //         SET salary = 60000 where sal='23' and;)";

//     string str=R"(                UPDATE employees
//                 SET salary = '60000', id=256, name='rishu' WHERE     (a = 5 AND b != 10) OR (x >= 100 AND y <= 200) AND (z <> 50 OR w = 300)
// ;)";

    // string str=R"(SELECT * FROM employees;)";
    // string str=R"(                        SELECT first_name, last_name, age
    //         FROM employees WHERE (('country') <> ('USA' AND status = 'inactive')
    //          OR (country = 'Canada' AND (status <= 'inactive' OR status = 'pending')))
    //         ORDER BY last_name ASC, first_name DESC, name  ASC;)";


    /*
                SELECT first_name, last_name
            FROM employees
            ORDER BY last_name ASC;
    
    */

    // string str="((add  <=  '  phagwara  ')  + (((country != '   USA   ' AND status  <> 23)  ) OR ( id >= 1 )));";
    // string str="add=\"phagwara\" OR (country = '   USA   ' AND status = 'inactive' OR (id=12 AND section=\"K23BV\" OR ( section=\"K23CG\" AND surname=\"singh\" ) AND cgpa=\"8.9\") OR regno=\"12345\" );";
    // string str=R"(DELETE FROM  employee WHERE a+b;)";
    // str=lexers::sanitization::sanitize(str);
    // cout<<"query size: "<<str.size()<<endl;



    // string str=R"(CREATE DATABASE mydatabase;)";
    //string str=R"(use mydatabase;)";








    // str=lexers::sanitization::sanitize(str);
    // lexers::tokenizer(str);

    // lexers::printToken();



    // // parsers::Parser::ParseDataBaseCreation();
    // cout<<endl<<endl;
    // parsers::Parser::ParseUseDataBase();
    // sementics::Analyse::UseDatabaseAnalysis();
    // lexers::flush_tokens();
    // cout<<endl;
    // // parsers::Parser::ParseTableCreation();
    // // parsers::Parser::ParseDrop();
    // str1=lexers::sanitization::sanitize(str1);
    // lexers::tokenizer(str1);

    // lexers::printToken();


    // parsers::Parser::ParseInsert();
    // sementics::Analyse::InsertAnalysis();
    // parsers::Parser::ParseDelete();
    // cout<<endl;
    // int x=0;
    // parsers::Parser::parseExpression(x);
    // parsers::Parser::parseExpression(x,true);
    // parsers::Parser::ParseSelect();
    // expEvaluation::postOrder(expEvaluation::expTree);
    // parsers::Parser::ParseUpdate();
    // cout<<endl;
    // expretree::expEvaluation::postOrder(expretree::expEvaluation::expTree);

    /////// symetic checkup/////////////////
    // sementics::Analyse::CreateDatabaseAnalysis();
    // sementics::Analyse::UseDatabaseAnalysis();
    // sementics::Analyse::InsertAnalysis();
    // // sementics::Analyse::is_type_matching("VARCHAR(5)","\"RISHU\"");
    // // sementics::Analyse::is_type_matching("VIDEO","8424");
    // vector<pair<string,string>> datas=sementics::Analyse::fetch_table_header_info("table");

    // for(pair<string,string> p:datas){
    //     cout<<"|"<<p.first<<"=>"<<p.second<<"|"<<endl;
    // }




    
    
    
    // cout<<"Database name is: "<<parsers::AST::ASTs_db_creation.nameOfdatabase<<endl;

    // cout<<"Table name: "<<parsers::AST::ASTs_table_creation.table_name<<endl;
    // // for(string:)
    // for(parsers::AST::TableColumnInfo s:parsers::AST::ASTs_table_creation.column_list_Info){
    //     s.printInfo();
    // }


    ////////////////////// INSERT DATA PRINTING/////////////////////////////////////////////////
    // cout<<"TABLE NAME: "<<(parsers::AST::ASTs_insert_data.table_name)<<endl;

    // for(string s:parsers::AST::ASTs_insert_data.column_list){
    //     cout<<s<<" | ";
    // }
    // cout<<"\n---------------------------------------------"<<endl;
    // for(pair<int,vector<string>> p:parsers::AST::ASTs_insert_data.value_list){
    //     cout<<p.first<<") ";
    //     for(string s:p.second){
    //         cout<<s<<" | ";
    //     }
    //     cout<<endl;
    // }

    //////////////////////////////////DELETE TABLE //////////////////////////////////

    // cout<<"TABLE NAME: "<<(parsers::AST::ASTs_delete_data.table_name)<<endl;

    // if(parsers::AST::ASTs_delete_data.expressionTreess!=nullptr){
    //     expretree::expEvaluation::postOrder(parsers::AST::ASTs_delete_data.expressionTreess);
    // }

    // /////////////////////////// SELECT TEST//////////////////////////////////
    // cout<<"TABLE NAME: "<<(parsers::AST::ASTs_select_data.table_name)<<endl;
    
    // for(string s:(parsers::AST::ASTs_select_data.column_list)){
    //     cout<<s<<" | ";
    // }
    
    // cout<<endl;
    // for(pair<string,string> p:(parsers::AST::ASTs_select_data.column_for_sorting)){
    //     cout<<p.first<<"=>"<<p.second<<endl;
    // }


    // cout<<endl;
    // expretree::expEvaluation::postOrder(expretree::expEvaluation::expTree);


    ////////////////////////////////////// UPDATE STATEMENT////////////////////////////////////////////
    // cout<<"TABLE NAME: "<<(parsers::AST::ASTs_update_data.table_name.size())<<endl;
    // for(pair<string,string> p:(parsers::AST::ASTs_update_data.columns_and_values)){
    //     cout<<p.first<<"=>"<<p.second<<endl;
    // }
    // expretree::expEvaluation::postOrder(expretree::expEvaluation::expTree);




    // cout<<"Table Name: "<<parsers::insert_TBLSMT.table_name<<endl;
    // if(!parsers::insert_TBLSMT.column_list.empty()){
    //     for(string v:parsers::insert_TBLSMT.column_list){
    //         cout<<v<<" | ";
    //     }
    // }
    // cout<<endl;

    // for(int i=0; i<parsers::insert_TBLSMT.row_data_list.size(); i++){
    //     cout<<i+1<<") ";
    //     for(string s:parsers::insert_TBLSMT.row_data_list[i]){
    //         cout<<s<<" | ";
    //     }
    //     cout<<endl;
    // }

    // cout<<endl;

    // cout<<"table name: "<<parsers::create_TBLSMT.table_name<<endl;
    // for(parsers::tablecolumn& v:parsers::create_TBLSMT.columns_list){
    //     cout<<v.column_name<<" "<<v.column_type<<" "<<v.is_primary<<endl;
    // }

    // cout<<parsers::drope_TBLORDBSMT.idenifier_name<<" "<<parsers::drope_TBLORDBSMT.is_table<<" "<<parsers::drope_TBLORDBSMT.is_database<<endl;
}