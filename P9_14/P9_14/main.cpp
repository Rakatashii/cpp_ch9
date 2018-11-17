/*
 Exercise P9.14.
 A bank keeps all bank accounts in a random access file in which each line has the format
 'account_number balance'
 Write a program that simulates an automatic teller machine. A user can deposit money to an account by specifying the account number and amount, withdraw money, query the account balance, or transfer money from one account to another.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "account.hpp"
#include <cstdlib>
#include <cmath>

using namespace std;

void print_accounts(vector<Account*> accounts);

int main(int argc, const char * argv[]) {
    string proj_dir = "/Users/christianmeyer/Cpp/ch9/P9_14/";
    string accounts_file = proj_dir + "accounts.txt";
    vector<Account*> accounts;
    
    fstream fs(accounts_file.c_str());
    string account_number, balance;
    while (getline(fs, account_number, '|')){
        getline(fs, balance, '\n');
        Account* acc = new Account(account_number, balance);
        accounts.push_back(acc);
    }
    fs.close();
    
    srand(time(NULL));
    for (int i = 0; i < accounts.size(); i++){
        long double rand_d = rand()%20000+1;
        long double rand_w = rand()%40000+1;
        accounts[i]->deposit(rand_d);
        if (rand_w <= accounts[i]->get_numeric_balance()){
            accounts[i]->withdraw(rand_w);
        }
    }
    //print_accounts(accounts);
    
    fs.open(accounts_file.c_str(), ios::in | ios::out);
    fs.seekg(0, ios::beg);
    int i = 0;
    string line;
    
    for (int i = 0; i < accounts.size(); i++){
        getline(fs, line, '|');
        int pos = fs.tellg();
        fs.seekp(pos, ios::beg);
        cout << "tellg: " << pos << endl;
        cout << "tellp: " << fs.tellp() << endl;
        cout << "accounts[i]->get_numeric_balance: " << accounts[i]->get_numeric_balance() << endl;
        cout << "accounts[i]->get_balance: " << accounts[i]->get_balance() << endl;
        // The problems from before seemed to stem from not setting these stream manipulators
        fs << left << setprecision(2) << setw(10) << accounts[i]->get_balance();
    }
    fs.close();

    print_accounts(accounts);
    
    return 0;
}

void print_accounts(vector<Account*> accounts){
    for (int i = 0; i < accounts.size(); i++){
        cout << "accounts[" << i << "]" << endl;
        cout << "    ";
        accounts[i]->print_account_number();
        cout << "    ";
        accounts[i]->print_balance();
        cout << fixed << setprecision(2) << "    " << "numeric_balance: $" << accounts[i]->get_numeric_balance() << endl;
    }
}
