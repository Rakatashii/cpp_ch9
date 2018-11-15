#include "junkmail.hpp"

extern std::string jm_template;

JunkMail::JunkMail(){
    templ = jm_template;
    num_fields = 0;
}
JunkMail::JunkMail(std::string l, std::string t, int n){
    dbline = l;
    templ = t;
    num_fields = n;
    this->make_tags();
    if (num_fields == 0){
        num_fields = tags.size();
    }
    this->fill_templ();
}
void JunkMail::make_tags(){
    int start = 0, end = 0;
    for (int i = 0; i < dbline.length(); i++){
        if (i == dbline.length()-1){
            tags.push_back( dbline.substr(start, ((dbline.length()-1)-start)) );
        } else if (dbline[i] == '|'){
            end = i;
            tags.push_back(dbline.substr(start, (end-start)));
            start = i+1;
        }
    }
}
void JunkMail::fill_templ(){
    int start = 0, end = 0;
    std::string line = "";
    
    for (int j = 0; j < templ.length(); j++){
        int size = templ.length();
        if ((templ[j] == '\n') || (j == (templ.length()-1))){
            end = j;
            line += templ.substr(start, (end-start)+1);
            if (j+1 < templ.length()-1){
                start = j+1;
            }
            filled_templ.push_back(line);
            line = "";
        }
        else if ((templ[j-2] == '|') && (templ[j] == '|')){
            int n = (int)(templ[j-1]-(int)('0'))-1;
            
            if ((n >= 0) && (n < num_fields)){
                end = j;
                line += templ.substr(start, (end-start)-2);
                if (j+1 < templ.length()-1){
                    start = j+1;
                }
                line += tags[n];
            }
        }
    }
end_loop: {}
}

std::vector<std::string> JunkMail::get_tags(){
    return tags;
}
std::string JunkMail::get_dbline() const{
    return dbline;
}
std::string JunkMail::get_template() const{
    return templ;
}
std::vector<std::string> JunkMail::get_filled_template_vector() const{
    return filled_templ;
}
std::string JunkMail::get_filled_template_string() const{
    std::string filled_templ_string;
    for (int i = 0; i < filled_templ.size(); i++){
        filled_templ_string += filled_templ[i];
    }
    return filled_templ_string;
}

