#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
typedef unsigned long long ull64;
using std::hash;
using std::list;
using std::unordered_set;
#if 1  
class element
{
public:
    // default construction
    element():key(0),fr(nullptr),time(nullptr), value(nullptr), left(nullptr), right(nullptr){}
    element(const int &k, const unsigned int &f = 0, const ull64 &t = 0, const int &v = 0):
        key(k){
            value = new int(v);
            fr = new unsigned int(f);
            time = new ull64(t);
            left = new const element*(nullptr);
            right = new const element*(nullptr);
        }
    // copy construction
    element(const element& ele):key(ele.key)
    {
        
        value = new int(ele.value?(*ele.value):0);
        fr = new unsigned int(ele.fr?(*ele.fr):0);
        time = new ull64(ele.time?(*ele.time):0);
        left = new const element*(nullptr);
        if (ele.left)
            *left = *ele.left;
        right = new const element*(nullptr);
        if (ele.right)
            *right = *ele.right;
    }
    // assignment 
    element & operator= (const element &ele)
    {
        key = ele.key;
        if (fr!=ele.fr)
        {
            unsigned int tmp =  0;
            if (ele.fr)
                tmp = *ele.fr;
            if (fr)
                *fr = tmp;
            else fr = new unsigned int(tmp);
        }
        if (time!=ele.time)
        {
            ull64 tmp = 0;
            if (ele.time)tmp = *ele.time;
            if (time)
            {
                *time = tmp;
            }
            else time = new ull64(tmp);
        }
        if (value!=ele.value)
        {
            int tmp = 0;
            if (ele.value)
                tmp = *ele.value;
            if (value) 
            {
                *value = tmp;
            }
            else value = new int(tmp);
        }
        if (left != ele.left)
        {
            const element *tmp = nullptr;
            if (ele.left)
                tmp = *ele.left;
            if (left)
            {
                *left = tmp;
            }
            else
            {
                left = new const element*(tmp);
            }
        }
        if (right != ele.right)
        {
            const element *tmp = nullptr;
            if (ele.right)
                tmp = *ele.right;
            if (right)
            {
                *right = tmp;
            }
            else
            {
                right = new const  element*(tmp);
            }
        }
        return *this;
    }

