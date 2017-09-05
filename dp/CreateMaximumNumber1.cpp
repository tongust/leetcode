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

struct ele{
    bool is_x;
    bool is_touched;
    bool is_ok;
    int next;
    ele(bool x, bool t, bool o, int n):
        is_x(x),
        is_touched(t),
        is_ok(o),
        next(n) { }
    ele(const ele &e): is_x(e.is_x), is_touched(e.is_touched), is_ok(e.is_ok) {}
    ele& operator=(const ele &e) {
        is_x = e.is_x; is_touched = e.is_touched;
        is_ok = e.is_ok;
        next = e.next;
        return *this;
    }
};
typedef vector<ele> vele;
typedef vector<vele> vvele;
typedef vector<vvele> vvvele;

class Solution {
public:
    void print_ele(ele e) {
        cout << "is x? (" << e.is_x << ") touced? (" << e.is_touched << ") ok? (" << e.is_ok << ") next (" << e.next << ")" << endl;
        return;
    }
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        M = nums1.size();
        N = nums2.size();
        K = k;
        vvvele dp(K+1, vvele(M+1, vele(N+1, ele(0,0,0,0))));
        for (auto i : dp) 
            for (auto j : i) 
                for (auto q : j) print_ele(q);
            
        recur_helper(nums1, nums2, dp, 0, 0, 0, false);
        vint res;
        auto it0 = dp[0][0][0];
        int x0 = 0, y0 = 0;
        if (!it0.is_ok) return res;
        for (int i = 0; i < k; ++i) {
            it0 = dp[i][x0][y0];
            int t1 = it0.is_x ? nums1[it0.next-1] : nums2[it0.next-1];
            res.push_back(t1);
            x0 = it0.is_x ? it0.next : x0;
            y0 = it0.is_x ? y0 : it0.next;
        }
        return res;
    }
    bool more_than(vint &numsx, vint &numsy, vvvele &dp, int k, int x0, int y0, int x1, int y1) {
        int initx0 = x0, inity0 = y0;
        int initx1 = x1, inity1 = y1;
        
        for (int i = k; i <= K; ++i) {
            auto e0 = dp[i][initx0][inity0],
                 e1 = dp[i][initx1][inity1];
            int t0 = e0.is_x ? numsx[initx0 - 1] : numsy[inity0 - 1];
            int t1 = e1.is_x ? numsx[initx1 - 1] : numsy[inity1 - 1];
            if (t0 != t1) return t0 > t1;
            if (e0.is_x) {
                initx0 = e0.next;
            } else {
                inity0 = e0.next;
            }
            if (e1.is_x) {
                initx1 = e1.next;
            } else {
                inity1 = e1.next;
            }
        }
        return false;
    }
    void recur_helper(vint &numsx, vint &numsy, vvvele &dp, int k, int x0, int y0, bool usdx)
    {
    MDebugLog(k) << " " << x0 << " " << y0 << " " << usdx << endl;
        if (M + N - x0 -y0 < K - k) {
            dp[k][x0][y0].is_touched = true;
            dp[k][x0][y0].is_ok = false;
            return;
        }
        if (k == K) {
            auto &it1 = dp[k][x0][y0];
            it1.is_touched = it1.is_ok = true;
            it1.is_x = usdx;
            return;
        }
        if (dp[k][x0][y0].is_touched) return;
        vvint tmpv;
        // select x
        bool used_x = true;
        for (int i = x0+1; i <= M; ++i) {
            cout << i << " " << y0 << endl;
            recur_helper(numsx, numsy, dp, k+1, i, y0, used_x);
            if (dp[k+1][i][y0].is_ok) {
                tmpv.push_back(vint({i, y0}));
            }
        }
        used_x = false;
        // select y
        for (int i = y0+1; i <= N; ++i) {
            cout << x0 << " - " << i << endl;
            recur_helper(numsx, numsy, dp, k+1, x0, i, used_x);
            if (dp[k+1][x0][i].is_ok) {
                tmpv.push_back(vint({x0, i}));
            }
        }
        auto &cur_ele = dp[k][x0][y0];
        if (tmpv.empty()) {
            cur_ele.is_ok = false;
            cur_ele.is_touched = true;
            return;
        }
        int initx0 = tmpv[0][0],
            inity0 = tmpv[0][1];
        int mc = 0;
        for (auto &it : tmpv) {
            if (mc++ == 0) continue;
            int t01 = it[0], t02 = it[1];
            for (int i = k+1; i <= K; ++i) {
                cout << numsx[t01] <<  " " << numsy[t02] << " --\n";
                auto dp1 = dp[i][t01][t02];
                t01 = dp1.is_x ? dp1.next : t01;
                t02 = dp1.is_x ? t02 : dp1.next;
            }
            if (!more_than(numsx, numsy, dp, k+1, initx0, inity0, it[0], it[1])) {
                initx0 = it[0];
                inity0 = it[1];
            }
        }
        if (initx0 != x0) {
            cur_ele.is_x = usdx;
            cur_ele.is_touched = true;
            cur_ele.is_ok = true;
            cur_ele.next = initx0;
        } else {
            cur_ele.is_x = usdx;
            cur_ele.is_touched = true;
            cur_ele.is_ok = true;
            cur_ele.next = inity0;
        }
        return;
    }

    int M, N, K;
};
int main() {
   vint numx = {3,2}; 
   vint numy = {0};
   PRINT1D(numx, " ");
   PRINT1D(numy, " ");
   Solution so;
   auto res = so.maxNumber(numx, numy, 2);
   PRINT1D(res, ",");
   return 0;
}


