/*
 Exercise P8.3.
 Derive a class Manager from Employee. Add a data field, named department, of type string. Supply a function print that prints the manager’s name, department, and salary. Derive a class Executive from Manager. Supply a function print that prints the string Executive, followed by the information stored in the Manager base object.
 */

#ifndef employee_hpp
#define employee_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

/**
 A basic employee class that is used in many examples
 in the book "Computing Concepts with C++ Essentials"
 */
class Employee{
public:
    Employee();
    Employee(std::string fn, std::string ln, double sal);
    Employee(std::string t, std::string fn, std::string ln, double sal, std::string a, std::string c, std::string s, std::string z);
    std::string* operator[](int i);
    int size(){ return 8; };
    void output_line_to_file(std::fstream& fs, std::string name);
    
    void make_salary_string();
    std::string get_salary_string();
    double get_salary() const { return salary; };
    void set_salary(double ns) { salary = ns; make_salary_string(); };
    
    std::string get_title() const { return title; };
    void set_title(std::string s) { title = s; };
    std::string get_first_name() const { return first_name; };
    void set_first_name(std::string s) { first_name = s; };
    std::string get_last_name() const { return last_name; };
    void set_last_name(std::string s) { last_name = s; };
    std::string get_address() const { return address; };
    void set_address(std::string s) { address = s; };
    std::string get_city() const { return city; };
    void set_city(std::string s) { city = s; };
    std::string get_state() const { return state; };
    void set_state(std::string s) { state = s; };
    std::string get_zip() const { return zip; };
    void set_zip(std::string s) { zip = s; };
private:
    std::string name;
    std::string title, first_name, last_name;
    double salary;
    std::string address, city, state, zip;
    std::string salary_string;
    std::string full_line;
};

#endif /* employee_hpp */
