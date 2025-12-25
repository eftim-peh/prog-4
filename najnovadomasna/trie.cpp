

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct Trie {
    Trie* children[26] = {NULL};
    bool is_end_word = false;
    string label=""; 
};

void add_to_trie(Trie* root, const string& str) {
    Trie* curr = root;
    for (char ch : str) { //izmini gi site charovi vo stringot
        char c = tolower(ch); //napravi gi so mali bukvi
        if (c < 'a' || c > 'z') continue; //izbegni gi ne-malite bukvi (special characters)
       
        int ind = c - 'a'; //napravi ja sekoja bukva vo odreden indeks (a-0, b-1, c-2, ..., z-25)

        if (!curr->children[ind])
            curr->children[ind] = new Trie(); //napravi dete ako nema za taa bukva

        curr = curr->children[ind]; //odi na novoto dete
    }
    curr->is_end_word = true; 
}

void convert_patricia(Trie* node) {
    if (!node) return;

    for (int i=0; i<26; i++) {
        if (node->children[i])
            convert_patricia(node->children[i]); //post-order i so ova rekurzivno ke gi kompresirame site deca prvo
    }

    int brojac = 0, ind = -1; //ova e vsusnost  kolku deca ima nekoj clen i index na nekoe negobo dete
    for (int i=0; i<26; i++) {
        if (node->children[i]) {
            brojac++;
            ind = i;
        }
    }
    if (brojac != 1) return; //ako clenot nema tocno edno dete togas nemoze da se kompresira
    Trie* child = node->children[ind];
   
    node->label.push_back('a' + ind);
    node->label += child->label; //spoj gi podatocite od deteto na roditelot created by andst
    for (int i=0; i<26; i++)
        node->children[i] = child->children[i]; //decata na deteto se sega deca na roditelot
    node->is_end_word = child->is_end_word; //sega ima nov kraj
    delete child; //ubi go staroto dete, sega ima novo dete
}

void print_trie(Trie* node, string &current) { //rekurzivna postapka za da gi isprinta site zborovi vo Trieto
    if (!node) return;

    if (node->is_end_word) //ako stignavme do krajot pecati go zborot
        cout << current << "\n";

    for (int i=0; i<26; i++) {
        if (node->children[i]) { //ako postoi dete
            current.push_back('a' + i); //stavi ja momentalnata bukva vo current created by andrej st
            print_trie(node->children[i], current); //sega rekurzivno povikaj se za noviot current
            current.pop_back(); //backtracking za tocno da gradime novi zborovi
        }
    }
}

void print_patricia(Trie* node, string &current) { //print funkcija za patricia
    if (!node) return;
    current += node->label; //dodai go label-ot vo current
    if (node->is_end_word) 
        cout << current << "\n"; //stignavme do kraj, pecati

    for (int i=0; i<26; i++) {
        if (node->children[i])
            print_patricia(node->children[i], current); //istata rekurzija kako kaj obicniot print
    }
    current.erase(current.size() - node->label.size()); 
}

bool search_trie(Trie* root, const string& str) { 
    Trie* curr = root;
    for (char ch : str) { 
        char c = tolower(ch); 
        if (c < 'a' || c > 'z') return false;

        int ind = c - 'a'; 
        if (!curr->children[ind]) 
            return false; 
        curr = curr->children[ind]; 
    }
    return curr->is_end_word; 
}

bool search_patricia(Trie* node, const string& word, int pos = 0) {
    if (!node) return false;

    int len = node->label.size();

    
    if (word.size()-pos < len) return false;

    for (int i=0; i<len; i++) {
        if (tolower(word[pos + i]) != node->label[i]) 
            return false;
    }
    
    pos += len;
    if (pos == word.size())
        return node->is_end_word;

    
    char next_char = tolower(word[pos]);
    if (next_char < 'a' || next_char > 'z') return false;

    int ind = next_char - 'a';
    return search_patricia(node->children[ind], word, pos);
}

int main() {
    Trie* root = new Trie();
    
    string path = "./wiki-100k.txt";
    ifstream txt(path);

    vector<string> words;
    string line;

    while (getline(txt, line)) {
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;

        words.push_back(line);
    }
    for (int i=0; i<words.size(); i++) {
        add_to_trie(root, words[i]);
    }
    string temp;
    print_trie(root, temp);

    convert_patricia(root);
    print_patricia(root, temp);

    return 0;
}