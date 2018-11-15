#ifndef helpers_hpp
#define helpers_hpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "employee.hpp"

namespace HELPERS{
    extern int max_record_size(std::istream& ifs, std::string file);
    
    extern int max_tag_size(std::vector<std::vector<std::string> > tags, int tag_index);
    
    extern std::vector<std::vector<std::string> > make_tags(std::fstream& fs);
    
    extern void output_new_buf_sizes(std::vector<std::vector<std::string> > tags, std::vector<int>& buffer_sizes, std::ofstream& out, std::string output_file, std::vector<std::string> header_fields = std::vector<std::string>());
    
    extern void print_employees(std::vector<Employee*> employees);
    
    //extern std::vector<Employee*> make_employees_with_tags(std::vector<std::vector<std::string> > tags);
    
    extern int get_sum_buffer_sizes(std::vector<int> bs, int current_index);
    extern bool check_for_header(std::fstream& fs);
    extern void sort_lines_by_field(std::vector<int> bs, std::fstream& fs, std::string file, int employee_field_index, std::string new_output = "0");
    extern int binary_search_by_field(std::vector<int> bs, std::fstream& fs, std::string file, int employee_field_index, std::string search, bool whole_line = false);
    
    //extern find_by_name(std::string name, ifstream& ifs, int )
};

#endif /* helpers_hpp */





