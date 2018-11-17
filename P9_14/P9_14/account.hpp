#ifndef account_hpp
#define account_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

class Account {
public:
    Account();
    Account(std::string acc_num);
    Account(std::string acc_num, std::string initial_balance);
    void make_numeric_account_number();
    void make_numeric_balance();
    void numeric_balance_to_balance();
    void numeric_account_to_account();
    std::string get_balance();
    void deposit(long double d);
    void withdraw(long double w);
    
    void set_balance(long double b);
    std::string get_account_number();
    long int get_numeric_account_number() const;
    // v losing decimal precision here with String#stold - find good alternative
    long double get_numeric_balance() const;
    void print_account_number() const;
    void print_balance() const;
private:
    std::string account_number, balance;
    long int numeric_account_number;
    long double numeric_balance;
};

#endif /* account_hpp */
