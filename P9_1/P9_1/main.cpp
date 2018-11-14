/*
 Exercise P9.1. Write a program that asks the user for a file name and displays the number of characters, words, and lines in that file. Then have the program ask for the name of the next file. When the user enters a file that doesn’t exist (such as the empty string), the program should exit.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    string name;
    cout << "name: ";
    // cin buffer still terminated by whitespace - use getline.
    getline(cin, name);
    
    string file_name = "/Users/christianmeyer/cpp/ch9/P9_1/P9_1/namefile.txt";
    ofstream out;
    out.open(file_name, ios::in | ios::out | ios::app);
    
    out << name << endl;
    out.close();
    
    ifstream inn(file_name.c_str());
    
    int num_characters = 0, num_words = 0, num_lines = 0;
    string w, l;
    char c;
    
    int idx = 0;
    while (getline(inn, l)){
        idx++;
    }
    num_lines = idx; idx = 0;
    cout << "num_lines = " << num_lines << endl;
    
    inn.close();
    inn.open(file_name.c_str());
    
    while (inn >> w){
        idx++;
    }
    num_words = idx; idx = 0;
    cout << "num_words = " << num_words << endl;
    
    inn.close();
    inn.open(file_name.c_str());
    
    while (inn.get(c)){
        idx++;
    }
    num_characters = idx; idx = 0;
    cout << "num_characters = " << num_characters << endl;
    inn.close();
    
    return 0;
}
