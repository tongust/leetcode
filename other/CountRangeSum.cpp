
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>       /* log2 */
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;
using std::pair;
using std::list;
using std::multiset;
using std::set;

/* Typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;
typedef long long ll64;

class Solution {
public:
    vint _nums;
    int low, up;
    int countRangeSum(vint &nums, int lower, int upper) {
        if (nums.empty()) return 0;
        low = lower;
        up = upper; 
        _nums = nums;
        multiset<ll64> sum_set;
        ll64 sum = 0;
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (isIn(sum)) res++;
            ll64 l = sum - upper, r = sum - lower;
            auto itl = sum_set.lower_bound(l),
                 itr = sum_set.upper_bound(r);
            res += std::distance(itl, itr);
            sum_set.insert(sum);
        }
        return res;
    }
    bool isIn(ll64 n) {
        return n >= low && n <= up; 
    }
};

