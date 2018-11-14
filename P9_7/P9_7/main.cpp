/*
 Exercise P9.7.
 The program in Section 9.6 only locates one record and updates the salary.
 Write a program that raises or lowers the salaries of all employees by a given percentage.
*/

// This exercise could have been accomplished with far less code. Focus here was more about experimenting with different storage and retrieval techniques - parallel vectors, namespacing the helper functions, storing file records as Employee objects, odd use of Employee#operator[], etc.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

#include "employee.hpp"
#include "helpers.hpp"
using namespace HELPERS;

using namespace std;

int main(int argc, const char * argv[]) {
    // This file starts out with contents (unformatted rows with fields separated by '|')
        // ex. "Mr.|Harry|Hacker|$239492|1105 Torre Ave.|Cupertino|CA|95014\n"
    string db_original = "/Users/christianmeyer/cpp/ch9/P9_7/db_original";
    // This file is the output once the record are formatted for seekg
    string db_original_output = "/Users/christianmeyer/cpp/ch9/P9_7/db_original_output";
    
    // Employee class comes into play. The purpose of the new files was realized after dealing with the old - which is to be able to store and modify the record data and to write the modifications to new files.
    string db_employees = "/Users/christianmeyer/cpp/ch9/P9_7/db_employees";
    // new output after Employee data members are changed.
    string db_employees_output = "/Users/christianmeyer/cpp/ch9/P9_7/db_employees_output";
    
    fstream fs;
    fs.open(db_original.c_str(), ios::in | ios::out);
    if (fs.fail()){
        cout << "Could not open file " << db_original << endl;
        exit(1);
    }
    fs.seekg(0, ios::end);
    int tellg = (int)(fs.tellg());
    fs.seekg(0, ios::beg);
    cout << "(in db_original)" << endl;
    cout << "tellg: " << tellg << endl;
    int record_size = HELPERS::max_record_size(fs, db_original);
    // ^ Wrong number of record here. An #avg_record_size would probably be a little better, but just following along the lines of examples in book. Note: #max_record_size is all that is needed when the record sizes are fixed. The records here, in db_original, are the ones that are problematic, since those record sizes are variable.
    int nrecord = tellg / record_size;
    cout << "avg_record_size: " << record_size << endl;
    cout << "nrecord: " << nrecord << endl;
    fs.close();

    fs.open(db_original.c_str());
    if (fs.fail()){
        cout << "Could not open file " << db_original << endl;
        exit(1);
    }
    vector<vector<string> > tags = HELPERS::make_tags(fs);
    vector<int> buffer_sizes;
    int num_tags = tags[0].size();
    for (int j = 0; j < num_tags; j++){
        buffer_sizes.push_back(HELPERS::max_tag_size(tags, j));
    }
    fs.close();
    cout << "\n";
    
    ofstream ofs;
    vector<string> tag_fields = {"TITLE", "FIRST NAME", "LAST NAME", "SALARY", "ADDRESS", "CITY", "STATE", "ZIP"};
    HELPERS::output_new_buf_sizes(tags, buffer_sizes, ofs, db_original_output, tag_fields);
    ofs.close();
    
    fs.open(db_original_output.c_str());
    if (fs.fail()){
        cout << "Could not open file " << db_original_output << endl;
        exit(1);
    }
    fs.seekg(0, ios::end);
    tellg = (int)(fs.tellg());
    fs.seekg(0, ios::beg);
    cout << "(in db_original_output)" << endl;
    cout << "tellg: " << tellg << endl;
    record_size = HELPERS::max_record_size(fs, db_original);
    nrecord = tellg / record_size;
    cout << "avg_record_size: " << record_size << endl;
    cout << "nrecord: " << nrecord << " (+1 for header)" << endl;
    fs.close();
    cout << "\n";
    
    vector<Employee*> employees;
    for (int i = 0; i < tags.size(); i++){
        Employee* e = new Employee();
        for (int j = 0; j < tags[i].size(); j++){
            *((*e)[j]) = tags[i][j];
        }
        employees.push_back(e);
    }
    
    HELPERS::print_employees(employees);
    
    ofs.open(db_employees.c_str(), ios::in | ios::out | ios::trunc);
    if (ofs.fail()){
        cout << "Could not open file " << db_employees << endl;
        exit(1);
    }
    for (int i = 0; i < employees.size(); i++){
        string line = *((*employees[i])[8]);
        ofs << line;
    }
    ofs.close();
    
    ofs.open(db_employees.c_str(), ios::in | ios::out | ios::trunc);
    if (ofs.fail()){
        cout << "Could not open file " << db_employees << endl;
        exit(1);
    }
    for (int i = 0; i < employees.size(); i++){
        string line = *((*employees[i])[8]);
        ofs << line;
    }
    ofs.close();
    
    // changing salaries of all employees by random amount
    for (int i = 0; i < employees.size(); i++){
        for (int j = 0; j < employees[i]->size(); j++){
            double salary = employees[i]->get_salary();
            int sign = rand()%2; // 0 or 1
            double change_in_salary = rand()%50000+1;
            if (sign == 0) change_in_salary *= -1;
            salary += change_in_salary;
            if (salary > 0.0) employees[i]->set_salary(salary);
        }
    }
    
    HELPERS::print_employees(employees);
    
    fs.open(db_employees.c_str());
    tags.clear();
    for (int i = 0; i < employees.size(); i++){
        vector<string> line;
        for (int j = 0; j < employees[i]->size(); j++){
            line.push_back(*((*employees[i])[j]));
        }
        tags.push_back(line);
        line.clear();
    }
    num_tags = tags[0].size();
    buffer_sizes.clear();
    for (int j = 0; j < num_tags; j++){
        buffer_sizes.push_back(HELPERS::max_tag_size(tags, j));
    }
    fs.close();
    HELPERS::output_new_buf_sizes(tags, buffer_sizes, ofs, db_employees_output, tag_fields);
    ofs.close();
    cout << "\n";
    
    fs.open(db_employees.c_str());
    if (fs.fail()){
        cout << "Could not open file " << db_employees << endl;
        exit(1);
    }
    fs.seekg(0, ios::end);
    tellg = (int)(fs.tellg());
    fs.seekg(0, ios::beg);
    cout << "(in db_employees)" << endl;
    cout << "tellg: " << tellg << endl;
    record_size = HELPERS::max_record_size(fs, db_employees);
    nrecord = tellg / record_size;
    cout << "avg_record_size: " << record_size << endl;
    cout << "nrecord: " << nrecord << endl;
    fs.close();
    cout << "\n";
    
    fs.open(db_employees_output.c_str());
    if (fs.fail()){
        cout << "Could not open file " << db_employees_output << endl;
        exit(1);
    }
    fs.seekg(0, ios::end);
    tellg = (int)(fs.tellg());
    fs.seekg(0, ios::beg);
    cout << "(in db_employees_output)" << endl;
    cout << "tellg: " << tellg << endl;
    record_size = HELPERS::max_record_size(fs, db_employees_output);
    nrecord = tellg / record_size;
    cout << "avg_record_size: " << record_size << endl;
    cout << "nrecord: " << nrecord << " (+1 for header)" << endl;
    fs.close();
    cout << "\n";
    
    return 0;
}



