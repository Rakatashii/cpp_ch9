/*
 P9_17:
 Write a program find that searches all files specified on the command line and prints out all lines containing a keyword. For example, if you call:
 'find Tim report.txt address.txt homework.cpp'
 then the program might print
 report.txt: discussed the results of my meeting with Tim T
 address.txt: Torrey, Tim|11801 Trenton Court|Dallas|TX
 address.txt: Walters, Winnie|59 Timothy Circle|Detroit|MI
 homework.cpp: Time now;
 The keyword is always the first command line argument.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

bool match(string sub, string full);
vector<int> get_start_end(string sub, string full, bool& success);

int main(int argc, const char * argv[]) {
    if (argc < 4){
        cout << "Invalid number of arguments (" << argc << " given)." << endl;
        exit(1);
    }
    
    bool full_file_names = false;
    string keyword = argv[1];
    if (strcmp(argv[1], "-f") == 0){
        full_file_names = true;
        keyword = argv[2];
    }
    
    string dir = "/Users/christianmeyer/cpp/ch9/P9_17/";
    vector<string> matched_lines;
    
    string color_start = "\e[1;32m";
    string color_end = "\e[0m";
    
    
    int i = 2;
    if (full_file_names){
        i = 3;
    }
    for (i = i; i < argc-1; i++){
        string file = argv[i];
        
        ifstream ifs((dir+file).c_str());
        string line;
        int k = 0;
        while (getline(ifs, line, '.')){
            string msg = file + " [line ";
            if (full_file_names){
                msg = dir+file + " [line ";
            }
            //cout << "line " << k << ": " << line << endl;
            if (match(keyword, line)){
                ostringstream oss;
                oss << k;
                msg += oss.str() + "]:";
                //line = msg + line + "\n";
                bool success = false;
                
                vector<int> start_end = get_start_end(keyword, line, success);
                if (success){
                    line.insert(start_end[0], color_start);
                    line.insert((start_end[1]+color_start.length())+2, color_end);
                }
                matched_lines.push_back(msg+line);
            }
            k++;
        }
        ifs.close();
    }
    
    if (matched_lines.size() == 0){
        cout << "No lines match keyword " << keyword << "." << endl;
    }
    else {
        cout << matched_lines.size() << " lines matching keyword '" << keyword << "':" << endl;
        for (int i = 0; i < matched_lines.size(); i++){
            cout << matched_lines[i] << endl;
        }
    }
    
    return 0;
}

bool match(string sub, string full){
    int sub_length = sub.length();
    int full_length = full.length();
    for (int i = 0; i < (full_length-sub_length); i++){
        if (full.compare(i, sub_length, sub) == 0){
            return true;
        }
    }
    return false;
}
vector<int> get_start_end(string sub, string full, bool& success){
    vector<int> start_end;
    success = false;
    if (match(sub, full)){
        int start = 0, end = 0;
        for (int i = 0; i < full.length(); i++){
            int j = 0;
            if (sub[j] == full[i]){
                int count = 1;
                int start = i, temp_i = i;
                i++;
                j++;
                while (sub[j] == full[i]){
                    count++;
                    if (count >= sub.length()){
                        end = i;
                        start_end.push_back(start);
                        start_end.push_back(end);
                        success = true;
                        goto end;
                    }
                    j++;
                    i++;
                }
                i = temp_i;
            }
        }
    }
end:{}
    return start_end;
}
