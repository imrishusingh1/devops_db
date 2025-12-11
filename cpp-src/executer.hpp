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
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;
namespace fs = std::filesystem;
#include "parse.hpp"


namespace executer {
    using namespace parsers::AST;

    static string active_database_path;
    static void createDatabaseExecute() {
        string db_name = ASTs_db_creation.nameOfdatabase;
        string db_path = "./data/" + db_name;
        fs::create_directories(db_path);

        // Create empty schema file
        ofstream schema_file(db_path + "/.schema", ios::out);
        schema_file.close();

        cout << "Database created: " << db_name << endl;
    }

    static void useDatabaseExecuter() {
        string db_name = ASTs_use_db.db_name;
        string db_path = "./data/" + db_name;

        if (!fs::exists(db_path)) {
            cerr << "Database does not exist: " << db_name << endl;
            return;
        }
        active_database_path = db_path;
        cout << "Database in use: " << db_name << endl;
    }

    static void createTableExecute() {
        // cout<<active_database_path<<endl;
        if (active_database_path.empty()) {
            cerr << "No database selected." << endl;
            return;
        }

        // Append table info to .schema
        string schema_path = active_database_path + "/.schema";
        ofstream schema_file(schema_path, ios::app);
        schema_file << "TABLE " << ASTs_table_creation.table_name << endl;

        for (auto &col : ASTs_table_creation.column_list_Info) {
            schema_file << col.getColumn_name() << " "
                        << col.getData_type() << " "
                        << (col.is_primary_key() ? "1" : "0") << endl;
        }
        schema_file << "ENDTABLE" << endl;
        schema_file.close();

        // Create empty binary file for data
        string table_data_path = active_database_path + "/" + ASTs_table_creation.table_name + ".bin";
        ofstream table_file(table_data_path, ios::binary | ios::out);
        table_file.close();

        cout << "Table created: " << ASTs_table_creation.table_name << endl;
    }
    static void insertTableExecuter() {
        if (active_database_path.empty()) {
            cerr << "No database selected." << endl;
            return;
        }

        string table_path = active_database_path + "/" + ASTs_insert_data.table_name + ".bin";
        ofstream table_file(table_path, ios::binary | ios::app);
        if (!table_file.is_open()) {
            cerr << "Cannot open table for insert." << endl;
            return;
        }

        for (const auto &pair : ASTs_insert_data.value_list) {
            const vector<string> &row = pair.second;

            // For simplicity, write length-prefixed strings
            for (const string &val : row) {
                size_t len = val.size();
                table_file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                table_file.write(val.c_str(), len);
            }
        }

        table_file.close();
        cout << "Data inserted into table: " << ASTs_insert_data.table_name << endl;
    }
    // static void selectTableExecuter() {
    //     if (active_database_path.empty()) {
    //         cerr << "No database selected." << endl;
    //         return;
    //     }

    //     // Load schema for this table
    //     string schema_path = active_database_path + "/.schema";
    //     ifstream schema_file(schema_path, ios::in);
    //     if (!schema_file.is_open()) {
    //         cerr << "Schema not found." << endl;
    //         return;
    //     }

    //     vector<string> columns;
    //     bool table_found = false;
    //     string line;
    //     while (getline(schema_file, line)) {
    //         if (line == "TABLE " + ASTs_select_data.table_name) {
    //             table_found = true;
    //             continue;
    //         }
    //         if (line == "ENDTABLE") {
    //             break;
    //         }
    //         if (table_found) {
    //             istringstream iss(line);
    //             string colname, dtype, primary;
    //             iss >> colname >> dtype >> primary;
    //             columns.push_back(colname);
    //         }
    //     }
    //     schema_file.close();

    //     if (!table_found) {
    //         cerr << "Table not found in schema." << endl;
    //         return;
    //     }

    //     // Read data
    //     string table_path = active_database_path + "/" + ASTs_select_data.table_name + ".bin";
    //     ifstream table_file(table_path, ios::binary | ios::in);
    //     if (!table_file.is_open()) {
    //         cerr << "Cannot open table data." << endl;
    //         return;
    //     }

    //     vector<vector<string>> rows;
    //     while (!table_file.eof()) {
    //         vector<string> row;
    //         for (size_t i = 0; i < columns.size(); i++) {
    //             size_t len;
    //             if (!table_file.read(reinterpret_cast<char*>(&len), sizeof(len))) break;

