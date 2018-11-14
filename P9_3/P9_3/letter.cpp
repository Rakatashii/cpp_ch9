#include <stdio.h>
#include <iostream>
#include <string>
#include "letter.hpp"
#include <sstream>

Letter::Letter(){
    count = 0;
    total = 0;
    frequency = 0.0;
}
Letter::Letter(char c){
    let = c;
    count = 1; total = 0;
    frequency = 0.0;
}
void Letter::incr(){
    count += 1;
    if (total > 0){
        calc_frequency();
    }
}
void Letter::set_total(int t){
    total = t;
}
int Letter::get_total() const {
    return total;
}
void Letter::calc_frequency(){
    frequency = static_cast<double>(static_cast<double>(count) / static_cast<double>(total));
}
double Letter::get_frequency() {
    if (total > 0){
        calc_frequency();
    }
    return frequency;
    
}
char Letter::get_letter() const { return let; }
int Letter::get_count() const { return count; }
std::string Letter::get_print_string() {
    std::string result = "letter: ";
    std::ostringstream oss;
    oss << "letter: ";
    oss << let;
    oss << " | count: ";
    oss << count;

    if (total > 0){
        calc_frequency();
    }
    if (frequency > 0.0){
        oss << " | frequency: ";
        oss << (frequency*100.0);
        oss << "%";
    }
    result = oss.str();
    return result;
}
void Letter::print(){
    std::string result = get_print_string();
    std::cout << result << std::endl;
}
