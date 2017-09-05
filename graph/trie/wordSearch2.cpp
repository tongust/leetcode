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

    unordered_multimap<char, pair<int, int>> mmps;
    typedef pair<int,int> pint;
    auto isLeftOK = [](const size_t &L, const size_t &R, char c, vector<vector<char>>& board)->bool{
        if (L+1 >= board.size()) return false;
        else if (c == board[L+1][R]) return true;
        else return false;
    };
    auto isRightOK = [](const size_t &L, const size_t &R, char c, vector<vector<char>>& board)->bool{
        if (R+1 >= board[0].size()) return false;
        else if (c == board[L][R+1]) return true;
        else return false;
    };
    bool isIn(vector<vector<char>>& board, string &word, size_t index, size_t L, size_t R) {
        if (index >= word.size()) return true;
        if (isLeftOK(L, R, word[index], board)) {
            return isIn(board, word, index+1, L+1, R);
        }
        else if (isRightOK(L, R, word[index], board))
            return isIn(board, word, index+1, L, R+1);
        else return false;
    }
    bool isInBoard(vector<vector<char>>& board, string &word) {
        
    string word0(word.rbegin(), word.rend());
    bool res;
    if (mmps.empty()) {

            for (size_t i = 0; i < board.size(); ++i) {

                for (size_t j = 0; j < board[i].size(); ++j) {
                    mmps.insert(pair<char, pint>(board[i][j], pint(i,j)));
                }

        }
    }
    // forward
    char c = word[0];
    auto resfs = mmps.equal_range(c);
    for (auto it = resfs.first; it != resfs.second; it++) {
        res = false;
        res = isIn(board, word, 1, it->second.first, it->second.second);
        if (res) return res;
    }
    // reverse
    c = word0[0];
    resfs = mmps.equal_range(c);
    for (auto it = resfs.first; it != resfs.second; it++) {
        res = false;
        res = isIn(board, word0, 1, it->second.first, it->second.second);
        if (res) return res;
    }
    return false;
    
}

class LRUCache {

public:

    LRUCache(int capacity) {

        cap = capacity;

        nums.resize(cap,pair<int,size_t>(0,0));

        for (auto it = nums.begin(); it != nums.end(); ++it) {

            ptrs.push_back(it);

            mset.insert(it);

        }

        age = 0;

    }

    int get(int key) {

        auto res = get(key, 0, false);

        if (res == nums.end())return -1;

        else return res->first;

    }

    void change_heap(decltype(ptrs)::iterator it, size_t a) {

        (*it)->second = ptrs[0]->second-1;// make sure smaller than the head

        push_heap(ptrs.begin(), it+1, mcmp);

        

        pop_heap(ptrs.begin(), ptrs.end());

        

        ptrs.back()->second = a;

        

        push_heap(ptrs.begin(), ptrs.end());

        return;

    }

    decltype(nums)::iterator get(int key, int value, bool change_fl = true) {

        auto resf = mmap.find(key);

        if (resf != mmap.end()) {

            if (change_fl) 

                (*(resf->second))->first = value;// set new value

            age++;

            change_heap(resf->second, age);

            

            return *(resf->second);

        } else return nums.end();

    }

    void put(int key, int value) {

        if (get(key, value, true) == nums.end()) { // insert

            if (mset.empty()) {

                ptrs.front()->first = value;

                age++;

                change_heap(ptrs.begin(), age);

            } else {

                auto newIt = mset.front();

                mset.erase(mset.begin());

                (*newIt)->first = value;

                mmap[key] = newIt;

                age++;

                change_heap(newIt, age);

            }

        }

        return;

    }

private:

    int cap;

    size_t age;

    vector<pair<int/*value*/, size_t/*age*/>> nums;
    vector<pair<int/*value*/, size_t/*age*/>> 

    /* > means min-heap by age */

    bool mcmp(const decltype(nums)::iterator &lhs, const decltype(nums)::iterator &rhs) {return lhs->second > rhs->second;};

    vector<decltype(nums)::iterator> ptrs; // heap

    unordered_map<int, decltype(ptrs)::iterator> mmap;

    unordered_set<decltype(ptrs)::iterator> mset;

    

};

int 
main()
{
    return 0;
}
