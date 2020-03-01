#include <iostream>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <functional>
using std::pair;
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
typedef unsigned long long ull64;
using std::hash;
using std::unordered_map;
using std::unordered_set;
using std::string;
#define PARENT(i) (((i+1)/2)-1)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define mswap_ele(l,t,r) {t = (l);l = (r); r = (t);}
class element
{
public:
    // default construction
    // construction
    element(const int &i = 0, const int&v = 0, const string&str = string("")):index(i), value(v), key(str){};
    // copy construction
    element(const element &ele):index(ele.index),
    value(ele.value),
    key(ele.key){}
    // assignment 
    element & operator=(const element &ele)
    {
        index = ele.index;
        value = ele.value;
        key = ele.key;
        return *this;
    }
    // deconstruction
    ~element() = default;
public:// member
    int index;
    int value;
    string key;
};
bool operator==(const element &lhs, const element &rhs) { return lhs.index == rhs.index; }
bool operator<(const element &lhs, const element &rhs){return lhs.value < rhs.value;};
bool operator<=(const element &lhs, const element &rhs){return lhs.value <= rhs.value;};
bool operator>=(const element &lhs, const element &rhs){return lhs.value >= rhs.value;};
bool operator>(const element &lhs, const element &rhs){return lhs.value > rhs.value;};
using std::ostream;
ostream & operator<<(ostream &os,const element &ele)
{
    os << "[" << ele.index << "," << ele.value << ","
        << ele.key << "]";
    return os;
}
int min_heap_decrease_value ( vector<element*> &A, int i, const int &value)
{
    if (value >= *A[i]) return i;
    (*A[i]).value = value;
    int pi = PARENT(i);
    element *tmp;
    while (pi > -1 && *A[pi] > *A[i])
    {
        // exchange A[i] with A[PARENT(i)]
        mswap_ele(A[i], tmp, A[pi]);
        A[i]->index = i;
        A[pi]->index = pi;
        i = pi;
        pi = PARENT(i);
    }
    return i;
}
int min_heap_decrease_value_by_one (vector<element*> &A, int i)
{
    return min_heap_decrease_value(A, i, A[i]->value-1);
}

int min_heap_increase_value ( vector<element*> &A, int i, const int &value)
{
    if (value <= A[i]->value) return i;
    A[i]->value = value;
    int bot = A.size();
    int li = LEFT(i), ri = RIGHT(i);
    element *tmp = nullptr;
    while (li < bot)
    {
        if (ri >= bot)
        {
            if (*A[i] > *A[li])
                {
                    mswap_ele(A[li], tmp, A[i]);
                    A[li]->index = li;
                    A[i]->index = i;
                    i = li;
                }
            break;
        }
        if (*A[li] < *A[ri])
        {
            if (*A[li] < *A[i])
            {
                // exchange A[left(i)] with A[i]
                mswap_ele(A[li], tmp, A[i]);
                A[li]->index = li;
                A[i]->index = i;
                i = li;
            }
            else break;
        }
        else
        {
            if (*A[ri] < *A[i])
            {
                mswap_ele(A[ri], tmp, A[i]);
                A[ri]->index = ri;
                A[i]->index = i;
                i = ri;
            }
            else break;
        }
        li = LEFT(i);
        ri = RIGHT(i);
    }
    return i;
}