    ~element()
    {
        if (fr) delete fr;
        if (value) delete value;
        if (time) delete time;
        if (left) delete left;
        if (right) delete right;
    };
    friend bool operator==(const element &, const element &);
    friend bool operator<(const element &, const element &);
    friend bool operator>(const element &, const element &);
    friend bool operator!=(const element &, const element &);
public:
    int key;
    // first order pointer
    int *value;
    unsigned int *fr;
    unsigned long long *time;
    // second order pointer
    element const ** left;
    element const ** right;
};
bool operator==(const element &lhs, const element &rhs)
{
    return (lhs.key == rhs.key);
}
bool operator<(const element &lhs, const element &rhs)// less pro..
{
    if (*lhs.fr < *rhs.fr)
        return true;
    else
    {
        if (*lhs.fr == *rhs.fr)
            return *lhs.time < *rhs.time;
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
    strm << "[k: " << ele.key << ", v: "
        << *ele.value << ", f: " << *ele.fr << ", t: "
        << *ele.time << ", L.k: ";
    if (ele.left)
    {
        if (*ele.left)
        {
            strm << ((**ele.left).key) << ", R.k: ";
        }
        else
        {
            strm << "null, R.k: ";
        }
    }
    else
    {
        strm << "null, R.k: ";
    }
    if (ele.right)
    {
        if (*ele.right)
        {
            strm << ((**ele.right).key) << "]";
        }
        else
        {
            strm << "null]";
        }
    }
    else
    {
        strm << "null]";
    }
    return strm;
}
#endif
class elementHash
{
public:
    std::size_t operator() (const element &ele) const
    {
        return std::hash<int>()(ele.key);
    }
};
class LFUCache {
public:
    // data zone
    unordered_set<element, elementHash> ele_set;
    const element *head;
    const element *tail;
    int cap;
    ull64 max_index;
    LFUCache(int capacity)
    {
        max_index = 0;
        tail = head = nullptr;
        if (capacity > 0)
            cap = capacity;
        else
            cap = capacity;
    }
public:

    int get(int key) {
		    auto it_find = ele_set.find(element(key));
			if (it_find != ele_set.end())// exist
			{
				(*(it_find->fr))++;
				*(it_find->time) = ++max_index;
				auto res = *(it_find->value);
				if (ele_set.size() == 1)
					return res;
				// update the links 
				const element* p_find = &*it_find;
				const element* it_ele = *(p_find->right);
				while (it_ele != nullptr)
				{
					if (*(p_find) < *(it_ele))
					{
						break;
					}
					it_ele = *(it_ele->right);
				}
				if (it_ele == *(p_find->right))
					return res;
				if (it_ele != nullptr)// insert into the medle.
				{	
					if(it_ele != *(p_find->right))
					{
						if (head!=p_find)
							*((*(p_find->left))->right) = *(p_find->right);
						else
							{head = *(p_find->right);/////
							*(head->left) = nullptr;}
						*((*(p_find->right))->left) = *(p_find->left);
					// insert before the it_ele;
						*((*(it_ele->left))->right) = p_find;
						*(p_find->left) = *(it_ele->left);
						*(p_find->right) = it_ele;
						*(it_ele->left) = p_find;
						
					}
				}
				else
				{
					// delete p_find
					if (head!=p_find)
						*((*(p_find->left))->right) = *(p_find->right);
					else
						{head = *(p_find->right);/////
						*(head->left) = nullptr;
						}
					*((*(p_find->right))->left) = *(p_find->left);
					*(tail->right) = p_find;
					*(p_find->left) = tail;
					*(p_find->right) = nullptr;
					tail = p_find;
				}
				return res;
			}
			else
			{
				return -1;
			}
    }

    void put(int key, int v1) {
        // put function
        if (cap == 0)return;
        auto N = ele_set.size();
		if (N == 0)
		{
			max_index++; 
			element ele(key,1,max_index,v1);
			auto set_it = ele_set.insert(ele).first;
			*set_it->left = nullptr;
			*set_it->right = nullptr;
			head = &(*set_it);
			tail = head;
		}
		else
		{
		    auto it_find = ele_set.find(element(key));
			if (it_find != ele_set.end())// exist
			{
				*(it_find->value) = v1;
				get(key);
				return;
			}
			if (N == cap)// full
			{
				if (cap == 1)
				{
				    ele_set.erase(*head);
					const element*  set_it = &*(ele_set.insert(element(key, 1, ++max_index, v1)).first);
					*set_it->left = nullptr;
					*set_it->right = nullptr;
					head = &(*set_it);
					tail = head;
					return;////////////////////////////////////////
				}
				// delete the head
				auto tmp = head;
				head = *(head->right);
				*(head->left) = nullptr;
				ele_set.erase(*tmp);
			}   
			const element*  set_it = &*(ele_set.insert(element(key, 1, ++max_index, v1)).first);
		    // update the head and tail	
			auto it_ele = tail;// const element
			while(true)// delete the head pointer because the priority of head is less than tail.
			{
				if ((*it_ele) < (*set_it))
				{
					*(set_it->right) = *(it_ele->right);//(it_ele->right)?(*(it_ele->right)):nullptr;
					*(set_it->left) = it_ele;
					if (*(it_ele->right))
					{
						*((*(it_ele->right))->left) = set_it;
					}
					else
					{	
						tail = set_it;// update the tail.
					}
					*(it_ele->right) = set_it;
					break;
				}
				if (*(it_ele->left) == nullptr)
				{
					*(set_it->right) = it_ele;
					*(it_ele->left) = set_it;
					*(set_it->left) = nullptr;
					head = set_it;// update the head.
					break;
				}
				it_ele = *(it_ele->left);
			}
		}
		///////////////////////////////////////////////////////////
		return;
    }

};
int main1()
{
    // k f t v
    LFUCache lf(2);
    lf.put(2,1);
    lf.put(3,2);
	cout << lf.get(3) << endl;
	cout << lf.get(2) << endl;
    lf.put(4,3);
	cout << lf.get(2) << endl;
	cout << lf.get(3) << endl;
	cout << lf.get(4) << endl;
    for (auto &i :lf.ele_set)cout << i << endl;
    /*
    unordered_set<element, elementHash> ele_set;
    ele_set.insert(element(1,1,1,1));
    ele_set.insert(element(2,1,2,1));
    ele_set.insert(element(3,1,3,1));
    ele_set.insert(element(4,1,4,1));
    for (auto &i : ele_set)cout << i << endl;
    */
    return 0;
    int  const *  * ipp = nullptr;
    const int *ip = nullptr;
    const int i = 12;
    ip = &i;
    ipp = &ip;
    cout << **ipp << endl;
    const int j = 13;
    const int *jp = &j;
    ipp = &jp;
    cout << **ipp << endl;

    const int i1 = 1;
    const int *p1 = &i1;
    int i2 = 3;
    int i3 = 4;
    int *const p2 = &i2;// read-only

    {
        int u1 =1,u2=2,u3=3;
        int const *p3 = nullptr;// read-only
        // const int * p = 0; // read-only;
        p3 = &u1;
        p3 = &u2;
        cout << *p3 << endl;
    }
    
    //*ipp = ip;
    //LFUCache lf(3);
    //lf.put(1,2);
    //lf.put(2,2);
    return 0;
}
