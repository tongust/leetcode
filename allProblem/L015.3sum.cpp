#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <iomanip>
#include <utility> 
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include <vector>
#include "t.h"

using namespace std;

typedef unordered_set<int> intset;

typedef pair<int, int> piit;

typedef unordered_multimap<int/*2sum*/, piit> intmap;
typedef unordered_multiset<int> intmset;
class Solution {

public:

    static
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;
        intmset mset;
        for (auto i : nums)mset.insert(i);
        /*special case */
        vector<int> tmp(3,0);
        {
            auto resf = mset.equal_range(0);
            int mc = 0;
            for (auto it = resf.first; it != resf.second; ++it)mc++;
            if (mc>=3)
                res.push_back(tmp);
        }
        /**/
        unordered_set<int> tset0, tset1;
        for (auto i : nums){
            if (i > 0)
                tset1.insert(i);
            else if(i!=0) tset0.insert(i);
        }
        vector<int> minusV(tset0.begin(), tset0.end()),
            plusV(tset1.begin(), tset0.end());
        for (int im = 0; im < minusV.size(); ++im) {
            for (int ip = 0; ip < plusV.size(); ++ip) {
                int t0 = 0 - minusV[im] - plusV[ip];
                auto resf = mset.equal_range(t0);
                tmp[0] = minusV[im];
                tmp[1] = t0;
                tmp[2] = plusV[ip];
                int mc = 0;
                for (auto it = resf.first; it != resf.second; ++it) {
                    mc++;
                }
                if (t0 == minusV[im] || t0 == plusV[ip]) {
                    if (mc >= 2) 
                        res.push_back(tmp);
                } else {
                    if (mc >= 1) 
                        res.push_back(tmp);
                }
            }
        }
        return res;


    }// return

};

int main()
{
    auto res =  Solution::threeSum(A);
    for (auto &i : res) {
        for (auto j : i) {
            cout << j << ",";
        }
        cout << endl;
    }
    return 0;
}
