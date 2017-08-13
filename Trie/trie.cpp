#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include <math.h>       /* log2 */

#ifndef PRINT1D
#define PRINT1D(v,d) do {for (auto it_print : v) cout << it_print << d; cout << endl;}while(0)
#endif

#ifdef PRINT1D
#ifndef PRINT2D
#define PRINT2D(v,d)                          \
do {                                          \
    cout << endl;                             \
    for (auto &it_print2d : v) {              \
        for (auto &it_print1d : it_print2d) { \
            cout << it_print1d << d;          \
            } cout << endl;                   \
    }                                         \
} while(0)
#endif
#endif

#ifndef MDebugLog
#define MDebugLog(msg)  std::cout << __FILE__ << ":" << __LINE__ << ": " << msg
#endif

/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

#define WIDTH_TRIE 26
#define MIN_BASE 'a'
#define MAX_BASE 'z'
#define ITER_CHILDREN_TRIE for(int i_trie = 0; i_trie < WIDTH_TRIE; ++i_trie) 

struct nodeTrie {
    nodeTrie(char d = 'a') : c(d) { 
        pos = 0;
        isLeaf = false;
        for (int i = 0; i != WIDTH_TRIE; ++i) {
            children[i] = nullptr;
        }
    }
    char c;
    nodeTrie* children[WIDTH_TRIE];
    int pos;
    bool isLeaf;
};
/* Only a-z */
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new nodeTrie('\0'); // nill
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        nodeTrie* n = root;
        int idx = 0;
        for (int i = 0; i < word.size(); ++i) {
            char c = word[i];
            idx = c - MIN_BASE;
            if (n->children[idx] == nullptr) {
                n->children[idx] = new nodeTrie(c);
            }
            if (i + 1 == word.size()) {
                n->children[idx]->isLeaf = true;
            }
            n = n->children[idx];
        }
        return;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto n = root;
        if (word.empty()) return false;
        for (int i  = 0; i < word.size(); ++i) {
            char c = word[i];
            int idx = c - MIN_BASE;
            if (n->children[idx] == nullptr) 
                return false;
            if (i + 1 == word.size()) {
                if (n->children[idx]->isLeaf)
                    return true;
                else return false;
            }
            n = n->children[idx];
        }
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if(prefix.empty())return false;
        auto n = root;
        for (auto c : prefix) {
            int idx = c - MIN_BASE;
            if (n->children[idx] == nullptr) 
                return false;
            n = n->children[idx];
        }
        return true;
    }
    ~Trie() {
        dispose(root);
    }
    void dispose(nodeTrie* leaf) {
        if (leaf == nullptr) return;
        auto child = &leaf->children[0];
        ITER_CHILDREN_TRIE {
            if (*child != nullptr)dispose(*child);
            child++;
        }
        delete leaf;
        return;
    }
private:
    const char maxBase = 'z';
    const char minBase = 'a';
    nodeTrie* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */



int main() {

    Trie trie;

    trie.insert(string("hello"));
    trie.insert(string("hela"));
    trie.insert(string("helal"));
    trie.insert(string("world"));
    cout << "hello" << (trie.search(string("hello"))) << endl;
    cout << "hel" << (trie.search(string("hel"))) << endl;
    cout << "hela" << (trie.search(string("hela"))) << endl;
    cout << "world" << (trie.search(string("world"))) << endl;
    return 0;
}
