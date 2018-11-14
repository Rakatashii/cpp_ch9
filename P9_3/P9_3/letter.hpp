#ifndef letter_hpp
#define letter_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Letter {
public:
    Letter();
    Letter(char c);
    void incr();
    void set_total(int t);
    int get_total() const;
    void calc_frequency();
    double get_frequency();
    char get_letter() const;
    int get_count() const;
    std::string get_print_string();
    void print();
private:
    char let;
    int count, total;
    double frequency;
};

#endif /* letter_hpp */
