#include<iostream>
#include "lexer.hpp"
#include "parse.hpp"
#include "exprtree.hpp"
#include<vector>
#include <filesystem>
#include "symentic.hpp"
#include "executer.hpp"
#include "crow.h"
namespace fs=filesystem;





#include <string>
#include <stdexcept>
#include <sstream>

std::string distributer(const std::string& query) {
    std::ostringstream out;

    try {
        std::string clean_query = lexers::sanitization::sanitize(query);
        lexers::flush_tokens();
        lexers::tokenizer(clean_query);

        int i = 0;
        while (lexers::tokens[i].token_type == WHITESPACE) {
            i++;
        }

        if (lexers::tokens[i].token_value == "USE") {
            executer::active_database_path.clear();
            parsers::Parser::ParseUseDataBase();
            executer::useDatabaseExecuter();
            out << "Database changed to: " << parsers::AST::ASTs_use_db.db_name << "\n";

        } else if (lexers::tokens[i].token_value == "CREATE") {
            i++;
            while (lexers::tokens[i].token_type == WHITESPACE) {
                i++;
            }
            if (lexers::tokens[i].token_value == "TABLE") {
                parsers::Parser::ParseTableCreation();
                executer::createTableExecute();
                out << "Table created successfully.\n";

            } else if (lexers::tokens[i].token_value == "DATABASE") {
                parsers::Parser::ParseDataBaseCreation();
                executer::createDatabaseExecute();
                out << "Database created successfully.\n";

            } else {
                throw std::runtime_error("Syntax error!");
            }

        } else if (lexers::tokens[i].token_value == "INSERT") {
            parsers::Parser::ParseInsert();
            executer::insertTableExecuter();
            out << "Data inserted successfully.\n";

        } else if (lexers::tokens[i].token_value == "UPDATE") {
            parsers::Parser::ParseUpdate();
            executer::updateTableExecuter();
            out << "Table updated successfully.\n";

        } else if (lexers::tokens[i].token_value == "DELETE") {
            parsers::Parser::ParseDelete();
            executer::deleteTableExecuter();
            out << "Data deleted successfully.\n";

        } else if (lexers::tokens[i].token_value == "SELECT" || lexers::tokens[i].token_value == "GET") {
            parsers::Parser::ParseSelect();
            std::string result = executer::selectTableExecuter();
            out << result;

        } else if (lexers::tokens[i].token_value == "DROP") {
            i++;
            while (lexers::tokens[i].token_type == WHITESPACE) {
                i++;
            }
            parsers::Parser::ParseDrop();
            executer::dropExecuter();
            out << "Drop executed successfully.\n";

        } else {
            throw std::runtime_error("Syntax error!");
        }
    } catch (const std::exception& e) {
        out << "ERROR: " << e.what() << "\n";
    }

    parsers::AST::flush_ASTS();
    parsers::brackets::flush_buffer();

    return out.str();
}

// Declare your distributer function somewhere
std::string distributer(const std::string& query);

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/data").methods("POST"_method)
    ([](const crow::request& req) {
        std::string query = req.body;

        std::string result;
        try {
            result = distributer(query);
        } catch (const std::exception& e) {
            result = std::string("ERROR: ") + e.what();
        }

        crow::json::wvalue res;
        res["result"] = result;

        crow::response response(res);
        response.set_header("Content-Type", "application/json");
        response.add_header("Access-Control-Allow-Origin", "*");
        return response;
    });

    app.port(8080).multithreaded().run();
}



// int main(){
//     while(true){
//         string str;
//         getline(cin,str);
//         try{
//             distributer(str);
//         }catch(runtime_error e){
//             cout<<e.what()<<"try again please!"<<endl;
//         }
//     }
// }