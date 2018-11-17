#include "account.hpp"

Account::Account(){
    balance = "";
    account_number = "";
    make_numeric_balance();
    make_numeric_account_number();
}
Account::Account(std::string acc_num){
    balance = "";
    account_number = acc_num;
    make_numeric_balance();
    make_numeric_account_number();
}
Account::Account(std::string acc_num, std::string initial_balance){
    account_number = acc_num;
    balance = initial_balance;
    make_numeric_account_number();
    make_numeric_balance();
};
void Account::make_numeric_account_number(){
    numeric_account_number = std::stol(account_number, nullptr);
};
void Account::make_numeric_balance(){
    if (balance[0] == '$') numeric_balance = std::stold(balance.substr(1));
    else numeric_balance = std::stold(balance);
};
void Account::numeric_account_to_account(){
    std::ostringstream oss;
    oss << numeric_account_number;
    account_number = oss.str();
};
void Account::numeric_balance_to_balance(){
    std::ostringstream oss;
    oss << '$';
    oss << numeric_balance;
    balance = oss.str();
}
std::string Account::get_balance(){
    numeric_balance_to_balance();
    return balance;
}
void Account::deposit(long double d) {
    numeric_balance += d;
    numeric_balance_to_balance();
};
void Account::withdraw(long double w) {
    numeric_balance -= w;
    numeric_balance_to_balance();
};
void Account::set_balance(long double b){
    numeric_balance = b;
    numeric_balance_to_balance();
}
std::string Account::get_account_number(){
    numeric_account_to_account();
    return account_number;
};
long int Account::get_numeric_account_number() const{
    return numeric_account_number;
};
long double Account::get_numeric_balance() const{
    return numeric_balance;
}
void Account::print_account_number() const{
    std::cout << "account number: " << account_number << std::endl;
};
void Account::print_balance() const{
    std::cout << "balance: " << balance << std::endl;
};

/*
private:
std::string account_number;
int numeric_account_number;
double balance;
*/
