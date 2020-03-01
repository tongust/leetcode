/*
 * 1)   This algorithm constructs the pointer instead of the element into heap array.
 *      It mimics that it will behave like the element is linked with each other on a heap tree, 
 *      although the truth is that there only exists the heap-array data structure.
 *
 * 2)   Based the condition above, this code can hash the pointer to the element in the heap-array.
 * 
 * */
#include <iostream>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <functional>
#define PARENT(i) (((i+1)/2)-1)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define mswap_ele(l,t,r) {t = (l);l = (r); r = (t);}
using std::pair;
using std::cout;
using std::vector;
using std::endl;
using std::hash;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::ostream;
typedef vector<int> vint;
typedef unsigned long long ull64;
class element
{
public:
    /* default construction */
    /* construction */
    element(const int &i = 0, const int&v = 0, const string&str = string("")):index(i), value(v), key(str){};
    /* copy construction */
    element(const element &ele):index(ele.index),
    value(ele.value),
    key(ele.key){}
    /* assignment */
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
    int index;// means the order in the array. the heap array start at 0.
    int value;// sort by this memeber
    string key;// the identity of element
};
bool operator==(const element &lhs, const element &rhs) { return lhs.value == rhs.value; }
bool operator<(const element &lhs, const element &rhs){return lhs.value < rhs.value;};
bool operator<=(const element &lhs, const element &rhs){return lhs.value <= rhs.value;};
bool operator>=(const element &lhs, const element &rhs){return lhs.value >= rhs.value;};
bool operator>(const element &lhs, const element &rhs){return lhs.value > rhs.value;};
ostream & operator<<(ostream &os,const element &ele) { return os << "[" << ele.index << "," << ele.value << "," << ele.key << "]"; }
int min_heap_decrease_value ( vector<element*> &A, int i, const int &value)/* up the heap */
{
    if (value >= A[i]->value) return i;
    (*A[i]).value = value;
    int pi = PARENT(i);
    element *tmp;
    while (pi > -1 && *A[pi] > *A[i])
    {
        /* exchange A[i] with A[PARENT(i)] */
        mswap_ele(A[i], tmp, A[pi]);
        A[i]->index = i;
        A[pi]->index = pi;
        i = pi;
        pi = PARENT(i);
    }
    return i;
}

