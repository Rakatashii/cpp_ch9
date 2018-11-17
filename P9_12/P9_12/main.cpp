/*
 Exercise P9.12.
 Write a program that manipulates three database files.
 The first file contains the names and telephone numbers of a group of people.
 The second file contains the names and Social Security numbers of a group of people.
 The third file contains the Social Security numbers and annual salaries of a group of people.
 The groups of people should overlap but need not be completely identical.
 Your program should ask the user for a telephone number and then print the name, Social Security number, and annual income, if it can determine that information.
*/

/*
 call the .rb file in the project directory to generate a database file filled with records:
 ./generate_data.rb -n -args -file
 -n is the number of records to generate
 -args must be comprised of at least one: "name", "telephone", "social", or "salary"
 -file is an optional file argument that will overwrite the default file name - "db"
 if the file is executed with no args or the args do not have the proper name, the db file will not look as expected
 note: Faker gem required, so no calls like 'system("cd /Users/christianmeyer/cpp/ch9/P9_11; ./generate_names.rb 20 name telephone")'
 note: optional file parameter must have an extension (like .txt) or else program will not be able to tell it is the name of a file.
 */

// Note: didn't end up using the Person class - at least that may be useful later on...

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "people.hpp"

using namespace std;

vector<string> lines_to_vect(fstream& fs, string file);
vector<vector<string> > line_fields_to_vect(fstream& fs, string file, int num_fields = 1);
void display_string_vector(vector<string> v, string vector_name = "v", bool tab = false);
bool is_numeric(string s);
void concat_fields_in_file(vector<string> v1, vector<string> v2, ofstream& ofs, string output_file);
bool str_match(string sub, string full);

int main(int argc, const char * argv[]) {
    string proj_dir = "/Users/christianmeyer/cpp/ch9/P9_11/";
    // INPUT FILES
    //string name_file = proj_dir + "name.txt";
    //string telephone_file = proj_dir + "telephone.txt";
    string name_and_telephone_file = proj_dir + "name_and_telephone.txt";
    string social_file = proj_dir + "social.txt";
    string salary_file = proj_dir + "salary.txt";
    // OUTPUT FILES
    string name_and_social_file = proj_dir + "name_and_social.txt";
    string social_and_salary_file = proj_dir + "social_and_salary.txt";
    string final_output = proj_dir + "final_output.txt";
    
    fstream fs;
    vector<string> socials = lines_to_vect(fs, social_file);
    vector<string> salaries = lines_to_vect(fs, salary_file);
    vector<string> names, telephones;
    vector<vector<string> > name_and_telephone = line_fields_to_vect(fs, name_and_telephone_file, 2);
    for (int i = 0; i < name_and_telephone.size(); i++){
        names.push_back(name_and_telephone[i][0]);
    }
    for (int i = 0; i < name_and_telephone.size(); i++){
        telephones.push_back(name_and_telephone[i][1]);
    }

    ofstream ofs;
    concat_fields_in_file(names, socials, ofs, name_and_social_file);
    vector<vector<string> > name_and_social = line_fields_to_vect(fs, name_and_social_file, 2);
    concat_fields_in_file(socials, salaries, ofs, social_and_salary_file);
    vector<vector<string> > social_and_salary = line_fields_to_vect(fs, social_and_salary_file, 2);
    
    vector<vector<string> > lines = name_and_telephone;
    for (int i = 0; i < lines.size(); i++){
        int cfi = 0; // current field index
        string lines_name = lines[i][cfi++];
        string lines_telephone = lines[i][cfi++];
        
        string NS_name = name_and_social[i][0];
        string NS_social = name_and_social[i][1];
        string SS_social = social_and_salary[i][0];
        string SS_salary = social_and_salary[i][1];

        if (str_match(lines_name, NS_name)){
            lines[i].push_back(NS_social);
            if (str_match(lines[i][cfi], SS_social)){
                lines[i].push_back(SS_salary);
            }
        }
    }
    
    for (int i = 0; i < lines.size(); i++){
        cout << "lines[" << i << "]\n";
        display_string_vector(lines[i], "fields", true);
    }
    
    ofs.open(final_output.c_str(), ios::in | ios::out | ios::trunc);
    for (int i = 0; i < lines.size(); i++){
        int line_size = lines[i].size();
        for (int j = 0; j < line_size-1; j++){
            ofs << lines[i][j] << '|';
        }
        ofs << lines[i][line_size-1] << '\n';
    }
    ofs.close();
    
    return 0;
}

bool str_match(string sub, string full){
    int count = 0;
    for (int i = 0; i < sub.length(); i++){
        for (int j = 0; j < full.length(); j++){
            if (sub[i] == full[j]){
                while (sub[i] == full[i]){
                    count++;
                    i++;
                    j++;
                    if (count >= sub.size()-1){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
void concat_fields_in_file(vector<string> v1, vector<string> v2, ofstream& ofs, string output_file){
    ofs.open(output_file.c_str(), ios::in | ios::out);
    
    int size;
    if (v1.size() == v2.size() && (v1.size() != 0)) size = v1.size();
    else exit(1);
    
    for (int i = 0; i < size; i++){
        std::cout << "got here\n";
        string str1 = v1[i], str2 = v2[i];
        std::cout << "str1: " << str1 << " | str2: " << str2 << std::endl;
        ofs << str1 << "|" << str2 << "\n";
    }
    ofs.close();
}
vector<vector<string> > line_fields_to_vect(fstream& fs, string file, int num_fields){
    fs.open(file.c_str(), ios::in | ios::out);
    vector<vector<string> > all_line_fields;
    vector<string> line_fields;
    string field;
    while (!fs.eof()){
        if (num_fields > 1){
            for (int i = 0; i < num_fields-1; i++){
                getline(fs, field, '|');
                if (field.size() > 0) line_fields.push_back(field);
            }
        }
        getline(fs, field, '\n');
        if (field.size() > 1) line_fields.push_back(field);
        if (line_fields.size() > 0) all_line_fields.push_back(line_fields);
        line_fields.clear();
    }
    fs.close();
    return all_line_fields;
}
vector<string> lines_to_vect(std::fstream& fs, string file){
    vector<string> lines;
    fs.open(file.c_str(), ios::in | ios::out);
    string line;
    while (getline(fs, line)){
        if (line.size() > 2) lines.push_back(line);
    }
    fs.close();
    return lines;
}
void display_string_vector(vector<string> v, string vector_name, bool tab){
    for (int i = 0; i < v.size(); i++){
        if (tab) cout << "    ";
        cout << vector_name << "[" << i << "]: " << v[i] << endl;
    }
}
bool is_numeric(string s){
    for (int i = 0; i < s.length(); i++){
        if (((int)s[i] < 48) || ((int)s[i] > 57)) return false;
    }
    return true;
}






