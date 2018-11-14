/*
 Exercise P9.3. Letter frequencies.
 If you encrypt a file using the cipher of Exercise P9.2, it will have all of its letters jumbled up, and will look as if there is no hope of decrypting it without knowing the keyword. Guessing the keyword seems hopeless too. There are just too many possible keywords. However, someone who is trained in decryption will be able to break this cipher in no time at all. The average letter frequencies of English letters are well known. The most common letter is E, which occurs about 13 percent of the time. Here are the average frequencies of the letters (see [5]).
 
 Write a program that reads an input file and displays the letter frequencies in that file. Such a tool will help a code breaker. If the most frequent letters in an encrypted file are H and K, then there is an excellent chance that they are the encryptions of E and T.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "letter.hpp"

using namespace std;

vector<Letter*> get_frequencies (string text);

int main(int argc, const char * argv[]) {
    string filename = "/Users/christianmeyer/cpp/ch9/P9_3/input";
    
    ifstream ifs(filename.c_str());
    string text, sentence;
    while (getline(ifs, sentence)){
        text += sentence;
        if (ifs.peek() != -1){
            text += "\n";
        }
    }
    ifs.close();
    
    ifs.open(filename);
    int num_letters = 0;
    while(!ifs.eof()){
        char c;
        ifs.get(c);
        num_letters++;
    }
    ifs.close();
    
    cout << "num_letters: " << num_letters << endl;
    vector<Letter*> freqs = get_frequencies(text);
    for (int i = 0; i < freqs.size(); i++){
        freqs[i]->set_total(num_letters);
        string result = freqs[i]->get_print_string();
        cout << result << endl;
    }
    
    cout << "\n";
    return 0;
}

vector<Letter*> get_frequencies (string text){
    vector<Letter*> frequencies;

    for (int i = 0; i < text.size(); i++){
        char let = text[i];
        if (frequencies.size() > 0){
            bool match = false;
            for (int j = 0; j < frequencies.size(); j++){
                if (let == frequencies[j]->get_letter()){
                    match = true;
                    frequencies[j]->incr();
                    goto endj;
                }
            }
            if (match == false){
                frequencies.push_back(new Letter(let));
            }
            endj: {}
        } else {
            frequencies.push_back(new Letter(let));
        }
    }
    return frequencies;
}

