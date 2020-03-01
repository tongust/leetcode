/*
 * Implement wildcard pattern matching with support for "?" and "*"
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
using std::unordered_set;
using std::string;
using std::cout;
using std::vector;
using std::endl;
typedef vector<unsigned short> vint;
bool isMatch(string s, string p) 
{
    unordered_set<int> mst, mst1;
    int Ns = s.size(),
        Np = p.size();
    mst.insert(0);
    int t1 = 0;
    for (int i = 0; i<Np; ++i)
    {
        mst1.clear();
        if (p[i] != '*')
        {
            for (auto it : mst)
            {
                t1 = it + 1;
                if (t1 <= Ns)
                {
                    if (s[t1-1] == p[i] || p[i] == '?')
                        mst1.insert(t1);
                }
            }
        }
        else/* * */
        {
            auto it_min = std::min_element(mst.begin(), mst.end());
            for (int k = *it_min; k <= Ns; k++)
                mst1.insert(k);
        }
        mst = mst1;
        if (mst.empty()) return false;
    }
    /* verification */
    char lastp = p[Np-1];
    if (lastp == '*')
    {
        if (mst.empty())return false;
        else return true;
    }
    else
    {
        auto resf = mst.find(Ns);
        if (resf != mst.end())
        {
            if (lastp == '?' || lastp == s[Ns-1])
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }

}
int main()
{
    string s = "abcd",
           p = "*ab?";
    cout << isMatch(s,p) << endl;;
    return 0;
}
