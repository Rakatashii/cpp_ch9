/*
 Exercise P9.2. Random monoalphabet cipher. The Caesar cipher, which shifts all letters by a fixed amount, is far too easy to crack. Here is a better idea. As the key, don’t use numbers but words. Suppose the key word is FEATHER. Then first remove duplicate letters, yielding FEATHR, and append the other letters of the alphabet in reverse order:
Now encrypt the letters as follows:
 Write a program that encrypts or decrypts a file using this cipher. For example,
 crypt -d -kFEATHER encrypt.txt output.txt
 decrypts a file using the keyword FEATHER. It is an error not to supply a keyword.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> separate_whitespace(string s);
string encrypt(string s, vector<char> key);
string remove_duplicates(string ciph);
vector<char> get_reverse_alphabet(string ciph = "", bool reverse = true);
string decrypt(string s, vector<char> key);
void set_command_line_variables(int argc, const char * argv[], string& input_file, string& output_file, string& key, bool& encrypt_mode);

/* to use this program set argv[1] to "-d" to decrypt (encrypts by default). If "-d" is given, set argv[2] to "-k" to indicate that a custom key will be given (defaults to "feather"). Then argv[3] is the key itself, argv[4] is the input file name, which defaults to pwd + "input.txt" and argv[5] is the output file name, which defaults to pwd + "output.txt". May be better to refer to input as either encrypt or decrypt, and fill it with the text to be encryted or decryted.
 ex1.)
    > g++ P9_2/main.cpp -o main
    > ./main -d -k feather decrypt.txt output.txt
    full_text (to be decrypted):
        yhuup qhg gpmutyhuup ojmh ehfjkxrjuzmfc zmhhq eujhgpmut
    encrypted sentence:
        hello pure beautifulgray green blueworld
 ex2.)
    > ./main encrypt.txt output.txt
    full_text (to be encrypted):
        hello pure beautiful
        gray green blue
        world
    encrypted sentence:
        yhuup qhg gpmutyhuup ojmh ehfjkxrjuzmfc zmhhq eujhgpmut
 */

int main(int argc, const char * argv[]) {
    string key1 = "feather";
    string keyND = remove_duplicates(key1);
    vector<char> cipher = get_reverse_alphabet(keyND);
    vector<char> alpha = get_reverse_alphabet("", false);
    vector<char> rev_alpha = get_reverse_alphabet();
    
    cout << "alpha.size(): " << alpha.size() << endl;
    cout << "rev_alpha.size(): " << rev_alpha.size() << endl;
    cout << "cipher.size(): " << cipher.size() << endl;
    for (int i = 0; i < alpha.size(); i++){
        cout << "rev_alpha[" << i << "] = " << rev_alpha[i] << "    alpha[" << i << "] = " << alpha[i] << "    cipher[" << i << "] = " << cipher[i] << endl;
    }
    cout << "\n";
    
    string encrypted = encrypt(keyND, cipher);
    cout << "encrypted = " << encrypted << endl;
    
    string decrypted = decrypt(encrypted, cipher);
    cout << "decrypted = " << decrypted << endl;
    
    string sen = "hello new world";
    string encrypted_sen;
    
    vector<string> words = separate_whitespace(sen);
    for (int i = 0; i < words.size(); i++){
        //cout << "encrypt(" << words[i] << ", cipherKEY): " << encrypt(words[i], cipherKEY) << endl;
        encrypted_sen += encrypt(words[i], cipher);
    }
    cout << "encrypted_sen = " << encrypted_sen << endl;
    
    string decrypted_sen = decrypt(encrypted_sen, cipher);
    cout << "decrypted_sen = " << decrypted_sen << endl;
    
    bool encrypt_mode = true;
    string key2 = "feather";
    string dir = "/Users/christianmeyer/Cpp/ch9/P9_2/";
    string input_file = dir;
    string output_file = dir;

    set_command_line_variables(argc, argv, input_file, output_file, key2, encrypt_mode);
    cout << "\n";
    cout << "key2: " << key2 << endl;
    cout << "input_file: " << input_file << endl;
    cout << "output_file: " << output_file << endl;
    cout << "encrypt_mode " << encrypt_mode << endl;
    cout << "\n";
    
    if (argc > 0) {
        ifstream ifs(input_file, ios::in);
        ofstream ofs(output_file, ios::in | ios::out | ios::trunc);
        string sentence;
        string full_text;
        while (getline(ifs, sentence)){
            full_text += sentence;
            if (ifs.peek() != -1){
                full_text += "\n";
            }
        }
        
        key2 = remove_duplicates(key2);
        cipher = get_reverse_alphabet(key2);
        words = separate_whitespace(full_text);
        
        if (encrypt_mode){
            // ENCRYPT
            cout << "full_text (to be encrypted): \n" << full_text << endl;
            if (words.size() <= 1){
                encrypted_sen = words[0];
            } else {
                for (int i = 0; i < words.size(); i++){
                    encrypted_sen += encrypt(words[i], cipher);
                }
            }
            cout << "encrypted sentence: \n" << encrypted_sen << endl;
            ofs << encrypted_sen;
        } else {
            // DECRYPT
            cout << "full_text (to be decrypted): \n" << full_text << endl;
            if (words.size() <= 1){
                decrypted_sen = words[0];
            } else {
                decrypted_sen = "";
                for (int i = 0; i < words.size(); i++){
                    decrypted_sen += decrypt(words[i], cipher);
                }
            }
            cout << "decrypted sentence: \n" << decrypted_sen << endl;
            ofs << decrypted_sen;
        }
        
        ifs.close();
        ofs.close();
    }
    
    cout << "\n";
    return 0;
    
}

