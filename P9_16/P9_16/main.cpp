/*
 Exercise P9.16.
 Write a program that concatenates the contents of several files into
 one file. For example:
 catfiles chapter1.txt chapter2.txt chapter3.txt book.txt
 makes a long file book.txt that contains the contents of the files chapter1.txt, chapter2.txt, and chapter3.txt. The target file is always the last file specified on the command line.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool line_is_empty(string line);

/* command line: './program_name -at FILE1 FILE2 ... OUTPUT_FILE'
    -a flag signals that OUTPUT_FILE should be appended to, rather than truncating every time. This is the default behavior.
    -t says to truncate OUTPUT_FILE before appending the contents of FILE1..FILEn to it.
*/

int main(int argc, const char * argv[]) {
    if (argc < 3){
        cout << "Invalid number of arguments (" << argc << " provided)." << endl;
        exit(1);
    }
    vector<string> lines;
    string dir = "/Users/christianmeyer/cpp/ch9/P9_16/";
    string output = dir + argv[argc-1];
    
    bool trunc_first  = false;
    bool optional_given = false;
    if (strncmp(argv[1], "-a", 2) == 0){
        string arg1 = argv[1];
        cout << arg1 << ": output file will be appended to only.\n";
        optional_given = true;
    } else if (strncmp(argv[1], "-t", 2) == 0){
        string arg1 = argv[1];
        cout << arg1 << ": output file will be truncated.\n";
        trunc_first = true;
        optional_given = true;
    }
    
    ofstream ofs;
    for (int i = 1; i < argc-1; i++){
        if (optional_given && i == 1) i++;
        string file = dir + argv[i];
        ifstream ifs(file.c_str());
        if (ifs.fail()){
            cout << "Could not open file " << argv[i] << endl;
            exit(1);
        }
        string line;
        
        // Now working. Problem before was using open, ios::trunc just to clear the file, which added a blank line at the beginning of the file. This if else logic ensures that the ostream obj with ios::trunc will actually output lines if it needs to be called.
        if ((i == 1 && trunc_first) || (i == 2 && optional_given && trunc_first)){
            ofs.open(output.c_str(), ios::trunc);
            if (ofs.fail()){
                cout << "Could not output to file " << argv[i] << endl;
                exit(1);
            }
            while (getline(ifs, line)){
                if (line_is_empty(line)){
                    break;
                }
                else ofs << line;
            }
            ofs.close();
        } else {
            ofstream ofs(output.c_str(), ios::app | ios::out);
            if (ofs.fail()){
                cout << "Could not output to file " << argv[i] << endl;
                exit(1);
            }
            while (getline(ifs, line)){
                if (line_is_empty(line)){
                    break;
                }
                else ofs << line;
            }
            ofs.close();
        }
    }
    
    return 0;
}

bool line_is_empty(string line){
    for (int i = 0; i < line.length()-1; i++){
        if (line[i] != '\n' && line[i] != ' '){
            return false;
        }
    }
    return true;
}
