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
	void setZeroes(vector<vector<int>>& matrix) {
                unordered_set<int> rset,cset;
                for (int i = 0; i < matrix.size(); ++i) {
                        auto &rows = matrix[i];
                        for (int j = 0; j < rows.size(); ++j) {
                                if (!rows[j]) {
                                        rset.insert(i);
                                        cset.insert(j);
                                }
                        }
                }
                for (auto &it : rset) {
                        for (auto &m : matrix[it])
                                m = 0;
                }
                for (auto &it : cset) {
                        for (int k = 0; k < matrix.size(); ++k) {
                                matrix[k][it] = 0;
                        }
                }
                return;
	}
};
int main()
{
        Solution so;
        vvint mat = {{0,1,1,1}, {1,0,0,1}, {1,1,1,1}};
        PRINT2D(mat, " ");
        so.setZeroes(mat);
        PRINT2D(mat, " ");
        return 0;
}

