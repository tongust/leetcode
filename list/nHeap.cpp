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
typedef pair<int/*key*/, pair<int/*value*/, int/*fr*/> > PIIT;

typedef list<PIIT> LPIIT;

typedef list<LPIIT> LPLIST;

class LFUCache {

public:

    LFUCache(int capacity) : _capacity(capacity), len(0){

        

    }

    

    int get(int key, int value = -1) {
        if(_capacity == 0)return -1;
        auto resf = mpKeyIt.find(key);
        if (resf != mpKeyIt.end()) {
			if (value != -1) resf->second->second.first = value;
            auto res =  resf->second->second.first;
            update(resf->second);
            return res;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        {// if exist
            if(_capacity == 0)return;
			auto r1 = get(key, value);
            if(r1 != -1) {
				cout << r1 << endl;
                return;
			}
        }
        // non-exist
        if (len >= _capacity) {
            // delete
            auto itL0 = mlis.begin();
            auto itL1 = itL0->end();
            itL1--;
            auto keyOld = itL1->first;
            auto frOld = itL1->second.second;
            mpKeyIt.erase(keyOld);
            itL1 = itL0->erase(itL1);
            if (itL0->empty()) {
                itL0 = mlis.erase(itL0);
                mpFrIt.erase(frOld);
            } 
            
        } else {
            len++;
        }
        auto refs = mpFrIt.find(1);
        PIIT piit(key, pair<int, int>(value, 1));
        if (refs != mpFrIt.end()) {
            mpFrIt[1]->push_front(piit);
        } else {
            LPIIT lpiit;
            lpiit.push_front(piit);
            mlis.push_front(lpiit);
            mpFrIt[1] = mlis.begin();
        }
        mpKeyIt[key] = mpFrIt[1]->begin();
    }

private:
    int _capacity;
    int len;
    LPLIST mlis;
    unordered_map<int/*fr*/, LPLIST::iterator> mpFrIt;
    unordered_map<int/*key*/, LPIIT::iterator> mpKeyIt;
    void update(LPIIT::iterator it) {
        // delete old
        auto fr = it->second.second;
        auto val = it->second.first;
        auto key = it->first;
        auto newFr = fr+1;
        PIIT piit(key, pair<int,int>(val, newFr));
        it = mpFrIt[fr]->erase(it);

        auto resf = mpFrIt.find(newFr); 
        if (resf != mpFrIt.end()) {
            resf->second->push_front(piit);
            mpKeyIt[key] = resf->second->begin();
        } else {
            auto itp = mpFrIt[fr];
            itp++;
            LPIIT lpiit;
            lpiit.push_front(piit);
            itp = mlis.insert(itp, lpiit);
            mpFrIt[newFr] = itp;
            mpKeyIt[key] = itp->begin();
        }
        // delete fr
        if (mpFrIt[fr]->empty()) {
            mpFrIt[fr] = mlis.erase(mpFrIt[fr]); // delete mlis
            mpFrIt.erase(fr); // delete mpFrIt
        } 
    }

};
int main()
{
    LFUCache obj(2);
    obj.put(1,1);
    obj.put(2,2);
    obj.put(2,3);
    cout << obj.get(2) << endl;
    obj.put(3,3);
    cout << obj.get(2) << endl;
    cout << obj.get(3) << endl;
    obj.put(4,4);
    cout << obj.get(3) << endl;
    //cout << obj.get(1) << endl;
    //cout << obj.get(3) << endl;
    //cout << obj.get(4) << endl;
	return 0;
}
