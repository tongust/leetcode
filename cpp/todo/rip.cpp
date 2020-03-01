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

typedef vector<string> vstring;
static const int UNTOUCHED = _MIN_S_32;
class Solution {
public:
        bool isLP(char c) { return c == '('; }
        bool isRP(char c) { return c == ')'; }
        bool isP(char c) { return isLP(c) || isRP(c);}
        bool isTouched(int i) { return i != UNTOUCHED; }
        bool isPair(char l, char r) {return isLP(l) && isRP(r);}
        string clean(string &s)
        {
                int n = s.size();
                string ts0, ts1, ts2;
                int t0 = n, t1 = -1;
                for (int i = 0; i < n; ++i) {
                        if (isLP(s[i])) {
                                t0 = i;
                                break;
                        }
                        if (!isRP(s[i]))
                                ts0.push_back(s[i]);
                }
                for (int i = n-1; i > -1; --i) {
                        if (isRP(s[i])) {
                                t1 = i;
                                break;
                        }
                        if (!isLP(s[i]))
                                ts2.push_back(s[i]);
                }
                if (t0 < n && t1 > -1 &&t1+1-t0 > 0) ts1 = s.substr(t0, t1+1-t0);
                ts2 = string(ts2.rbegin(), ts2.rend());
                return ts0 + ts1 + ts2;
        }
        int recur(vvint &dp, string &s, int i0, int j0)
        {
                if (i0 > j0) return 0;
                if (i0 == j0) {
                        char c = s[i0];
                        if (isP(c)) { dp[i0][j0] = isLP(c) ? 1 : -1; }
                        else dp[i0][j0] = 0;
                }
                if (isTouched(dp[i0][j0])) return dp[i0][j0];
                int min_cost = _MAX_S_32;
                char l = s[i0], r = s[j0];
                min_cost = recur(dp, s, i0+1, j0-1) 
                               + int( isPair(l,r) ? 0 : int(isP(l)) + int (isP(r))
                );
                for (int i = i0; i < j0; ++i) {
                        int t0 = recur(dp, s, i0, i);
                        t0 += recur(dp, s, i+1, j0);
                        if (min_cost > t0)
                                min_cost = t0;
                }
                dp[i0][j0] = min_cost;
                return min_cost;
        }
        vector<string> removeInvalidParentheses(string s)
        {
                vstring res;
                s = clean(s);
                if (s.empty()) {
                        res.push_back(s);
                        return res;
                }
                int n = s.size();
                vvint dp(n, vint(n, UNTOUCHED));
                for (int i = 0; i < n; ++i)
                        for (int j = i; j < n; ++j)
                                dp[i][j] = dp[j][i] = recur(dp, s, i, j);
                PRINT2D(dp, " ");
                return res;
        }
};
int main()
{
        Solution so;
        string s;
        while (cin >> s) {
                auto it = so.clean(s);
                cout << it << endl;
                auto res = so.removeInvalidParentheses(s);
        }
        return 0;
}

