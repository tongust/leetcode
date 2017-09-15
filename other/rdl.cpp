#include <algorithm>
#include <cmath>
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

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::multiset;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/* Typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;

typedef pair<char, bool> pcbool;
typedef list<pcbool> lpcbool;
typedef unordered_map<char, set<int>> mapcvint;

#define BASECHAR 'a'
class Solution {
public:
	string removeDuplicateLetters(string s) {
		char dict[256];
                for (auto &c : dict)
                        c = 0;
                for (auto c : s) {
                        dict[c]++;
                }
                unordered_map<char, set<int>> mmp;
                unordered_map<char, int> lastidx;
                for (int i = 0; i < s.size(); ++i) {
                        char c = s[i];
                        auto resf = lastidx.find(c);
                        if (resf != lastidx.end()) {
                                resf->second = i;
                        } else {
                                lastidx.insert(pair<char, int>(c, i));
                        }
                }
                int idx = 0;
                for (auto c : s) {
                        if (dict[c] > 1)// dup
                        {
                                mmp[c].insert(idx++);
                        }
                }
                lpcbool res;
                for (int i = 0; i < s.size(); ++i) {
                        char c = s[i];
                        if (dict[c] == 1) {
                                res.push_back(pcbool(c, 0));
                                clear_list(res, c, mmp);
                                continue;
                        } else {
                                auto resf = mmp.find(c);
                                if (resf != mmp.end())
                                {
                                        auto &mset = mmp[c];
                                        bool isf = true;
                                        for (auto r : res) {
                                                if (r.first == c) {
                                                        isf = false;
                                                        break;
                                                }
                                        }
                                        if (isf) // first push
                                        {
                                                res.push_back(pcbool(c, true));
                                        }
                                        else { // dup
                                                if (lastidx[c] == i) {
                                                        res.push_back(pcbool(c, 0));
                                                        clear_list(res, c, mmp);
                                                }
                                                
                                        }
                                }
                        }
                }
                string res_str;
                for (auto it : res) {
                        res_str.push_back(it.first);
                }
                return res_str;
	}
        void clear_list(lpcbool &res, char c, mapcvint &mmp)
        {
                int lmd = res.size() - 1;
                vector<int> delidx;
                auto it = res.begin();
                auto it_end = res.end();
                while(it != it_end) {
                        if (it->second) {
                                if (it->first >= c)// dup then erase
                                {
                                        it = res.erase(it);// it will point to next iterator
                                        continue;// 
                                }
                                else // dup keep
                                {
                                        it->second = 0;
                                        mmp.erase(it->first);
                                }
                        }
                        it++;
                }
        }
};

int main() {
        Solution so;
        string s = "32320110";
        cout << so.removeDuplicateLetters(s) << endl;
        return 0;
}
