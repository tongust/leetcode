#include <iostream>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
//#include <pair>
#include <functional>
using std::cout;
using std::vector;
using std::endl;
using std::hash;
using std::list;
using std::pair;
using std::unordered_set;
using std::unordered_map;
class LRUCache
{	
public:
	LRUCache(int c): cap(c){};
	int get(int key)
	{
		if (cap == 0)return -1;
		auto tmp_it = map_int_pair.find(key);
		if (tmp_it == map_int_pair.end())
		{
			return -1;
		}
		else
		{
			auto it_lis = tmp_it->second;
			int res = it_lis->first;
			auto it_lis_new = ls.insert(ls.begin(), *it_lis);
			it_lis = ls.erase(it_lis);
			tmp_it->second = it_lis_new;
			//map_int_pair[key] = it_lis_new;
			return res;
		}
	}
	void put(int k, int v)
	{
		if (cap == 0)return;
		auto N = map_int_pair.size();
		auto tmp_it = map_int_pair.find(k);
		if (tmp_it != map_int_pair.end())//find it
		{
			auto it_lis = tmp_it->second;
			it_lis->first = v;
			auto it_lis_new = ls.insert(ls.begin(), *it_lis);
			it_lis = ls.erase(it_lis);
			tmp_it->second = it_lis_new;
		}
		else
		{
			if (N == cap)// delete
			{
				auto del_key = ls.back().second;
				auto del_map_it = map_int_pair.find(del_key);
				del_map_it = map_int_pair.erase(del_map_it);
				ls.pop_back();//delete the last;
				ls.push_front(pair<int, int>(v,k));
				map_int_pair[k] = ls.begin();
			}
			else
			{
				ls.push_front(pair<int, int>(v,k));
			    map_int_pair[k] = ls.begin();
			}
		}

	}

public:
	int cap;
	unordered_map<int, list<pair<int/*value*/, int/*key*/> >::iterator> map_int_pair;
	list<pair<int, int>> ls;
};

int main1()
{
	LRUCache lru(2);
	lru.put(1,1);
	cout << lru.get(1) << endl;
	lru.put(2,2);
	cout << lru.get(2) << endl;
	lru.put(3,3);
	cout << lru.get(1) << endl;
	cout << lru.get(2) << endl;
	cout << lru.get(3) << endl;
	lru.put(3,4);
	lru.put(1,1);
	cout << lru.get(3) << endl;
	return 0;
}