    //             string val(len, '\0');
    //             table_file.read(&val[0], len);
    //             row.push_back(val);
    //         }
    //         if (!row.empty())
    //             rows.push_back(row);
    //     }
    //     table_file.close();

    //     // Determine which columns to display
    //     vector<int> selected_indexes;
    //     if (ASTs_select_data.to_select_all) {
    //         for (size_t i = 0; i < columns.size(); i++)
    //             selected_indexes.push_back(i);
    //     } else {
    //         for (const auto &sel_col : ASTs_select_data.column_list) {
    //             auto it = find(columns.begin(), columns.end(), sel_col);
    //             if (it != columns.end()) {
    //                 selected_indexes.push_back(distance(columns.begin(), it));
    //             }
    //         }
    //     }

    //     // Optional ORDER BY
    //     if (!ASTs_select_data.column_for_sorting.empty()) {
    //         string order_col = ASTs_select_data.column_for_sorting.begin()->first;
    //         string order_dir = ASTs_select_data.column_for_sorting.begin()->second;

    //         int sort_index = -1;
    //         for (size_t i = 0; i < columns.size(); i++) {
    //             if (columns[i] == order_col) {
    //                 sort_index = i;
    //                 break;
    //             }
    //         }
    //         if (sort_index != -1) {
    //             sort(rows.begin(), rows.end(), [&](const vector<string>& a, const vector<string>& b) {
    //                 if (order_dir == "ASC") {
    //                     return a[sort_index] < b[sort_index];
    //                 } else {
    //                     return a[sort_index] > b[sort_index];
    //                 }
    //             });
    //         }
    //     }

    //     // Print header
    //     for (int idx : selected_indexes) {
    //         cout << setw(20) << columns[idx] << " | ";
    //     }
    //     cout << endl;
    //     cout << string(22 * selected_indexes.size(), '-') << endl;

    //     // Print rows
    //     for (const auto& row : rows) {
    //         for (int idx : selected_indexes) {
    //             cout << setw(20) << row[idx] << " | ";
    //         }
    //         cout << endl;
    //     }
    // }

    static std::string selectTableExecuter() {
        std::ostringstream out;

        if (active_database_path.empty()) {
            out << "ERROR: No database selected.\n";
            return out.str();
        }

        // Load schema for this table
        string schema_path = active_database_path + "/.schema";
        ifstream schema_file(schema_path, ios::in);
        if (!schema_file.is_open()) {
            out << "ERROR: Schema not found.\n";
            return out.str();
        }

        vector<string> columns;
        bool table_found = false;
        string line;
        while (getline(schema_file, line)) {
            if (line == "TABLE " + ASTs_select_data.table_name) {
                table_found = true;
                continue;
            }
            if (line == "ENDTABLE") {
                break;
            }
            if (table_found) {
                istringstream iss(line);
                string colname, dtype, primary;
                iss >> colname >> dtype >> primary;
                columns.push_back(colname);
            }
        }
        schema_file.close();

        if (!table_found) {
            out << "ERROR: Table not found in schema.\n";
            return out.str();
        }

        // Read data
        string table_path = active_database_path + "/" + ASTs_select_data.table_name + ".bin";
        ifstream table_file(table_path, ios::binary | ios::in);
        if (!table_file.is_open()) {
            out << "ERROR: Cannot open table data.\n";
            return out.str();
        }

        vector<vector<string>> rows;
        while (!table_file.eof()) {
            vector<string> row;
            for (size_t i = 0; i < columns.size(); i++) {
                size_t len;
                if (!table_file.read(reinterpret_cast<char*>(&len), sizeof(len))) break;

                string val(len, '\0');
                table_file.read(&val[0], len);
                row.push_back(val);
            }
            if (!row.empty() && !row[0].empty())
                rows.push_back(row);
        }
        table_file.close();

        // Determine which columns to display
        vector<int> selected_indexes;
        if (ASTs_select_data.to_select_all) {
            for (size_t i = 0; i < columns.size(); i++)
                selected_indexes.push_back(i);
        } else {
            for (const auto& sel_col : ASTs_select_data.column_list) {
                auto it = find(columns.begin(), columns.end(), sel_col);
                if (it != columns.end()) {
                    selected_indexes.push_back(distance(columns.begin(), it));
                } else {
                    out << "ERROR: Column not found: " << sel_col << "\n";
                    return out.str();
                }
            }
        }

        // Optional ORDER BY
        if (!ASTs_select_data.column_for_sorting.empty()) {
            string order_col = ASTs_select_data.column_for_sorting.begin()->first;
            string order_dir = ASTs_select_data.column_for_sorting.begin()->second;

            int sort_index = -1;
            for (size_t i = 0; i < columns.size(); i++) {
                if (columns[i] == order_col) {
                    sort_index = i;
                    break;
                }
            }
            if (sort_index != -1) {
                sort(rows.begin(), rows.end(), [&](const vector<string>& a, const vector<string>& b) {
                    if (order_dir == "ASC") {
                        return a[sort_index] < b[sort_index];
                    } else {
                        return a[sort_index] > b[sort_index];
                    }
                });
            }
        }

        for (int idx : selected_indexes) {
            out << std::setw(20) << columns[idx] << " | ";
        }
        out << "\n";
        out << std::string(22 * selected_indexes.size(), '-') << "\n";

        for (const auto& row : rows) {
            for (int idx : selected_indexes) {
                out << std::setw(20) << row[idx] << " | ";
            }
            out << "\n";
        }

        return out.str();
    }


