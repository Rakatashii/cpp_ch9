#ifndef people_hpp
#define people_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Person{
public:
    Person();
    Person(std::string n, std::string tel);
    Person(std::string n, std::string tel, std::string soc, std::string sal);
    void make_numeric_salary();
    
    void set_name(std::string n);
    void set_telephone(std::string tel);
    void set_social(std::string soc);
    void set_salary(std::string sal);
    
    std::string get_name() const;
    std::string get_telephone() const;
    std::string get_social() const;
    std::string get_salary() const;
    double get_numeric_salary() const;
private:
    std::string name, telephone, social, salary;
    double numeric_salary;
};

#endif /* people_hpp */
