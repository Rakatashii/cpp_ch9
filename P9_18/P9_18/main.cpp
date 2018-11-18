/*
 Exercise P9.18.
 Write a program that checks the spelling of all words in a file. It should read each word of a file and check whether it is contained in a word list. A word list is available on most UNIX systems in the file /usr/dict/words. The program should print out all words that it cannot find in the word list.
*/

/*
 This program prints the contents of the input file to the console in color - green denotes a correctly spelled word while red denotes a misspelled word.
 To run the program call: './program INPUT_FILE OUTPUT_FILE'
    - INPUT_FILE is optional. If not provided a file called "${project_directory}/roughdraft" is used instead.
    - OUTPUT_FILE is also optional. If not provided then output will only be displayed on the console and no file will be given ouput.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int> > get_dict_indices(fstream& fs, string file);
bool correct_spelling(string word, vector<vector<int> > indices, fstream& fs, string file);
bool is_letter(char c);
bool is_space(char c);

int main(int argc, const char * argv[]) {
    bool display_colors = true;
    string env = argv[0];
    if (env == "/Users/christianmeyer/Cpp/ch9/P9_18/Build/Products/Debug/P9_18"){
        display_colors = false;
    }
    
    string dir = "/Users/christianmeyer/cpp/ch9/P9_18/";
    string roughdraft = dir + "roughdraft"; // this is the default input file, which will not be used at all if an input file is provided in argv[1]
    string dict_file = dir + "words"; // this is '/usr/share/dict' copied to the project directory
    string input_file;
    string output_file = "NONE"; // No output file unless one is provided in argv[2]
    if (argc>1){
        input_file = dir+argv[1];
    } else input_file = roughdraft;
    if (argc>2){
        output_file = dir+argv[2];
    }
    
    const string red_start = "\033[0;30m"; //10
    const string red_end = "\033[0m"; //7
    const string green_start = "\033[0;32m"; //10
    const string green_end = "\033[0m"; //7

    fstream fs;
    vector<vector<int> > indices = get_dict_indices(fs, dict_file);
    
    vector<string> lines;
    fs.open(input_file.c_str());
    string line;
    string corrected_line;
    while (getline(fs, line, '.') && !fs.eof()){
        
        string word;
        fstream fs2;
        int start = 0;
        int end = 0;
        
        if (line.size() >= 1){
            for (int i = 0; i < line.size(); i++){
                while (!is_space(line[i])){
                    if (i >= line.size()) goto space;
                    word+=line[i];
                    i++;
                }
                if (is_space(line[i]) || i >= line.size()-1){
                space: {}
                    if (word.size() == 0){
                        word.clear();
                        goto ipp;
                    }
                
                    bool correct = correct_spelling(word, indices, fs2, dict_file);
                    if (is_space(line[i])) word+=line[i];
                    
                    string temp_word = word;
                    if (correct) {
                        word = green_start + temp_word;
                        word += green_end;
                    } else {
                        word = red_start + temp_word;
                        word += red_end;
                    }
                    corrected_line += word;
                    word.clear();
                }
                ipp: {}
            }
            if (corrected_line.size() > (red_start.size()+red_end.size())){
                corrected_line += '.';
                lines.push_back(corrected_line);
            }
            corrected_line.clear();
        }
    }
    fs.close();
    cout << "\n";
    
    if (output_file != "NONE"){
        fs.open(output_file.c_str(), ios::out | ios::trunc);
        for (int i = 0; i < lines.size(); i++){
            fs << lines[i] << endl;
        }
        fs.close();
    }
    cout << "Color ouput: " << endl;
    for (int i = 0; i < lines.size(); i++){
        cout << lines[i] << endl;
    }
    
    cout << endl;
    return 0;
}
bool correct_spelling(string word, vector<vector<int> > indices, fstream& fs, string file){
    if (indices.size() == 0) {
        cout << "Error: indicies.size() == 0" << endl;
        return false;
    } else if (indices[0].size() == 0){
        cout << "Error: vectors in indices are empty." << endl;
        return false;
    }
    int letter_int = (int)word[0];
    if (letter_int >= 97 && letter_int <= 122){
        letter_int -= 32;
        word[0] = char(letter_int);
    }
    int k = 0;
    while (k < word.length()){
        if ((int)word[k] < 65 || ((int)word[k] > 90 && (int)word[k] < 97) || (int)word[k] > 122){
            word.erase(k, 1);
        }
        if (word[k] == ' '){
            word.erase(k, 1);
        }
        ++k;
    }
    cout << "...scanning for '" << word << "'" << endl;
    int target_index = -1;
    vector<int> letter_ints = indices[0];
    for (int i = 0; i < letter_ints.size(); i++){
        //cout << "letter_ints[" << i << "] " << letter_ints[i] << endl;
        if (letter_int == letter_ints[i] || letter_int + 32 == letter_ints[i]){
            target_index = i;
        }
    }
    if (target_index == -1){
        cout << "letter_int not found in letter_ints vector." << endl;
        return false;
    }
    
    fs.open(file.c_str());
    int start_pos = indices[1][target_index];
    int end_pos = indices[2][target_index];
    fs.seekg(start_pos, ios::beg);
    string line;
    while (getline(fs, line)){
        if (word == line){
            fs.close();
            return true;
        } else {
            char first = line[0];
            if ((int)first >= 65 && (int)first <= 90){
                first += 32;
                line = first + line.substr(1);
            }
            else if ((int)first >= 97 && (int)first <= 122){
                first -= 32;
                line = first + line.substr(1);
            }
            if (word == line){
                fs.close();
                return true;
            }
        }
        int pos = fs.tellg();
        if (pos >= end_pos){
            fs.close();
            return false;
        }
    }
    fs.close();
    return false;
}
vector<vector<int> > get_dict_indices(fstream& fs, string file){
    vector<int> letter_ints;
    vector<int> start_indices;
    vector<int> end_indices;

    int lower_let = (int)'a';
    int upper_let = (int)'A';
    fs.open(file.c_str(), ios::in | ios::out);

    string word;
    int start = 0, end = 0;
    while (!fs.eof()){
        start = fs.tellg();
        fs >> word;
        end = fs.tellg();
        int word_count = 0;
        
        while (((int)word[0] == upper_let || (int)word[0] == (upper_let+32)) && !fs.eof()){
            //cout << "word: " << word << endl;
            if (word_count == 0){
                letter_ints.push_back((int)word[0]);
                start_indices.push_back(start);
            }
            end = fs.tellg();
            fs >> word;
            word_count++;
            if ((int)word[0] != lower_let && (int)word[0] != upper_let) {
                end_indices.push_back(end);
                lower_let++;
                upper_let++;
                word_count = 0;
                start = fs.tellg();
                start -= word.length()+1;
            }
        }
        if (start_indices.size() > end_indices.size()){
            fs.seekg(0, ios::end);
            int last_index = fs.tellg();
            end_indices.push_back(end-1);
            goto end;
        }
    }
end: {}
    fs.close();
    vector<vector<int> > indices;
    indices.push_back(letter_ints);
    indices.push_back(start_indices);
    indices.push_back(end_indices);
    return indices;
}
bool is_letter(char c){
    if ((int)c < 65 || ((int)c > 90 && (int)c < 97) || (int)c > 122) return false;
    return true;
}
bool is_space(char c){
    if ((int)c == 32) return true;
    return false;
}