int min_heap_increase_value_by_one ( vector<element*> &A, int i)
{
    return min_heap_increase_value(A, i, A[i]->value+1);
}
int min_heap_insert(vector<element*> &A, const int& value, string &key)
{
    if (A.empty()){A.push_back(new element(0, value, key)); return 0;}
    A.push_back(new element(A.size(),std::numeric_limits<int>::max(), key));
    return min_heap_decrease_value(A, A.size()-1, value);
}
int min_heapify(vector<element*> &A, const int& index)
{
    if (index >= A.size() || index < 0)return -1;
    int li = LEFT(index),
        ri = RIGHT(index);
    int smallest = index;
    element *tmp = nullptr;
    if (li < A.size() && *A[li] < *A[index])
        smallest = li;
    if (ri < A.size() && *A[ri] < *A[smallest])
        smallest = ri;
    if (smallest != index)
    {
        mswap_ele(A[index], tmp, A[smallest]);
        A[smallest]->index = smallest;
        A[index]->index = index;
        min_heapify(A, smallest);
    }
    return 0;
}
int min_heap_delete(vector<element*> &A, const int& index)
{
    // exchange
    if (index >= A.size() || index < 0)return -1;
    element *tmp;
    tmp = A[index];
    A[index] = *(A.end()-1);
    A[index]->index = index;
    A[A.size()-1] = tmp;
    //
    A.pop_back();
    delete tmp;
    return min_heapify(A, index);
}
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        mapele.clear();// map with hash function
        coll.clear();
        //max_ele = nullptr;
        max_eles.clear();
    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key)
    {
        auto resf = mapele.find(key);
        int resi = 0;
        if (resf != mapele.end())// exist!
        {
            resi = min_heap_increase_value_by_one(coll, resf->second->index);
            resf->second = coll[resi];
            updateMax(resf->second);
        }
        else// insert new element
        {
            resi = min_heap_insert(coll, 1, key);
            mapele[key] = coll[resi];
            updateMax(coll[resi]);
        }
    }
    void updateMax(element *ele)
    {
        if (max_eles.empty()) {max_eles.insert(ele);return;}
        if ((**max_eles.begin()).value == (*ele).value) 
        {
            max_eles.insert(ele);
        }
        else
        {
            if (**(max_eles.begin()) < *ele)
            {
                max_eles.clear();
                max_eles.insert(ele);
            }
        }
        return;
    }
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key)
    {
        auto resf = mapele.find(key);
        int resi = 0;
        if (resf != mapele.end())// exist!
        {
            if (resf->second->value == 1)// delete it!
            {
                {// 
                    auto t1 = max_eles.find(resf->second);
                    if (t1 != max_eles.end())// find it
                    {
                        max_eles.erase(t1);
                    }
                }
                min_heap_delete(coll, resf->second->index);
                resf = mapele.erase(resf);
            }
            else
            {
                {
                    auto t1 = max_eles.find(resf->second);
                    if (t1 != max_eles.end())// find it
                        //max_ele = coll[resi];
                    {
                    //    cout << **t1 << ",  " << max_eles.size() << endl;
                        max_eles.erase(t1);
                    }
                }
                resi = min_heap_decrease_value_by_one(coll, resf->second->index);
                resf->second = coll[resi];
                if (max_eles.empty())
                    max_eles.insert(coll[resi]);
            }
        }
        return;
    }
    /** Returns one of the keys with maximal value. */
    string getMaxKey()
    {
        if (!coll.empty() && !max_eles.empty())return (*max_eles.begin())->key;
        else return string("");
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey()
    {
        if (!coll.empty())return coll[0]->key;
        else return string("");
    }
    ~AllOne()
    {
        for (auto &i : coll)
            if (i) delete i;
    }
public:
    unordered_map<string, element*> mapele;// map with hash function
    unordered_set<element *> max_eles;
    vector<element*> coll;
};
int main()
{
    AllOne ao;
    ao.inc(string("hello"));
    ao.inc(string("world"));
    ao.inc(string("leet"));
    ao.inc(string("code"));

    ao.inc(string("DS"));
    ao.inc(string("leet"));

    ao.inc(string("DS"));
    for (auto &i :ao.coll) cout << *i << "-" <<endl;
    cout << ao.getMaxKey() << endl;
    ao.dec(string("leet"));


    cout << ao.getMaxKey() << endl;
    for (auto &i :ao.coll) cout << *i << endl;
    return 0;
    ao.inc(string("c"));
    ao.inc(string("d"));
    ao.inc(string("d"));
    ao.inc(string("a"));
}
