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

typedef vector<long long> vint;
typedef vector<vector<long long>> vvint;
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
        typedef list<long long> lint;
        long long erase_help(lint &ls, decltype(ls.begin()) &it) {
                long long res = -1;
                if (it != ls.end()) {
                        res = *it;
                        it  = ls.erase(it);
                }
                return res;
        }
        long long erase_help(lint &ls, long long idx)
        {
                long long res = -1;
                if (ls.size() > idx) {
                        auto it = std::next(ls.begin(), idx);
                        res = *it;
                        it = ls.erase(it);
                }
                return res;
        }
        long long cal_help(long long n)
        {
                return (n*n + n)/2;
        }
        int minPatches(vector<int>& nums, int n)
        {
                lint ls(nums.begin(), nums.end());
                long long max0 = 0;
                auto it = ls.begin();
                for (long long i = 1; i <= n;) {
                        if (it == ls.end()) {
                                it = ls.insert(it, i);
                        }
                        long long num = *it;
                        long long left = num,
                            right = num+max0;
                        if (i < num) {
                                it = ls.insert(it, max0+1);
                                continue;
                        } else {
                                i = right + 1;
                                if (i > n)
                                        break;
                                max0 = right;
                                it++;
                        }
                }
                for (auto it : ls) {
                        if (std::find(nums.begin(), nums.end(), it) == nums.end()) {
                                cout << "(" << it << ")" << " ";
                        }
                        else cout << it << " ";
                } cout << endl;
                return ls.size() - nums.size();
        }
};

int main()
{
        while (1) {
                int n = 0, m;
                cin >> n >> m;
                vector<int> aa(n);
                for (auto &it : aa)
                        cin >> it;
                Solution so;
                so.minPatches(aa, m);
        }
        return 0;
}

