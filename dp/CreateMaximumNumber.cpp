#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <math.h>       /* log2 */

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

/* Typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    int M = nums1.size(), 
        N = nums2.size();
    vector<vvint>(M, vvint(N, vint(k, -2)));
    }
    int recur_helper(vvvint &dp, int k, int x, int y, const int &K, vint &numsx, vint &numsy) { 
        int len_x = numsx.size(),
            len_y = numsy.size();
        if (k >= K || x >=  len_x || y >= len_y)
            return 0;
        if (len_x + len_y  - x - y < K - k) {
            dp[k][x][y] = -2; /* impossible */
            return -2;
        }
        int tmp = dp[k][x][y];
        if (tmp > -2) return tmp;
        int factor = 1;
        for (int i = 0; i < K - k - 1; ++i) {
            factor *= 10;
        }
        int res = -2;
        // select x
        for (int i = x; i < len_x; ++i) {
            int tmp1 = factor * numsx[i];
            int tmp2 = recur_helper(dp, k+1, i, y, K, numsx, numsy);
            if (tmp2 < 0) tmp2 = 0;
            int tmp3 = tmp1 + tmp2;
            if (res < tmp3) {
                res = tmp3;
            }
        }
        // select y
        for (int i = y; i < len_y; ++i) {
            int tmp1 = factor * numsy[i];
            int tmp2 = recur_helper(dp, k+1, x, i, K, numsx, numsy);
            if (tmp2 < 0) tmp2 = 0;
            int tmp3 = tmp1 + tmp2;
            if (res < tmp3) {
                res = tmp3;
            }
        }
        dp[k, x, y] = res;
        return res;
    }

};
int main() {
    
}

