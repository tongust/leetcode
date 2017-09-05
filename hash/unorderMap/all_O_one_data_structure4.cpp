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
using std::hash;
using std::unordered_map;
using std::unordered_set;
using std::string;
typedef string SG;
#define PARENT(i) (((i+1)/2)-1)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define ME(l,t,r) {t = (l);l = (r); r = (t);}
#define CT const
#define R5 return  
#define N int
class EL
{ public:
    EL(CT N &i = 0, CT N&v = 0, CT SG&str = SG("")):ID(i), V(v), key(str){}; EL(CT EL &ele):ID(ele.ID), V(ele.V), key(ele.key){} EL & operator=(CT EL &ele) { ID = ele.ID; V = ele.V; key = ele.key; R5 *this; } ~EL() = default;
public:// member
    N ID; N V; SG key;
};
bool operator==(CT EL &lhs, CT EL &rhs) { R5 lhs.ID == rhs.ID; } bool operator<(CT EL &lhs, CT EL &rhs){R5 lhs.V < rhs.V;}; bool operator<=(CT EL &lhs, CT EL &rhs){R5 lhs.V <= rhs.V;}; bool operator>=(CT EL &lhs, CT EL &rhs){R5 lhs.V >= rhs.V;}; bool operator>(CT EL &lhs, CT EL &rhs){R5 lhs.V > rhs.V;}; using std::ostream; ostream & operator<<(ostream &os,CT EL &ele) { os << "[" << ele.ID << "," << ele.V << "," << ele.key << "]"; R5 os; }
N MI1 ( vector<EL*> &A, N i, CT N &V)// up
{ if (V >= A[i]->V) R5 i; (*A[i]).V = V; N pi = PARENT(i); EL *tmp; while (pi > -1 && *A[pi] > *A[i]) {
        ME(A[i], tmp, A[pi]); A[i]->ID = i; A[pi]->ID = pi; i = pi; pi = PARENT(i); } R5 i; }
N max_heap_increase_value ( vector<EL*> &A, N i, CT N &V)// up
{ if (V <= A[i]->V) R5 i; (*A[i]).V = V; N pi = PARENT(i); EL *tmp; while (pi > -1 && *A[pi] < *A[i]) {
        ME(A[i], tmp, A[pi]); A[i]->ID = i; A[pi]->ID = pi; i = pi; pi = PARENT(i); } R5 i; }
N MI1_by_one (vector<EL*> &A, N i) { R5 MI1(A, i, A[i]->V-1); } N max_heap_increase_value_by_one (vector<EL*> &A, N i) { R5 max_heap_increase_value(A, i, A[i]->V+1); } N min_heap_increase_value ( vector<EL*> &A, N i, CT N &V) { if (V <= A[i]->V) R5 i; A[i]->V = V; N bot = A.size(); N li = LEFT(i), ri = RIGHT(i); EL *tmp = nullptr; while (li < bot) { if (ri >= bot) { if (*A[i] > *A[li]) { ME(A[li], tmp, A[i]); A[li]->ID = li; A[i]->ID = i; i = li; } break; } if (*A[li] < *A[ri]) { if (*A[li] < *A[i])
            {
                ME(A[li], tmp, A[i]); A[li]->ID = li; A[i]->ID = i; i = li; } else break; } else { if (*A[ri] < *A[i]) { ME(A[ri], tmp, A[i]); A[ri]->ID = ri; A[i]->ID = i; i = ri; } else break; } li = LEFT(i); ri = RIGHT(i); } R5 i; }

