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
using std::string;
#define PARENT(i) (((i+1)/2)-1)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define mswap(l,t,r) {t = (l);l = (r); r = (t);}
void heap_decrease_key_vector// up
(
    vector<int> &A,
    int i,
    const int &key
)
{
    if (key >= A[i]) return;
    A[i] = key;
    int pi = PARENT(i);
    while (pi > -1 && A[pi] > A[i])
    {
        // exchange A[i] with A[PARENT(i)]
        int tmp = A[i];
        A[i] = A[pi];
        A[pi] = tmp;
        i = pi;
        pi = PARENT(i);
    }
    return;
}

int heap_decrease_key_vector_int// up
(
    vector<int> &A,
    int i,
    const int &key
)
{
    if (key >= A[i]) return i;
    A[i] = key;
    int pi = PARENT(i);
    while (pi > -1 && A[pi] > A[i])
    {
        // exchange A[i] with A[PARENT(i)]
        int tmp = A[i];
        A[i] = A[pi];
        A[pi] = tmp;
        i = pi;
        pi = PARENT(i);
    }
    return i;
}
int heap_decrease_key_by_one_vector_int// up
(
    vector<int> &A,
    int i
)
{
    A[i]++;
    int pi = PARENT(i);
    while (pi > -1 && A[pi] > A[i])
    {
        // exchange A[i] with A[PARENT(i)]
        int tmp = A[i];
        A[i] = A[pi];
        A[pi] = tmp;
        i = pi;
        pi = PARENT(i);
    }
    return i;
}
void heap_increase_key_vector// down
(
    vector<int> &A,
    int i,
    const int &key
)
{
    if (key <= A[i]) return;
    A[i] = key;
    int bot = A.size();
    int li = LEFT(i), ri = RIGHT(i);
    int tmp = 0;
    while (li < bot)
    {
        if (ri >= bot)
        {
            if (A[i] > A[li])
                {mswap(A[li], tmp, A[i]);}
            break;
        }
        if (A[li] < A[ri])
        {
            if (A[li] < A[i])
            {
                // exchange A[left(i)] with A[i]
                mswap(A[li], tmp, A[i]);
                i = li;
            }
            else break;
        }
        else
        {
            if (A[ri] < A[i])
            {
                mswap(A[ri], tmp, A[i]);
                i = ri;
            }
            else break;
        }
        li = LEFT(i);
        ri = RIGHT(i);
    }
    return;
}

void heap_inc_by_one_key_vector// down
(
    vector<int> &A,
    int i
)
{
    A[i]++;
    int bot = A.size();
    int li = LEFT(i), ri = RIGHT(i);
    int tmp = 0;
    while (li < bot)
    {
        if (ri >= bot)
        {
            if (A[i] > A[li])
                {mswap(A[li], tmp, A[i]);}
            break;
        }
        if (A[li] < A[ri])
        {
            if (A[li] < A[i])
            {
                // exchange A[left(i)] with A[i]
                mswap(A[li], tmp, A[i]);
                i = li;
            }
            else break;
        }
        else
        {
            if (A[ri] < A[i])
            {
                mswap(A[ri], tmp, A[i]);
                i = ri;
            }
            else break;
        }
        li = LEFT(i);
        ri = RIGHT(i);
    }
    return;
}

int min_heap_insert(vector<int> &A, const int &key)
{
    A.push_back(std::numeric_limits<int>::max());
    return heap_decrease_key_vector_int(A, A.size()-1, key);
}


#if 1 
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        msint.clear();
        coll.clear();
        max_ele = std::make_pair(string(""), 1);
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
       auto resf = msint.find(key);
       if (resf == msint.end())// dont exist, then insert 
       {
           coll.push_back(1);
           int resi = min_heap_insert(coll, 1);
           msint[key] = coll.begin()+resi;
           updateMax(key, 1);
       }
       else // exist key
       {
           int resi = msint[key] - coll.begin();
           updateMax(key, (*msint[key])+1);
           heap_inc_by_one_key_vector(coll, resi);
       }
       return;

    }
    void updateMax(const string &key, const int &value)
    {
        if (max_ele.second < value) 
        {
            max_ele = std::make_pair(key, value);
        }
       return;
    }
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
       auto resf = msint.find(key);
       if (resf != msint.end())// exist 
       {
           int resi = (*resf).second - coll.begin();
           resi = heap_decrease_key_by_one_vector_int(coll, resi);

       }
       return;
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        
    }
public:
    unordered_map<string, vector<int>::iterator> msint;// map with hash function
    pair<string, int> max_ele;
    vector<int> coll;
};
#endif
int main()
{
    unordered_map<string, unsigned int> msint = {
    {"bob", 2}, {"dad", 1}, {"bro", 2}
    };
    vector<int> tvs = {3,4,5,6,8,11,33,9,1,13};
    vector<vector<int>::iterator> tvsit(tvs.size());
    std::make_heap(tvs.begin(), tvs.end(), [](const int &lhs, const int &rhs)->bool{return lhs > rhs;});
    for (int i = 0; i != tvs.size(); ++i)tvsit[i] = tvs.begin()+i;
    //cout << "by:\t" << heap_decrease_key_vector_int(tvs, 8, 7) << endl;
    for (auto &i : tvs) cout << i << ",";cout << endl;
    for (auto &i : tvsit) cout << *i << ","; cout << endl;
    //for (auto &i : msint) cout << i.first << "==" << i.second << endl;
    return 0;
}
