#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
#include <functional>
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
typedef unsigned long long ull64;
using std::hash;
class element
{
public:
    // default construction
    element():key(0),fr(0),time(0), value(0){}
    element(const int &k, const unsigned int &f, const ull64 &t, const int &v):
        key(k), fr(f), time(t), value(v){}
    // copy construction
    element(const element& ele):key(ele.key), fr(ele.fr), time(ele.time), value(ele.value){}
    // assignment construction
    element & operator= (const element &ele)
    {
        key = ele.key;
        fr = ele.fr;
        time = ele.time;
        value = ele.value;
        return *this;
    }

    ~element() = default;
    friend bool operator==(const element &, const element &);
    friend bool operator<(const element &, const element &);
    friend bool operator>(const element &, const element &);
    friend bool operator!=(const element &, const element &);
    /*
    bool operator == (const element & rhs) const
    {
        return key == rhs.key;
    }
    bool operator != (const element &rhs) const
    {
        return !(key == rhs.key);
    }*/
public:
    int key;
    int value;
    unsigned int fr;
    unsigned long long time;
};
bool operator==(const element &lhs, const element &rhs)
{
    return (lhs.key == rhs.key);
}
bool operator<(const element &lhs, const element &rhs)
{
    if (lhs.fr < rhs.fr)
        return true;
    else 
    {
        if (lhs.fr == rhs.fr)
            return lhs.time < rhs.time;
        else
            return false;
    }
}
bool operator>(const element &lhs, const element &rhs)
{
    if (lhs < rhs || lhs == rhs) return false;
    else return true;
    
}
bool operator!=(const element &lhs, const element &rhs)
{
    return !(lhs == rhs);
}
std::ostream& operator << (std::ostream &strm, const element &ele)
{
    return strm << "[k: " << ele.key << ", f: " 
        << ele.fr << ", t: " << ele.time
        << ", v: " << ele.value << "]";
}
using std::unordered_set;
class elementHash
{
public:
    std::size_t operator() (const element &ele) const
    {
        return std::hash<int>()(ele.key);
    }
};
class LFUCache
{
public:
    LFUCache(int capacity)
    {
        max_index = 0;
        if (capacity > 0)
        {
            cap = capacity;
        }
        else cap = 0;
    }
    void put(int key, int value)
    {
        element ele(key, 1/*fr*/, max_index+1, value);
        if (ele_set.find(ele) == ele_set.end()) // if not found key
        {
            auto N = ele_set.size();
            if (N == cap) // delete one then insert
            {
                auto ele_del = *(mes.begin());
                std::pop_heap(mes.begin(), mes.end());
                mes.pop_back();
                ele_set.erase(ele_del);
            }
            ele_set.insert(ele);
            mes.push_back(ele);
            auto f11 = [](const element& lhs, const element &rhs)->bool{if(lhs.fr == rhs.fr) return lhs.time > rhs.time;else return lhs.fr > rhs.fr;};
            std::push_heap(mes.begin(), mes.end(), f11);
            max_index++;
        }
        cout << "put:\t";
        for (auto &i : ele_set)
            cout << i << ", ";
        cout << endl;
        cout << "mes:\t";
        for (auto &i : mes)
            cout << i << ", ";
        cout << endl;
        return;
    }
    int get(int key)
    {
        auto ele_find = ele_set.find(element(key, 0, 0, 0));
        if (ele_find != ele_set.end())
        {
//            ele_find->fr = ele_find->fr + 1;
            element ele(*ele_find);
            ele.fr++;
            ele_find = ele_set.erase(ele_find);
            ele_set.insert(ele);
            auto t111 = std::find(mes.begin(), mes.end(), ele);
            t111->fr++;
//            mes.push_back(ele);
//            std::make_heap(mes.begin(), mes.end());
            std::push_heap(mes.begin(), mes.end());

            cout << "get--:\t";
            for (auto &i : ele_set)
                cout << i << ", ";
            cout << endl;

            return ele.value;
        }
        else
            return -1;
    }
    ~LFUCache() = default;
public:
    unordered_set<element, elementHash> ele_set;
    vector<element> mes;
    int cap;
    ull64 max_index;
};
int main()
{
    vector<element> mss1;
    mss1.push_back(element(0,1,0,0));
    mss1.push_back(element(1,1,1,0));
    mss1.push_back(element(2,1,2,0));
    mss1.push_back(element(3,1,3,0));
    std::make_heap(mss1.begin(), mss1.end(), [](const element& lhs, const element &rhs)->bool{if(lhs.fr == rhs.fr) return lhs.time < rhs.time;else return lhs.fr < rhs.fr;});
    for (auto &i : mss1) cout << i << endl;
    //return 0;
    auto obj = new LFUCache(3);
    obj->put(1,1);
    obj->put(2,2);
//    cout << obj->get(1) << endl;
    obj->put(3,3);
    obj->put(4,4);
    return 0;
    cout << obj->get(3) << endl;
    obj->put(4,4);
    cout << obj->get(1) << endl;
    cout << obj->get(3) << endl;
    cout << obj->get(4) << endl;

    delete obj;
    return 0;
    vector<element> mes;
    // key fr time
    mes.push_back(element(0,1,0, 0));
    mes.push_back(element(1,12,3, 0));
    mes.push_back(element(2,2,2, 0));
    mes.push_back(element(3,2,1, 0));
    std::make_heap(mes.begin(), mes.end());
    mes.pop_back();
    for (auto &i : mes)
    cout << i << endl;
    unordered_set<element, elementHash> mset;
    mset.insert(mes[0]);
    mset.insert(mes[1]);
    mset.insert(mes[2]);
    mset.insert(mes[3]);
    auto it = mset.find(element(300,2000,11111, 0));
    if (it != mset.end())
        cout << *it << endl;
    return 0;
}

