#include <algorithm>
#include <cmath>
#include <deque>
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

#ifndef SKELETON 
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
using std::list;
using std::multiset;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/* typedef */

//typedef int pair4[4];
typedef vector<int> pair4;
typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;

/* example */
/*
 * vector<int> mvec;
 * mvec.begin(); mvec.end(); pair<int, int>; first; second;
 * iterator
 */

int max4(const pair4& p)
{
        int res = _MIN_S_32;
        for (int i = 0; i < 4; ++i)
        {
                if (res < p[i])
                        res = p[i];
        }
        return res;
}
void rec(vector<vector<pair4>> &dp, int i, int j, vvint &mat)
{
        auto &it = dp[i][j];
        auto m = mat[i][j];
        int n = mat.size(), M = mat[0].size();
        for (int k = 0; k < 4; ++k) {
                if (it[k] != -1)
                        continue;
                switch (k) {
                        case 0:/*i-1, j*/
                                if (i == 0 || mat[i-1][j] <= mat[i][j]) {
                                        it[k] = 1;
                                } else {
                                        rec(dp, i-1, j, mat);

                                        it[k] = 1 + max4(dp[i-1][j]);
                                }
                                break;
                        case 1:/*i+1, j*/
                                if (i == n-1 || mat[i+1][j] <= mat[i][j]) {
                                        it[k] = 1;
                                } else {
                                        rec(dp, i+1, j, mat);

                                        it[k] = 1 + max4(dp[i+1][j]);
                                }
                                break;
                        case 2:/*i, j-1*/
                                if (j == 0 || mat[i][j-1] <= mat[i][j]) {
                                        it[k] = 1;
                                } else {
                                        rec(dp, i, j-1, mat);

                                        it[k] = 1 + max4(dp[i][j-1]);
                                }
                                break;
                        case 3:/*i, j+1*/
                                if (j == M-1 || mat[i][j+1] <= mat[i][j]) {
                                        it[k] = 1;
                                } else {
                                        rec(dp, i, j+1, mat);

                                        it[k] = 1 + max4(dp[i][j+1]);
                                }
                                break;
                        default:
                                break;

                }
        }
        return;
}
int foo(vvint & mat)
{
        if (mat.empty()) return 0;
        int n = mat.size(), M = mat[0].size();
        vector<vector<pair4>> dp(n);
        for (auto &it : dp) {
                pair4 tmp(4, -1);
                it.resize(M, tmp);
        }
        int res = _MIN_S_32;

#if 1
        for (auto &it_i : dp)
                for (auto &it_j : it_i)
                        for (auto &it_k : it_j)
                                it_k = -1;
        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < M; ++j) {
                        rec(dp,i,j,mat);
                        auto tmp = max4(dp[i][j]);
                        if (tmp > res)
                                res = tmp;
                }
        }
#endif
        return res;
}

int main()
{
        vvint mat = {
                {3,4,5},
                {3,2,6}
        };
        cout << foo(mat) << endl;
        return 0;
}

