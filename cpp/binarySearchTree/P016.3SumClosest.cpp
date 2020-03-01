#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>       /* log2 */
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define SKELETON

#ifdef SKELETON 
#define _MIN_S_32 0x80000001
#define _MIN_U_32 0x00000000
#define _MAX_S_32 0x7fffffff
#define _MAX_U_32 0xffffffff
#endif

#ifndef MMIN
#define MMIN(x,y) ((x) > (y) ? (y) : (x))
#endif
#ifndef MMAX
#define MMAX(x,y) ((x) < (y) ? (y) : (x))
#endif

#ifndef PRINT1D
#define PRINT1D(v,d) do {for (auto it_print : v) cout << it_print << d; cout << endl;}while(0)
#endif

#ifdef PRINT1D
#ifndef PRINT2D
#define PRINT2D(v,d)                          \
do {                                          \
    cout << endl;                             \
    for (auto &it_print2d : v) {              \
        for (auto &it_print1d : it_print2d) { \
            cout << it_print1d << d;          \
            } cout << endl;                   \
    }                                         \
} while(0)
#endif
#endif

#ifndef MDebugLog
#define MDebugLog(msg)  std::cout << __FILE__ << ":" << __LINE__ << ": " << msg
#endif

/* using */

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::getline;
using std::list;
using std::multiset;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/* typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;

/* example */
/*
 * vector<int> mvec;
 * mvec.begin(); mvec.end(); pair<int, int>; first; second;
 * iterator
 * while(getline(stringstream, string, char))
 */

class Solution {
public:
        void delOne(multiset<int> &mset, int val)
        {
                auto it = mset.find(val);
                if (it != mset.end()) {
                        it = mset.erase(it);
                }
        }
        int closest(multiset<int> &mset, int val) {
                auto lo = mset.lower_bound(val), up = mset.upper_bound(val);
                int clst = _MAX_S_32;
                int res = 0;
                if (lo != mset.end()) { clst = std::abs(*lo - val); res = *lo; }
                if (up != mset.begin()) { 
                        up--;
                        int tmp = std::abs(*up - val);
                        if (tmp < clst)
                        {
                                clst = tmp;
                                res = *up;
                        }
                }
                return res;
        }
        int threeSumClosest(vector<int>& nums, int target) {
                multiset<int> mset;
                if (nums.size() <= 2) return 0;
                int ori_t = target;
                if (target < 0) {
                        for (auto &num : nums)
                                num = -num;
                        target = -target;
                }
                int res = nums[0] + nums[1] + nums[2];
                int clst = std::abs(res - target);
                int n = nums.size();
                for (int i = 0; i < n; ++i)
                {
                        int a = nums[i];
                        if (i < 3) {
                                mset.insert(a);
                                continue;
                        }
                        for (int j = 0; j < i; ++j)
                        {
                                int b = nums[j];
                                delOne(mset, b);
                                int c = std::abs(target - a - b);
                                int d = closest(mset, c);
                                int tmp = std::abs(a + b + d - target);
                                if (tmp < clst){
                                        res = a + b + d;
                                        clst = tmp;
                                }
                                mset.insert(b);
                        }
                        mset.insert(a);
                        if (clst == 0) break;
                }
                return ori_t < 0 ? -res : res;
        }
};
int main()
{
        int m;
        cin >> m;
        vector<int> ms = {1,1,-1,-1,3};
        Solution so;
        cout << so.threeSumClosest(ms, m) << endl;
        return 0;
}

