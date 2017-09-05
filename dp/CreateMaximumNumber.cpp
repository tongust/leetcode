#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <math.h>       /* log2 */
#include <cmath>

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
typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
struct ele {
    bool isX;
    bool isOk;
    bool touched;
    int next;
    ele& operator=(const ele &e) {
        isX = e.isX; isOk = e.isOk; next = e.next;
        touched = e.touched;
        return *this;
    }
    ele(const ele& e): isX(e.isX), isOk(e.isOk), next(e.next), touched(e.touched){}
    ele(bool i1, bool i2, bool i3, int n): isX(i1), isOk(i2), touched(i3), next(n){ }
};
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vint res;
        int M = nums1.size(), 
            N = nums2.size();
        if (M+N<k)return res;
        if (M+N==1) {
            return nums1.empty() ? nums2 : nums1;
        }
        vector<vector<ele>> dp(k+1, vector<ele>(M+1, vint(N+1, ele(false,false,false,0))));


        //recur_helper(dp, 0, 0, 0, k, nums1, nums2); 
        int initx = 0, inity = 0;
        return res;
    }
    // 0: impossible, + :x, - :y
    // uninitialized -len_x - len_y
    bool MaxThan( 
    vvvint &dp, 
    int k, 
    int x0, int y0, 
    int x1, int y1, 
    const int &K, 
    vint &numsx, vint &numsy,
    bool currIsX0,
    bool currIsX1
    ) {
        int len_x = numsx.size(),
            len_y = numsy.size();
        for (int i = k; i < K; i++){ 
            vint *vp0 = &numsx,
                 *vp1 = &numsx;
            int t0 = dp[i][x0][y0],
                t1 = dp[i][x1][y1];
            if (t0 < 0) vp0 = &numsy;
            if (t1 < 0) vp1 = &numsy;
            int abst0 = std::abs(t0) - 1,
                abst1 = std::abs(t1) - 1;

            if (i == k) {
                int tmp0, tmp1;
                if (currIsX0) {
                    tmp0 = numsx[x0-1];
                } else {
                    tmp0 = numsy[y0-1];
                }
                if (currIsX1) { 
                    tmp1 = numsx[x1-1];
                } else {
                    tmp1 = numsy[y1-1];
                }
                if (tmp0 != tmp1)
                    return tmp0 > tmp1;
                else 
                    continue;
            }
            if ((*vp0)[abst0] != (*vp1)[abst1]) {
                return (*vp0)[abst0] > (*vp1)[abst1];
            } else {
                if (t0 < 0)  {
                    y0 = abst0;
                } else {
                    x0 = abst0;
                }
                if (t1 < 0)  {
                    y1 = abst1;
                } else {
                    x1 = abst1;
                }
            }
        }
        return true;
    }

    int recur_helper(vvvint &dp, int k, int x, int y, const int &K, vint &numsx, vint &numsy) { 
        int len_x = numsx.size(),
            len_y = numsy.size();
        if (k >= K && x <= len_x && y <= len_y) 
        {
            dp[k][x][y] = 1;
            return 1; // must be 1 or -1 
        }
        if (x >  len_x || y > len_y)
            return 0;
        if (len_x + len_y - x - y < K - k) {
            dp[k][x][y] = 0; /* impossible */
            return 0;
        }
        int tmp = dp[k][x][y];
        if (tmp != -len_x - len_y) return tmp;
        vvint nexv;
        vector<bool> nexBool;
        // select x
        for (int i = x+1; i <= len_x; ++i) {
            int r1 = recur_helper(dp, k+1, i, y, K, numsx, numsy);
            if (r1 != 0) {
                nexv.push_back(vint({i, y}));
                nexBool.push_back(true);

        cout << i << " " << y << endl;
            }
        }
        // select y
        for (int i = y+1; i <= len_y; ++i) {
            int r1 = recur_helper(dp, k+1, x, i, K, numsx, numsy);
            if (r1 != 0) {
                nexv.push_back(vint({x, i}));
                nexBool.push_back(false);
        cout << x << " " << i << endl;
            }
        }
        if (nexv.empty()) {
            dp[k][x][y] = 0;
            return 0;
        }
        int initx = nexv[0][0],
            inity = nexv[0][1];
        bool initBool = nexBool[0]; 
        int mc = 0;
        for (auto i : nexv) {

            if (mc++ == 0) continue;
            bool isX1 = nexBool[mc];
            cout << k << " " <<  initx << " " << inity << " " << i[0] << " " << i[1] << " " << K << endl;
            if (!MaxThan(
                dp, k, initx, inity, i[0], i[1], K, numsx, numsy, initBool, isX1
            )) {
                initx = i[0];
                inity = i[1];
                initBool = isX1;
            }
        }
        if (initx > x) {
            dp[k][x][y] = initx;
        } else {
            dp[k][x][y] = -inity;
        }
        return dp[k][x][y];
    }

};
int main() {
   vint numx = {3,4,6,5}; 
   vint numy = {0,1,2,5,8,3};
   PRINT1D(numx, " ");
   PRINT1D(numy, " ");
   Solution so;
   auto res = so.maxNumber(numx, numy, 2);
   PRINT1D(res, ",");
   return 0;
}

