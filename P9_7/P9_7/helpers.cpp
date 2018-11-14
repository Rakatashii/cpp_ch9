#include "helpers.hpp"

using namespace HELPERS;

int HELPERS::max_record_size(std::istream& ifs, std::string file){
    std::string line;
    int total = 0, count = 0;
    while (!ifs.eof() ){
        getline(ifs, line);
        total += line.length();
        count++;
    }
    int avg = total/count;
    return avg;
};
int HELPERS::max_tag_size(std::vector<std::vector<std::string> > tags, int tag_index){
    int max = 0;
    for (int i = 0; i < tags.size(); i++){
        if (tags[i][tag_index].length() > max){
            max = (int)(tags[i][tag_index].length());
        }
    }
    return max;
};
void HELPERS::output_new_buf_sizes(std::vector<std::vector<std::string> > tags, std::vector<int>& buffer_sizes, std::ofstream& out, std::string output_file, std::vector<std::string> header_fields){
    out.open(output_file.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
    if (out.fail()){
        std::cout << "Could not open file " << output_file << std::endl;
        exit(1);
    }
    if (header_fields.size() != 0){
        for (int i = 0; i < header_fields.size(); i++){
            int buffer_size = buffer_sizes[i];
            if (header_fields[i].length() > buffer_size){
                buffer_sizes[i] = header_fields[i].length();
            }
            if (i == header_fields.size()-1){
                out << std::left << std::setw(buffer_size) << header_fields[i] << '\n';
            }
            else {
                out << std::left << std::setw(buffer_size) << header_fields[i] << '|';
            }
        }
    }
    for (int i = 0; i < tags.size(); i++){
        for (int j = 0; j < tags[i].size(); j++){
            int buffer_size = buffer_sizes[j];
            if (j == tags[i].size()-1){
                out << std::left << std::setw(buffer_size) << tags[i][j] << '\n';
            } else {
                out << std::left << std::setw(buffer_size) << tags[i][j] << '|';
            }
        }
    }
    //out.close(); do this in main actually
};
std::vector<std::vector<std::string> > HELPERS::make_tags(std::fstream& fs){
    std::vector<std::vector<std::string> > all_tags;
    std::string line;
    while (getline(fs, line)){
        std::vector<std::string> line_tags;
        int start = 0, end = 0;
        for (int i = 0; i < line.length(); i++){
            if (i == line.length()-1){
                line_tags.push_back(line.substr(start, i));
                all_tags.push_back(line_tags);
                line_tags.clear();
            }
            if (line[i] == '|'){
                end = i;
                line_tags.push_back(line.substr(start, end-start));
                start = i+1;
            }
        }
    }
    return all_tags;
};
void HELPERS::print_employees(std::vector<Employee*> employees){
    for (int i = 0; i < employees.size(); i++){
        std::cout << "*employees[" << i << "]" << std::endl;
        for (int j = 0; j < employees[i]->size(); j++){
            std::cout << "   *((*employees[" << i << "])[" << j << "]) = " << *((*employees[i])[j]) << std::endl;
        }
    }
};






