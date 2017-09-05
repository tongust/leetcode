/*
 * Deep search first
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <map>
using std::cout;
using std::map;
using std::set;
using std::vector;
using std::endl;
using std::string;
typedef vector<int> vint;
typedef vector<string> vstr;
inline 
bool binaryS(const vector<string> &vs, string s,
        vector<set<string>> &vss,
        map<int/*length*/, int/*index*/> &mymap,
        vector<int> &size_v,
        const size_t& len_s)
{
    string ss1;
    auto N_s = s.size();
    for (const int &i : size_v)
    {
        //cout << "i\t" << i << " " << N_s << endl;
        if (i > N_s)
            break;
        ss1.resize(i);
        std::copy(s.begin(), s.begin()+i, ss1.begin());
        //cout << "ss1\t" << ss1 << "\t\t\t" << s << endl;
        set<string> &it = vss[mymap[i]];
        if (it.find(ss1) != it.end() )
        {
            if (N_s == i && N_s < len_s) return true;
            ss1.resize(N_s-i);
            std::copy(s.begin()+i, s.end(), ss1.begin());
            if (binaryS(vs, ss1, vss, mymap, size_v, len_s))
                return true;
        }

    }
    return false;
}

vector<string> find(vector<string> &vs)
{
    std::sort(vs.begin(), vs.end(), [](const string & s1, const string &s2)->bool{return s1.size() > s2.size();});
    map<int, int> mymap;
    int mc = 0;
    for (auto &s : vs)
    {
        auto it1 = mymap.find(s.size());
        if (it1 == mymap.end())
            mymap[s.size()] = mc++;
    }
    vector<set<string>> vss(mymap.size());
    vector<int> size_v(mymap.size());
    mc = 0;
    for (auto &it : mymap)
    {
        it.second = mc;
        size_v[mc] = it.first;
//        cout << it.first << "," << it.second<< endl;
        mc++;
        
    }
    //vector<vector<string>> nes_vs(mymap.size());
    for (auto &s : vs)
        vss[mymap[s.size()]].insert(s);
    for (auto &i : vss)
    {
        for (auto &j : i)
            cout << j << ",";
        cout << endl;
    }

    vector<string> res;
    string ss1 = "dog";
    cout << "bin\t" <<binaryS(vs, ss1, vss, mymap, size_v, ss1.size()) << endl;
//    return res;




    for (auto &i : vs)
    {
        if (binaryS(vs, i, vss, mymap, size_v,i.size()))
            res.push_back(i);
    }
    return res;
}

int main()
{
    vector<string> vs(8);// = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    vs[0] = "cat";
    vs[1] = "cats";
    vs[2] = "catsdogcats";
    vs[3] = "dog";
    vs[4] = "dogcatsdog";
    vs[5] = "hippopotamuses";
    vs[6] = "rat";
    vs[7] = "ratcatdogcat";
    auto res = find(vs);
    for(auto & i: res)cout << i << "..." << endl;
    return 0;
}

