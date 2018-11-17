/*
 Exercise P9.15.
 Write a program copyfile that copies one file to another. The file names are specified on the command line. For example:
 copyfile report.txt report.sav
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 3){
        cout << "Error. Invalid number of arguments (" << argc << " given)." << endl;
        exit(1);
    }
    string dir = "/Users/christianmeyer/cpp/ch9/P9_15/";
    string input_file = dir + argv[1];
    string output_file = dir + argv[2];
    
    vector<string> lines;
    string line;
    
    ifstream ifs(input_file.c_str());
    ofstream ofs(output_file.c_str(), ios::trunc);
    
    while (getline(ifs, line)){
        lines.push_back(line);
        ofs << line;
    }
    
    ifs.close();
    ofs.close();
    
    return 0;
}
