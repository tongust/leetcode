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
        typedef vector<vector<unordered_map<int/*value*/, vector<string>>>> dptype;
        typedef unordered_map<int, vector<string>> dpeletype;

        typedef unordered_map<int, bool> dpvisteletype;
        typedef vector<vector<dpvisteletype>> dpvisttype;

        typedef vector<string> vstring;
        static string max_s_str;

        dpeletype recur(dptype &dp, string &num, int beg, int end) {
                if (!dp[beg][end].empty()) {
                        return dp[beg][end];
                }
                if (beg == end) {
                        dpeletype res;
                        string ts(num.begin()+beg, num.begin()+end+1);
                        vstring tsv = {ts};
                        res[std::stoi(ts)] = tsv;
                        dp[beg][end] = res;
                        return res;
                }
                dpeletype res;
                for (int i = beg; i < end; ++i) {
                        string left(num.begin()+beg, num.begin()+i+1),
                               right(num.begin()+i+1, num.end()+end+1);
                        if (left <= max_s_str && right <= max_s_str) {
                                typedef unsigned long long ull;
                                unsigned long long tll;
                                auto l = std::stoull(left),
                                     r = std::stoull(right);
                                tll = l * r;
                                if (tll <= ull(_MAX_S_32)) {
                                        string ss = left + "*" + right;
                                        res[int(tll)].push_back(ss);
                                }
                                tll = l + r;
                                if (tll <= ull(_MAX_S_32)) {
                                        string ss = left + "+" + right;
                                        res[int(tll)].push_back(ss);
                                }
                                string ss = left + "-"+right;
                                res[int(l-r)].push_back(ss);
                        }
                        auto lres = recur(dp, num, beg, i),
                             rres = recur(dp, num, i+1, end);
                        comb(lres, rres, res);
                }
                dp[beg][end] = res;
                return res;
        }
        typedef long long signll;
        void comb(dpeletype &ls, dpeletype &rs, dpeletype &res) {

                static signll (* ops[])(signll, signll) {
                        [](signll l, signll r)->signll{return l + r;},
                        [](signll l, signll r)->signll{return l - r;},
                        [](signll l, signll r)->signll{return l * r;}
                };
                string opstrs[3] = {"+", "-", "*"};
                for (auto &it : ls) {
                        signll lv = it.first;
                        vstring &lvs = it.second;
                        for (auto &it1 : rs) {
                                signll rv = it1.first;
                                vstring &rvs = it1.second;
                                signll t0; 
                                for (int ii = 0; ii < 3; ++ii) {
                                        t0 = ops[ii](lv, rv);
                                        if (t0 <= _MAX_S_32 && t0 >= _MIN_S_32) {
                                                for (auto &it_i : lvs) {
                                                        for (auto &it_j : rvs)
                                                        {
                                                                res[t0].push_back(it_i+opstrs[ii]+it_j);
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        vector<string> recur(dptype & dp, int target, string &num)
        {
                vstring res;
                // all to one number
                if (num <= max_s_str) {
                        if (std::stoi(num) == target)
                                res.push_back(num);
                }
                int beg = 0,
                    end = num.size()-1;
                for (int i = beg; i < end; ++i) {
                        auto lres = recur(dp, num, beg, i),
                             rres = recur(dp, num, i+1, end);
                        /*
                        if (i == 1) {
                        cout << "loop " << i << endl;
                        for (auto it : lres) {
                                cout << "v: " << it.first << " -------\n";
                                PRINT1D(it.second, " ");
                        }
                        for (auto it : rres) {
                                cout << "v: " << it.first << " -------\n";
                                PRINT1D(it.second, " ");
                        }
                        }
                        */
                        comb(lres, rres, res, target);
                }
                return res;
        }
        void comb(dpeletype &ls, dpeletype &rs, vstring &res, int target) {
                static signll (* ops[])(signll, signll) {
                        [](signll l, signll r)->signll{return l + r;},
                        [](signll l, signll r)->signll{return l - r;},
                        [](signll l, signll r)->signll{return l * r;}
                };
                static string opstrs[3] = {"+", "-", "*"};
                for (auto &itl : ls) {
                        signll lv = itl.first;
                        auto &lvs = itl.second;
                        for (auto &itr : rs) {
                                signll rv = itr.first;
                                auto &rvs = itr.second;
                                for (int i = 0; i < 3; ++i) {
                                        auto lr = ops[i](lv,rv);
                                        if (lr == target) {
                                                for (auto &iti : lvs) {
                                                        for (auto &itj : rvs) {
                                                                res.push_back(iti + opstrs[i] + itj);
                                                        }
                                                }
                                        }
                                }
                        }
                }
                return;
        }
	vector<string> addOperators(string num, int target) {
                vstring res;
                int n = num.size();
                vector<vector<unordered_map<int/*value*/, vector<string>>>> dp(n,
                                vector<unordered_map<int, vector<string>>>(n));
                res = recur(dp, target, num);
                auto aa = dp[0][1],
                     bb = dp[2][3];
                
                for (auto it : aa) {
                        cout << "v: " << it.first << " -------\n";
                        PRINT1D(it.second, " ");
                }
                for (auto it : bb) {
                        cout << "v: " << it.first << " -------\n";
                        PRINT1D(it.second, " ");
                }
                return res;
	}
        void tst() {
                string num = "123456";
                auto res = addOperators(num, 6);
                PRINT1D(res, " ");
        }
};
string Solution::max_s_str = std::to_string(_MAX_S_32);
int main()
{
        
        Solution so;
        so.tst();
        return 0;
}