    static void updateTableExecuter() {
        if (active_database_path.empty()) {
            cerr << "No database selected." << endl;
            return;
        }

        // Load schema
        string schema_path = active_database_path + "/.schema";
        ifstream schema_file(schema_path, ios::in);
        if (!schema_file.is_open()) {
            cerr << "Schema not found." << endl;
            return;
        }

        vector<string> columns;
        bool table_found = false;
        string line;
        while (getline(schema_file, line)) {
            if (line == "TABLE " + ASTs_update_data.table_name) {
                table_found = true;
                continue;
            }
            if (line == "ENDTABLE") {
                break;
            }
            if (table_found) {
                istringstream iss(line);
                string colname, dtype, primary;
                iss >> colname >> dtype >> primary;
                columns.push_back(colname);
            }
        }
        schema_file.close();

        if (!table_found) {
            cerr << "Table not found in schema." << endl;
            return;
        }

        // Read all rows
        string table_path = active_database_path + "/" + ASTs_update_data.table_name + ".bin";
        fstream table_file(table_path, ios::binary | ios::in);
        vector<vector<string>> rows;
        while (!table_file.eof()) {
            vector<string> row;
            for (size_t i = 0; i < columns.size(); i++) {
                size_t len;
                if (!table_file.read(reinterpret_cast<char*>(&len), sizeof(len))) break;

                string val(len, '\0');
                table_file.read(&val[0], len);
                row.push_back(val);
            }
            if (!row.empty())
                rows.push_back(row);
        }
        table_file.close();

        // Update matching rows (no WHERE support yet)
        for (auto &row : rows) {
            for (const auto &p : ASTs_update_data.columns_and_values) {
                auto it = find(columns.begin(), columns.end(), p.first);
                if (it != columns.end()) {
                    int idx = distance(columns.begin(), it);
                    row[idx] = p.second;
                }
            }
        }

        // Write back
        table_file.open(table_path, ios::binary | ios::out | ios::trunc);
        for (auto &row : rows) {
            for (auto &val : row) {
                size_t len = val.size();
                table_file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                table_file.write(val.c_str(), len);
            }
        }
        table_file.close();

        cout << "Table updated: " << ASTs_update_data.table_name << endl;
    }
    static void deleteTableExecuter() {
        if (active_database_path.empty()) {
            cerr << "No database selected." << endl;
            return;
        }

        string table_path = active_database_path + "/" + ASTs_delete_data.table_name + ".bin";

        // Simply truncate the file for now 
        ofstream table_file(table_path, ios::binary | ios::out | ios::trunc);
        table_file.close();

        cout << "Table data deleted: " << ASTs_delete_data.table_name << endl;
    }

    static void dropExecuter() {
        if (ASTs_drop.is_table) {
            string table_path = active_database_path + "/" + ASTs_drop._name + ".bin";
            if (fs::exists(table_path)) {
                fs::remove(table_path);
                cout << "Table dropped: " << ASTs_drop._name << endl;
            } else {
                cerr << "Table not found: " << ASTs_drop._name << endl;
            }
        } else {
            string db_path = "./data/" + ASTs_drop._name;
            if (fs::exists(db_path)) {
                fs::remove_all(db_path);
                cout << "Database dropped: " << ASTs_drop._name << endl;
            } else {
                cout<<db_path<<endl;
                cerr << "Database not found: " << ASTs_drop._name << endl;
            }
        }
    }
}
