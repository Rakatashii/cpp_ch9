/*
 Exercise P9.6. Junk mail.
 Write a program that reads in two files: a template and a database. The template file contains text and tags. The tags have the form |1| |2| |3|... and need to be replaced with the first, second, third, ... field in the current database record.
 
 A typical database looks like this:
 Mr.|Harry|Hacker|1105 Torre Ave.|Cupertino|CA|95014
 Dr.|John|Lee|702 Ninth Street Apt. 4|San Jose|CA|95109
 Miss|Evelyn|Garcia|1101 S. University Place|Ann Arbor|MI|48105
 
 And here is a typical form letter:
 To:
 |1| |2| |3|
 |4|
 |5|, |6| |7|
 Dear |1| |3|:
 You and the |3| family may be the lucky winners of $10,000,000 in the C++
 compiler clearinghouse sweepstakes! ...
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "junkmail.hpp"

using namespace std;

string jm_template = " To: |1| |2| |3|\n|4| \n|5|, |6| |7| \nDear |1| |3|: \nYou and the |3| family may be the lucky winners of $10,000,000 in the C++ compiler clearinghouse sweepstakes! ...";

int main(int argc, const char * argv[]) {
    vector<string> dblines;
    string line;
    string templ;
    string db_file = "/Users/christianmeyer/cpp/ch9/P9_6/database";
    string template_file = "/Users/christianmeyer/cpp/ch9/P9_6/template";
    ifstream ifs(db_file.c_str());
    while (getline(ifs, line)){
        dblines.push_back(line);
    }
    ifs.close();
    ifs.open(template_file.c_str());
    if (ifs.peek() != -1){
        while (getline(ifs, line)){
            templ += line;
            if (ifs.peek() != -1){
                templ += "\n";
            }
        }
        if (templ.size() <= 1){
            templ = jm_template;
        }
    } else {
        templ = jm_template;
    }

    vector<JunkMail*> mail;
    //cout << "template: \n" << templ << endl;
    
    for (int i = 0; i < dblines.size(); i++){
        mail.push_back(new JunkMail(dblines[i], templ));
        //cout << "dblines[" << i << "]: " << dblines[i] << endl;
    }
    /*
    for (int i = 0; i < mail.size(); i++){
        vector<string> mailtags = mail[i]->get_tags();
        cout << "mail[" << i << "]" << endl;
        for (int j = 0; j < mailtags.size(); j++){
            cout << "   tag[" << j << "]: " << mailtags[j] << endl;
        }
    }
     */
    cout << "\n\n";
    
    for (int i = 0; i < mail.size(); i++){
        /*
        vector<string> filled_template = mail[i]->get_filled_template_vector();
        for (int j = 0; j < filled_template.size(); j++){
            cout << "FT[" << j << "]: " << filled_template[j] << endl;
        }
        */
        cout << "FT[" << i << "]: \n" << mail[i]->get_filled_template_string() << endl;
        mail[i] = NULL;
        delete mail[i];
        cout << "\n";
    }
    
    return 0;
}
