#include "people.hpp"

Person::Person(){}
Person::Person(std::string n, std::string tel){
    name = n;
    telephone = tel;
}
Person::Person(std::string n, std::string tel, std::string soc, std::string sal){
    name = n;
    telephone = tel;
    social = soc;
    salary = sal;
    make_numeric_salary();
}
void Person::make_numeric_salary(){
    numeric_salary = stod(salary);
}
void Person::set_name(std::string n){
    name = n;
}
void Person::set_telephone(std::string tel){
    telephone = tel;
}
void Person::set_social(std::string soc){
    social = soc;
}
void Person::set_salary(std::string sal){
    salary = sal;
    make_numeric_salary();
}
std::string Person::get_name() const{
    return name;
}
std::string Person::get_telephone() const{
    return telephone;
}
std::string Person::get_social() const{
    return social;
}
std::string Person::get_salary() const{
    return salary;
}
double Person::get_numeric_salary() const{
    return numeric_salary;
}