string decrypt(string s, vector<char> key){
    string decrypted;
    vector<char> alpha = get_reverse_alphabet("", false);
    for (int i = 0; i < s.length(); i++){
        for (int j = 0; j < key.size(); j++){
            if (s[i] == ' '){
                decrypted.push_back(' ');
                j = 0;
                break;
            }
            if (s[i] == key[j]){
                decrypted += alpha[j];
            }
        }
    }
    return decrypted;
}
string encrypt(string s, vector<char> key){
    if (s == " "){
        return " ";
    }
    vector<char> alpha = get_reverse_alphabet("", false);
    string encrypted = "";
    vector<int> alpha_indexes;
    for (int i = 0; i < s.length(); i++){
        for (int j = 0; j < alpha.size(); j++){
            if (s[i] == ' '){
                encrypted.push_back(' ');
                j = 0;
                break;
            }
            if (s[i] == alpha[j]){
                encrypted += key[j];
            }
        }
    }
    return encrypted;
}
vector<string> separate_whitespace(string s){
    vector<string> words;
    int start = 0;
    int end = 0;
    for (int i = 0; i < s.length(); i++){
        if (i == s.length()-1){
            words.push_back(s.substr(start, (end-start)));
        }
        if (s[i] == ' ' || s[i] == '\n'){
            end = i;
            words.push_back(s.substr(start, (end-start)));
            start = end+1;
            if (s[i] == ' '){
                words.push_back(" ");
            } else if (s[i] == '\n'){
                words.push_back("\n");
            }
        }
    }
    return words;
}
vector<char> get_reverse_alphabet(string ciph, bool reverse){
    vector<char> alpha;
    //const char a = '\u0061';
    const char a = 'a';
    const char z = a + 25;
    char c;
    int ciph_size = ciph.length();
    if (ciph_size > 0){
        for (int i = 0; i < ciph_size; i++){
            alpha.push_back(ciph[i]);
        }
    }
    if (reverse){
        for (int i = (int(z) - int(a)); i >= 0; i--){
            bool not_in_ciph = true;
            if (ciph_size > 0){
                for (int j = 0; j < ciph_size; j++){
                    if ((int)(a+i) == int(ciph[j])){
                        not_in_ciph = false;
                        goto next_reverse_if;
                    }
                }
            }
        next_reverse_if: {}
            if (not_in_ciph){
                c = a + i;
                alpha.push_back(c);
            }
        }
    } else if (!reverse){
        for (int i = 0; i <= (int(z) - int(a)); i++){
            bool not_in_ciph = true;
            if (ciph_size > 0){
                for (int j = 0; j < ciph_size; j++){
                    if ((int)(a+i) == int(ciph[j])){
                        not_in_ciph = false;
                        goto next_no_reverse_if;
                    }
                }
            }
        next_no_reverse_if: {}
            if (not_in_ciph){
                c = a + i;
                alpha.push_back(c);
            }
        }
    }
    return alpha;
}
string remove_duplicates(string ciph){
    string no_duplicates = "";
    for (int i = 0; i < ciph.length(); i++){
        bool not_a_duplicate = true;
        if (no_duplicates.length() > 0){
            for (int j = 0; j < no_duplicates.length(); j++){
                if (ciph[i] == ' '){
                    goto endj; // not_a_duplicate == true - so ' ' appended to string and j reset to 0.
                }
                if (ciph[i] == no_duplicates[j]){
                    not_a_duplicate = false;
                }
            }
        endj: {}
        }
        if (not_a_duplicate){
            no_duplicates += ciph[i];
        }
    }
    return no_duplicates;
}
void set_command_line_variables(int argc, const char * argv[], string& input_file, string& output_file, string& key, bool& encrypt_mode){
    if (argc > 1){
        if (strcmp(argv[1], "-d") == 0){
            encrypt_mode = false;
        }
        if (argc > 2){
            cout << "one" << endl;
            if (strcmp(argv[2], "-k") == 0){
                cout << "TRUE \"-k\"" << endl;
                if (argc > 3){
                    key = argv[3];
                    //cout << "key: " << key << endl;
                }
                if (argc > 4){
                    input_file += argv[4];
                    if (argc > 5){
                        output_file += argv[5];
                    }
                }
            } else {
                input_file += argv[2];
                if (argc > 3){
                    output_file += argv[3];
                }
            }
        }
    }
    if (input_file[input_file.length()-1] == '/'){
        input_file += "input.txt";
    }
    if (output_file[output_file.length()-1] == '/'){
        output_file += "output.txt";
    }
}
