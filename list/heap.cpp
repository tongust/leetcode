#include <list>
#include <string>
#include <iterator>
#include <iomanip>
#include <utility> 
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef vector<pair<pair<int/*key*/, int/*value*/>, size_t/*age*/>> numsT;

typedef vector<numsT::iterator> ptrsT;

typedef list<pair<int, int>> LINT;
typedef unordered_map<int/*key*/, LINT::iterator> MAP;
class LRUCache {

public:


    LRUCache(int capacity): _capacity(capacity),len(0) {
    }
    int get(int key) {
        auto resf = mmap.find(key);
        if (resf != mmap.end()) {
            int res =  (*(resf->second)).second;
            update(resf->second);
            return res;
        } else return -1;
    }
    void put(int key, int value) {
        auto resf = mmap.find(key);
        if (resf != mmap.end()) {
            resf->second->second = value;
            update(resf->second);
        } else {
            if (len >= _capacity) {
                auto it = mlis.end();
                it--;
                mmap.erase(it->first);
                it = mlis.erase(it);
            } else {
                len++;
            }
            pair<int, int> ele(key, value);
            mlis.push_front(ele);
            mmap[key] = mlis.begin();
        }
    }

private:

    int _capacity, len;
    LINT mlis;
    MAP mmap;
    LINT::iterator update(LINT::iterator it){
        decltype(*it) ele = *it;
        it = mlis.erase(it);
        mlis.push_front(ele);
        mmap[ele.first] = mlis.begin();
        return it;
    }


    

};
int main() 
{
    LRUCache obj(3);
    obj.put(1,1);
    obj.put(2,2);
    obj.put(3,3);
    obj.put(4,4);
    cout << obj.get(2) << endl;
	return 0;
}
