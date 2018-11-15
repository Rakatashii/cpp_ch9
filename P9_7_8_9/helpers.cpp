#include "helpers.hpp"

using namespace HELPERS;

void swap(std::vector<std::string> &v, int i, int j);

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
int HELPERS::get_sum_buffer_sizes(std::vector<int> bs, int current_index){
    int total_before_current = 0;
    for (int i = 0; i < (current_index); i++){
        total_before_current += (bs[i]);
    }
    return total_before_current+current_index;
};
bool HELPERS::check_for_header(std::fstream& fs){
    std::string first_line;
    getline(fs, first_line);
    int line_length = first_line.length();
    int caps_count = 0;
    for (int i = 0; i < line_length; i++){
        if (((int)first_line[i] >= 65) && ((int)first_line[i] <= 90)){
            caps_count++;
        }
    }
    if (caps_count >= 25){
        return true;
    }
    return false;
}
// just pass opened fstream obj and close after calling function.
void HELPERS::sort_lines_by_field(std::vector<int> bs, std::fstream& fs, std::string file, int employee_field_index, std::string new_output){
    fs.open(file.c_str(), std::ios::in | std::ios::out);
    std::vector<std::string> lines;
    std::vector<std::string> sublines;
    bool header = HELPERS::check_for_header(fs);
    int current_line = 0;
    fs.seekg(0, std::ios::beg);
    
    int line_length = 0;
    do {
        line_length++;
    } while (fs.get() != '\n');
    fs.seekg(0, std::ios::end);
    int file_length = fs.tellg();
    fs.seekg(0, std::ios::beg);
    int num_records = file_length/line_length;
    if (header) num_records--;

    fs.close();
    fs.open(file.c_str(), std::ios::in | std::ios::out);
    
    std::string line, header_line;
    std::string subline;
    int initial_pos = fs.tellg(), seekg_pos = 0;
    fs.clear();
    int lines_index = 0, sublines_index = 0;
    
    while (current_line <= num_records){
        fs.seekg((line_length * current_line), std::ios::beg);
        seekg_pos = fs.tellg();
        
        getline(fs, line);
        line += "\n";
        
        if (header && current_line == 0){
            header_line = line;
        }
        if (header && current_line > 0){
            lines.push_back(line);
            lines_index++;
        } else if (!header){
            lines.push_back(line);
            lines_index++;
        }
        
        subline = line.substr(get_sum_buffer_sizes(bs, employee_field_index), bs[employee_field_index]);
        if (header && current_line > 0){
            sublines.push_back(subline);
            sublines_index++;
        } else if (!header){
            sublines.push_back(subline);
            sublines_index++;
        }
        ++current_line;
    }

    std::vector<std::string> temp_lines, temp_sublines;
    for (int i = lines.size()-1; i >= 0; i--){
        temp_lines.push_back(lines[i]);
        temp_sublines.push_back(sublines[i]);
    }
    sublines = temp_sublines;
    
    bool sorted = false;
    while (!sorted){
        int correct_count = 0;
        for (int i = 1; i < sublines.size(); i++){
            int j = 0;
            if ((int)sublines[i-1][j] > (int)sublines[i][j]){
                swap(sublines, i-1, i);
                swap(temp_lines, i-1, i);
                break;
            }
            else if ((int)sublines[i-1][j] == (int)sublines[i][j]){
                bool same_letter = true;
                while (same_letter){
                    ++j;
                    if ((int)sublines[i-1][j] > (int)sublines[i][j]){
                        swap(sublines, i-1, i);
                        swap(temp_lines, i-1, i);
                        correct_count = 0;
                        break;
                    } else if (sublines[i-1][j] < sublines[i][j]){
                        same_letter = false;
                        correct_count++;
                    }
                }
            } else correct_count++;
            
            if (correct_count >= num_records-1) sorted = true;
        }
    }
    lines.clear();
    lines.push_back(header_line);
    for (int i = 0; i < temp_lines.size(); i++){
        lines.push_back(temp_lines[i]);
    }
    
    if (fs.is_open()) fs.close();
    if (new_output == "0") new_output = file;
    fs.open(new_output.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
    
    for (int i = 0; i < lines.size(); i++){
        fs << lines[i];
    }
    
    fs.close();
}
int HELPERS::binary_search_by_field(std::vector<int> bs, std::fstream& fs, std::string file, int employee_field_index, std::string search, bool whole_line){
    fs.open(file.c_str(), std::ios::in | std::ios::out);
    std::vector<std::string> lines;
    std::vector<std::string> sublines;
    int current_line = 0;
    fs.seekg(0, std::ios::beg);
    int line_length = 0;
    do {
        line_length++;
    } while (fs.get() != '\n');
    fs.seekg(0, std::ios::end);
    int file_length = fs.tellg();
    fs.seekg(0, std::ios::beg);
    int num_records = file_length/line_length;
    fs.close();
    
    fs.open(file.c_str(), std::ios::in | std::ios::out);
    std::string line, subline;
    fs.clear();
    
    bool no_match = true;
    int start = 0, end = num_records;
    while (no_match){
        current_line = (start+end) / 2;
        fs.seekg((line_length*current_line)+get_sum_buffer_sizes(bs, employee_field_index), std::ios::beg);
        int return_index = fs.tellg();
        if (whole_line) return_index -= get_sum_buffer_sizes(bs, employee_field_index);
        
        for (int i = 0; i < search.length(); i++){
            //std::cout << "current_line: " << current_line << std::endl;
            char c = fs.get();
            int match_count = 0;

            if (c == search[i]){
                for (int j = 1; j < search.length(); j++){
                    c = fs.get();
                    //std::cout << "c = " << c << std::endl;
                    //std::cout << "search[" << j << "] = " << search[j] << std::endl;
                    if (c == search[j]){
                        match_count++;
                        if (match_count >= search.length()-1){
                            fs.close();
                            return return_index;
                        }
                    } else {
                        break;
                    }
                }
            } else if ((int)c > (int)search[i]){
                end = current_line;
            } else if ((int)c < (int)search[i]){
                start = current_line;
            }
        }
    }
    fs.close();
    return 0;
}

void swap(std::vector<std::string> &v, int i, int j){
    std::string temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}






