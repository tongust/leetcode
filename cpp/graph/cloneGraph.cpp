
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

struct UndirectedGraphNode {
     int label;
     vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
 };
typedef UndirectedGraphNode undgp;
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node)return node;
        mmap.clear();
        mset.clear();
        innerv.clear();
        innerv.reserve(1000000);
        cloneGraph1(node);
        if(mset.empty()){
            decltype(node) res;
            res = new UndirectedGraphNode(node->label);
            return res;
        }
        unordered_map<undgp*, undgp*> mp1;
        for (auto it : mset) {
            mp1[it] = new undgp(it->label);
        }
        for (auto it : mset) {
            auto dp = mp1[it];
            for (auto it_ : it->neighbors) {
                dp->neighbors.push_back(mp1[it_]);
            }
        }
        return mp1[node];
    }
    void cloneGraph1(UndirectedGraphNode *node) {
        if (!node || node->neighbors.empty())return;
        auto resf = mmap.find(node);
        mset.insert(node);
        for (auto it : node->neighbors) {
            resf = mmap.find(node);
            mset.insert(it);
            if (resf == mmap.end()) {
                unordered_set<undgp*> tmps;
                tmps.insert(it);
                innerv.push_back(tmps);
                mmap.insert(pair<undgp*,miter>(node, innerv.end()-1));
                auto resf2 = mmap.find(it);
                if (resf2 == mmap.end()) {
                    unordered_set<undgp*> tmps2;
                    tmps2.insert(node);
                    innerv.push_back(tmps2);
                    mmap.insert(pair<undgp*,miter>(it, innerv.end()-1));
                } else {
                    resf2->second->insert(node);
                }
                cloneGraph1(it);
            } else {
                auto resf1 = mmap[node]->find(it);
                if (resf1 == mmap[node]->end()) {
                    mmap[node]->insert(it);
                    auto resf2 = mmap.find(it);
                    if (resf2 == mmap.end()) {
                        unordered_set<undgp*> tmps2;
                        tmps2.insert(node);
                        innerv.push_back(tmps2);
                        mmap.insert(pair<undgp*,miter>(it, innerv.end()-1));
                    } else {
                        resf2->second->insert(node);
                    }
                    cloneGraph1(it);
                }
            }
        }// it
    }
    vector<unordered_set<undgp*>> innerv;
    typedef vector<unordered_set<undgp*>>::iterator miter;
    unordered_map<undgp*,decltype(innerv)::iterator> mmap;
    unordered_set<undgp*> mset;
};

int main() {

    Solution s;
    UndirectedGraphNode *d = new UndirectedGraphNode(12);
    auto d1 =  s.cloneGraph(d);


    cout << d1->label << endl;

    delete d1;
    delete d;
    return 0;
}
