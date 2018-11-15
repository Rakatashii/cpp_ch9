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
    string db_employees_sorted = "/Users/christianmeyer/cpp/ch9/P9_7/db_employees_sorted";
    
    fstream fs;
    fs.open(db_original.c_str());
    if (fs.fail()){
        cout << "Could not open file " << db_original << endl;
        exit(1);
    }
    // this vector contains records as the type vector<string>, and each vector<string> contains the fields for an individual record.
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
    
    // Make new employee objects using the tags created by reading the db_original file contents
    vector<Employee*> employees;
    for (int i = 0; i < tags.size(); i++){
        Employee* e = new Employee();
        for (int j = 0; j < tags[i].size(); j++){
            *((*e)[j]) = tags[i][j];
        }
        employees.push_back(e);
    }
    
    // This is the massive print out of employee objects to the console
    HELPERS::print_employees(employees);
    cout << "\n";
    
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
    
    // Employee objects printed out again to observe change in salary
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
    // ^ Note: Confusing that half the helper functions are given fstream obj and a string name, and are expected to open and close within function scope, while other half are opened in closed in main scope to avoid having to pass a string. If I had to guess, best practice would be to open and close in main. At the same time, this could mean not knowing the file string within the function definition. Figure out what is prefered and how to handle the former case if it's really the best practice.
    cout << "\n";
    
    // By choosing 4 here, for example, the new file provided to the helper below 'db_employees_sorted' will contain the same contents in 'db_employees_output', but will be sorted by the 4th perameter, which is address.
    int employee_field_index = 2;
    // v Note: if db_employeed_sorted is given as the final perameter (optional), the contents of db_employees_output does not change.
    HELPERS::sort_lines_by_field(buffer_sizes, fs, db_employees_output, employee_field_index, db_employees_sorted);
    cout << "\n";
    
    cout << "File " << db_employees_sorted << " was sorted by " << tag_fields[employee_field_index] << ".\n";
    
    // Now need to do a binary search in the new file (or old) using the same employee_field_index as the one used in #sort_lines_by_field (otherwise, binary search would not be performed on sorted contents anyway).
    
    string search = "Lawson";
    cout << "Searching " << db_employees_sorted << " for keyword " << search << " in field " << tag_fields[employee_field_index] << ".\n" << endl;
    int word_search_pos = HELPERS::binary_search_by_field(buffer_sizes, fs, db_employees_sorted, employee_field_index, search);
    //cout << "search_pos = " << word_search_pos << endl;
    
    if (word_search_pos != 0){
        cout << "Word \"" << search << "\" found at position " << word_search_pos << ".\n";
        fs.open(db_employees_sorted.c_str(), ios::in | ios::out);
        fs.seekg(word_search_pos, ios::beg);
        string search_word;
        getline(fs, search_word, '|');
        fs.close();
        cout << "\n";
    }
    
    int line_search_pos = HELPERS::binary_search_by_field(buffer_sizes, fs, db_employees_sorted, employee_field_index, search, true);
    //cout << "line_search_pos = " << line_search_pos << endl;
    if (line_search_pos != 0){
        cout << "Line containing \"" << search << "\" found at position " << line_search_pos << ".\n";
        fs.open(db_employees_sorted.c_str(), ios::in | ios::out);
        fs.seekg(line_search_pos, ios::beg);
        string search_line;
        getline(fs, search_line);
        cout << "Output: " << search_line << endl;
        fs.close();
        cout << "\n";
    }
    
    return 0;
}



