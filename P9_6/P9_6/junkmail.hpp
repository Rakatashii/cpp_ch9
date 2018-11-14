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

#ifndef junkmail_hpp
#define junkmail_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

extern std::string jm_template;

class JunkMail{
public:
    JunkMail();
    JunkMail(std::string l, std::string t = jm_template, int n = 0);
    void make_tags();
    void fill_templ();
    std::vector<std::string> get_tags();
    std::string get_dbline() const;
    std::string get_template() const;
    std::vector<std::string> get_filled_template_vector() const;
    std::string get_filled_template_string() const;
private:
    std::string dbline, templ;
    std::vector<std::string> tags;
    std::vector<std::string> filled_templ;
    int num_fields;
};

#endif /* junkmail_hpp */
