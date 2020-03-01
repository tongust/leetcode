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
#define _MIN_S_32 0x8fffffff
#define _MIN_U_32 0x80000000
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
        int recur(string &s, vvint &dp, string &t, int i, int j) {
                int m = s.size(),
                    n = t.size();
                if (i < m && j < n &&dp[i][j] != -1)return dp[i][j];
                char c0 = s[i],
                     c1 = t[j];
                int count = 0;
                if (c0 == c1) {
                        if (j == n-1) {
                                count++;
                                if (i != m-1)
                                        count += recur(s, dp, t, i+1, j);
                        } else {
                                if (i != m-1)
                                {
                                        count += recur(s, dp, t, i+1, j+1);
                                        count += recur(s, dp, t, i+1, j);
                                }
                        }
                }
                else {
                        if (i != m-1) {
                                count += recur(s, dp, t, i+1, j);
                        }
                }
                dp[i][j] = count;
                return count;
        }
	int numDistinct(string s, string t) {
                if (s.empty() && !t.empty()) return 0;
                if (s.empty() && t.empty()) return 1;
                if (!s.empty() && t.empty()) {
                        return 1;
                }
                vvint dp(s.size(), vint(t.size(), -1));
                auto res = recur(s, dp, t, 0, 0);
                return res;
	}
};

int main()
{
        Solution so;
        string s = "rabbbit",
               t = "rabbit";
        cin >> s >> t;
        cout << so.numDistinct(s, t) << endl;
        return 0;
}