int max_heap_increase_value ( vector<element*> &A, int i, const int &value)// up
{
    if (value <= A[i]->value) return i;
    (*A[i]).value = value;
    int pi = PARENT(i);
    element *tmp;
    while (pi > -1 && *A[pi] < *A[i])
    {
        /* exchange A[i] with A[PARENT(i)] */
        mswap_ele(A[i], tmp, A[pi]);
        A[i]->index = i;
        A[pi]->index = pi;
        i = pi;
        pi = PARENT(i);
    }
    return i;
}
int min_heap_decrease_value_by_one (vector<element*> &A, int i)
{ return min_heap_decrease_value(A, i, A[i]->value-1); }
int max_heap_increase_value_by_one (vector<element*> &A, int i)
{ return max_heap_increase_value(A, i, A[i]->value+1); }
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
int max_heap_decrease_value ( vector<element*> &A, int i, const int &value)// down
{
    if (value >= A[i]->value) return i;
    A[i]->value = value;
    int bot = A.size();
    int li = LEFT(i), ri = RIGHT(i);
    element *tmp = nullptr;
    while (li < bot)
    {
        if (ri >= bot)
        {
            if (*A[i] < *A[li])
                {
                    mswap_ele(A[li], tmp, A[i]);
                    A[li]->index = li;
                    A[i]->index = i;
                    i = li;
                }
            break;
        }
        if (*A[li] > *A[ri])
        {
            if (*A[li] > *A[i])
            {
                /* exchange A[left(i)] with A[i] */
                mswap_ele(A[li], tmp, A[i]);
                A[li]->index = li;
                A[i]->index = i;
                i = li;
            }
            else break;
        }
        else
        {
            if (*A[ri] > *A[i])
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
{ return min_heap_increase_value(A, i, A[i]->value+1); }
int max_heap_decrease_value_by_one ( vector<element*> &A, int i)
{ return max_heap_decrease_value(A, i, A[i]->value-1); }
int min_heap_insert(vector<element*> &A, const int& value, string &key)
{
    if (A.empty()){A.push_back(new element(0, value, key)); return 0;}
    A.push_back(new element(A.size(),std::numeric_limits<int>::max(), key));
    return min_heap_decrease_value(A, A.size()-1, value);
}
int max_heap_insert(vector<element*> &A, const int& value, string &key)
{
    if (A.empty()){A.push_back(new element(0, value, key)); return 0;}
    A.push_back(new element(A.size(),std::numeric_limits<int>::min(), key));
    return min_heap_increase_value(A, A.size()-1, value);
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
int max_heapify(vector<element*> &A, const int& index)
{
    if (index >= A.size() || index < 0)return -1;
    int li = LEFT(index),
        ri = RIGHT(index);
    int largest = index;
    element *tmp = nullptr;
    if (li < A.size() && *A[li] > *A[index])
        largest = li;
    if (ri < A.size() && *A[ri] > *A[largest])
        largest = ri;
    if (largest != index)
    {
        mswap_ele(A[index], tmp, A[largest]);
        A[largest]->index = largest;
        A[index]->index = index;
        max_heapify(A, largest);
    }
    return 0;
}
int min_heap_delete(vector<element*> &A, const int& index)
{
    if (index >= A.size() || index < 0)return -1;
    element *tmp;
    tmp = A[index];
    A[index] = *(A.end()-1);
    A[index]->index = index;
    A[A.size()-1] = tmp;
    A.pop_back();
    delete tmp;
    return min_heapify(A, index);
}
int max_heap_delete(vector<element*> &A, const int& index)
{
    if (index >= A.size() || index < 0)return -1;
    element *tmp;
    tmp = A[index];
    A[index] = *(A.end()-1);
    A[index]->index = index;
    A[A.size()-1] = tmp;
    A.pop_back();
    delete tmp;
    return max_heapify(A, index);
}
/*
 * The class AllOne combines the hash table with heap.
 * It hashes the pointer to an element in heap array.
 * */
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        mapele.clear();// map with hash function
        mapele_max.clear();
        coll.clear();
        coll_max.clear();
    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key)
    {
        auto resf = mapele.find(key);
        auto resf_max = mapele_max.find(key);
        int resi = 0;
        int resi1 = 0;
        if (resf != mapele.end())// exist!
        {
            resi = min_heap_increase_value_by_one(coll, resf->second->index);
            resi1 = max_heap_increase_value_by_one(coll_max, resf_max->second->index);
            resf->second = coll[resi];
            resf_max->second = coll_max[resi1];
        }
        else// insert new element
        {
            resi = min_heap_insert(coll, 1, key);
            resi1 = max_heap_insert(coll_max, 1, key);
            mapele[key] = coll[resi];
            mapele_max[key] = coll_max[resi1];
        }
    }
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key)
    {
        auto resf = mapele.find(key);
        auto resf_max = mapele_max.find(key);
        int resi = 0;
        int resi_max = 0;
        if (resf != mapele.end())// exist!
        {
            if (resf->second->value == 1)// delete it!
            {
                min_heap_delete(coll, resf->second->index);
                max_heap_delete(coll_max, resf_max->second->index);
                resf = mapele.erase(resf);
                resf_max = mapele_max.erase(resf_max);
            }
            else
            {
                resi = min_heap_decrease_value_by_one(coll, resf->second->index);
                resi_max = max_heap_decrease_value_by_one(coll_max, resf_max->second->index);
                resf->second = coll[resi];
                resf_max->second = coll_max[resi_max];
            }
        }
        return;
    }
    /** Returns one of the keys with maximal value. */
    string getMaxKey()
    {
        if (!coll_max.empty())return coll_max[0]->key;
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
        for (auto &i : coll_max)
            if (i) delete i;
    }
public:
    unordered_map<string, element*> mapele;// map with hash function
    unordered_map<string, element*> mapele_max;// map with hash function
    vector<element*> coll;
    vector<element*> coll_max;
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
    for (auto &i :ao.coll_max) cout << *i << "+" <<endl;
    cout << ao.getMinKey() << endl;
    cout << ao.getMaxKey() << endl;
    ao.dec(string("leet"));
    cout << ao.getMinKey() << endl;
    cout << ao.getMaxKey() << endl;
    for (auto &i :ao.coll) cout << *i << "-" <<endl;
    for (auto &i :ao.coll_max) cout << *i << "+" <<endl;
    return 0;
    ao.inc(string("c"));
    ao.inc(string("d"));
    ao.inc(string("d"));
    ao.inc(string("a"));
}
