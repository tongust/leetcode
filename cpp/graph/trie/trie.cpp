#include <string>
#include <iomanip>
#include <utility> 
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>



using namespace std;



template<typename T>
class nodeHash {
public:
    nodeHash():len(0){}
    nodeHash(const T&t): val(t) {}
    T val;
    vector<shared_ptr<nodeHash<T>>> children;
    unordered_map<T, shared_ptr<nodeHash<T>>> mmps;
    size_t len;
};

class trie{
public:
    trie():root(nullptr){}
    shared_ptr<nodeHash<char>> root;
    void add(const string& word) {
        if (!root) root = make_shared<nodeHash<char>>('\0');
        auto it = root;
        for (size_t i = 0; i < word.size(); ++i) {
            auto resf = it->mmps.find(word[i]);
            if (resf != it->mmps.end()) {
                it = resf->second;
            } else {
                shared_ptr<nodeHash<char>> tmpptr = make_shared<nodeHash<char>>(nodeHash<char>(word[i]));
                it->children.push_back(tmpptr);
                pair<char, decltype(tmpptr)> tmppair;
                tmppair.first = word[i];
                tmppair.second = tmpptr;
                it->mmps.insert(tmppair);
                it = tmpptr;
            }
        }
        return;
    }
    bool search(const string &word,size_t index ,decltype(root) it) { /*dsf*/
        if ( ( (it->mmps).empty() && index < word.size())
                /*
                 ||  
                ( (!(it->mmps).empty()) && index >= word.size())
                */
                 )
                 {
            return false;
        }
        if (index >= word.size()) return true;
        if (!it) return false;
        char c = word[index];
        if (c != '.') {
            auto resf = it->mmps.find(c);
            if (resf == it->mmps.end()) {
                return false;
            } else {
                it = resf->second;
                return search(word, index+1, it);
            }
            
        } else {
            for (auto &c1 : it->mmps) {
                if (search(word, index+1, c1.second))
                    return true;
            }
            return false;
        }
    }
};


int 
main() {
    trie mt;
    mt.add(string("bad"));
    mt.add(string("dad"));
    mt.add(string("mad"));


    cout << boolalpha << mt.search(string("pad"), 0, mt.root) << endl;
    cout << boolalpha << mt.search(string("bad"), 0, mt.root) << endl;
    cout << boolalpha << mt.search(string(".ad"), 0, mt.root) << endl;
    cout << boolalpha << mt.search(string("b.."), 0, mt.root) << endl;

    return 0;

}
