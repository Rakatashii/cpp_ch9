#include "employee.hpp"

Employee::Employee(){
    title = "null";
    first_name = "null";
    last_name = "null";
    salary = 0.0;
    make_salary_string();
    address = "null";
    city = "null";
    state = "null";
    zip = "null";
}
Employee::Employee(std::string fn, std::string ln, double sal){
    title = "null";
    first_name = fn;
    last_name = ln;
    salary = sal;
    make_salary_string();
    address = "null";
    city = "null";
    state = "null";
    zip = "null";
}
Employee::Employee(std::string t, std::string fn, std::string ln, double sal, std::string a, std::string c, std::string s, std::string z){
    title = t;
    first_name = fn;
    last_name = ln;
    salary = sal;
    make_salary_string();
    city = c;
    state = s;
    zip = z;
}
std::string* Employee::operator[](int i){
    switch (i){
        case 0: {
            std::string* t = &title;
            return t;
        }
        case 1: {
            std::string* fn = &first_name;
            return fn;
        }
        case 2: {
            std::string* ls = &last_name;
            return ls;
        }
        case 3: {
            std::string* sal = &salary_string;
            return sal;
        }
        case 4: {
            std::string* a = &address;
            return a;
        }
        case 5: {
            std::string* c = &city;
            return c;
        }
        case 6: {
            std::string* s = &state;
            return s;
        }
        case 7: {
            std::string* z = &zip;
            return z;
        }
        case 8: {
            full_line = title+'|'+first_name+'|'+last_name+'|'+salary_string+'|'+address+'|'+city+'|'+state+'|'+zip+'\n';
            std::string* full = &full_line;
            return full;
        }
    }
    return 0;
}
void Employee::make_salary_string(){
    std::ostringstream oss;
    oss << "$" << salary;
    salary_string = oss.str();
}
std::string Employee::get_salary_string(){
    return salary_string;
}