N MXDV ( vector<EL*> &A, N i, CT N &V)// down
{
    if (V >= A[i]->V) R5 i; A[i]->V = V; N bot = A.size(); N li = LEFT(i), ri = RIGHT(i); EL *tmp = nullptr; while (li < bot) { if (ri >= bot)
        { if (*A[i] < *A[li]) { ME(A[li], tmp, A[i]); A[li]->ID = li; A[i]->ID = i; i = li; } break; } if (*A[li] > *A[ri]) {
            if (*A[li] > *A[i])
            {
                ME(A[li], tmp, A[i]); A[li]->ID = li; A[i]->ID = i; i = li; }
            else break; } else { if (*A[ri] > *A[i]) { ME(A[ri], tmp, A[i]); A[ri]->ID = ri; A[i]->ID = i; i = ri; } else break; } li = LEFT(i); ri = RIGHT(i); } R5 i; } N min_heap_increase_value_by_one ( vector<EL*> &A, N i) { R5 min_heap_increase_value(A, i, A[i]->V+1); } N MXDV_by_one ( vector<EL*> &A, N i) { R5 MXDV(A, i, A[i]->V-1); } N min_heap_insert(vector<EL*> &A, CT N& V, SG &key) { if (A.empty()){A.push_back(new EL(0, V, key)); R5 0;} A.push_back(new EL(A.size(),std::numeric_limits<N>::max(), key)); R5 MI1(A, A.size()-1, V); } N max_heap_insert(vector<EL*> &A, CT N& V, SG &key) { if (A.empty()){A.push_back(new EL(0, V, key)); R5 0;} A.push_back(new EL(A.size(),std::numeric_limits<N>::min(), key)); R5 min_heap_increase_value(A, A.size()-1, V);// up
}
N min_heapify(vector<EL*> &A, CT N& ID) { if (ID >= A.size() || ID < 0)R5 -1; N li = LEFT(ID), ri = RIGHT(ID); N smallest = ID; EL *tmp = nullptr; if (li < A.size() && *A[li] < *A[ID]) smallest = li; if (ri < A.size() && *A[ri] < *A[smallest]) smallest = ri; if (smallest != ID) { ME(A[ID], tmp, A[smallest]); A[smallest]->ID = smallest; A[ID]->ID = ID; min_heapify(A, smallest); } R5 0; } N max_heapify(vector<EL*> &A, CT N& ID) { if (ID >= A.size() || ID < 0)R5 -1; N li = LEFT(ID), ri = RIGHT(ID); N largest = ID; EL *tmp = nullptr; if (li < A.size() && *A[li] > *A[ID]) largest = li; if (ri < A.size() && *A[ri] > *A[largest]) largest = ri; if (largest != ID)
    { ME(A[ID], tmp, A[largest]); A[largest]->ID = largest; A[ID]->ID = ID; max_heapify(A, largest); } R5 0; } N min_heap_delete(vector<EL*> &A, CT N& ID)
{ if (ID >= A.size() || ID < 0)R5 -1; EL *tmp; tmp = A[ID]; A[ID] = *(A.end()-1); A[ID]->ID = ID; A[A.size()-1] = tmp; A.pop_back(); delete tmp; R5 min_heapify(A, ID); } N max_heap_delete(vector<EL*> &A, CT N& ID) { if (ID >= A.size() || ID < 0)R5 -1; EL *tmp; tmp = A[ID]; A[ID] = *(A.end()-1); A[ID]->ID = ID; A[A.size()-1] = tmp; A.pop_back(); delete tmp; R5 max_heapify(A, ID); }
class AllOne {
public:
    AllOne() {
        mapele.clear();
        mapele_max.clear();
        coll.clear();
        coll_max.clear();
    }
    void inc(SG key)
    {
        auto resf = mapele.find(key);
        auto resf_max = mapele_max.find(key);
        N resi = 0;
        N resi1 = 0;
        if (resf != mapele.end())
        {
            resi = min_heap_increase_value_by_one(coll, resf->second->ID);
            resi1 = max_heap_increase_value_by_one(coll_max, resf_max->second->ID);
            resf->second = coll[resi];
            resf_max->second = coll_max[resi1];
        }
        else
        {
            resi = min_heap_insert(coll, 1, key);
            resi1 = max_heap_insert(coll_max, 1, key);
            mapele[key] = coll[resi];
            mapele_max[key] = coll_max[resi1];
        }
    }
    void dec(SG key)
    {
        auto resf = mapele.find(key);
        auto resf_max = mapele_max.find(key);
        N resi = 0;
        N resi_max = 0;
        if (resf != mapele.end())// exist!
        {
            if (resf->second->V == 1)// delete it!
            {
                min_heap_delete(coll, resf->second->ID);
                max_heap_delete(coll_max, resf_max->second->ID);
                resf = mapele.erase(resf);
                resf_max = mapele_max.erase(resf_max);
            }
            else
            {
                resi = MI1_by_one(coll, resf->second->ID);
                resi_max = MXDV_by_one(coll_max, resf_max->second->ID);
                resf->second = coll[resi];
                resf_max->second = coll_max[resi_max];
            }
        }
        R5;
    }
    SG getMaxKey()
    {
        if (!coll_max.empty())R5 coll_max[0]->key;
        else R5 SG("");
    }
    
    SG getMinKey()
    {
        if (!coll.empty())R5 coll[0]->key;
        else R5 SG("");
    }
    ~AllOne()
    {
        for (auto &i : coll)
            if (i) delete i;
        for (auto &i : coll_max)
            if (i) delete i;
    }
public:
    unordered_map<SG, EL*> mapele;
    unordered_map<SG, EL*> mapele_max;
    vector<EL*> coll;
    vector<EL*> coll_max;
};
N main()
{
    AllOne ao;
    ao.inc(SG("hello"));
    ao.inc(SG("world"));
    ao.inc(SG("leet"));
    ao.inc(SG("code"));

    ao.inc(SG("DS"));
    ao.inc(SG("leet"));

    ao.inc(SG("DS"));
    for (auto &i :ao.coll) cout << *i << "-" <<endl;
    for (auto &i :ao.coll_max) cout << *i << "+" <<endl;
    cout << ao.getMinKey() << endl;
    cout << ao.getMaxKey() << endl;
    ao.dec(SG("leet"));
    cout << ao.getMinKey() << endl;
    cout << ao.getMaxKey() << endl;
    for (auto &i :ao.coll) cout << *i << "-" <<endl;
    for (auto &i :ao.coll_max) cout << *i << "+" <<endl;
    R5 0;
    ao.inc(SG("c"));
    ao.inc(SG("d"));
    ao.inc(SG("d"));
    ao.inc(SG("a"));
}
