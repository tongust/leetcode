

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

typedef vector<string> vstring;
typedef vector<vstring> vvstring;
typedef vector<vvstring> vvvstring;
struct greater
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};
class Solution {
public:
    vint numsx, numsy;
    int K, M, N;
    vint maxNumber(vint &num1, vint &num2, int k) {
        vint res;
        K = k;
        M = num1.size();
        N = num2.size();
        numsx = num1;
        numsy = num2;
        if (M+N < K) return res;
        vvvstring dp(K+1, vvstring(M+1, vstring(N+1)));
        rec_helper(dp, 0, 0, 0);
        
        for (auto c : dp[0][0][0]) {
            res.push_back(c-48);
        }
        cout << dp[0][0][0] << endl;
        return res;
    }
    bool more_than(vint &a, vint &b) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            if (a[i] != b[i]) 
                return a[i] > b[i];
        }
        return false;
    }
    bool rec_helper(vvvstring &dp, int k, int x, int y) {
        if (k >= K ) return true;
        if (!dp[k][x][y].empty()) {
            return dp[k][x][y][0] != 1;
        }
        if (M+N-x-y < K - k) {
            dp[k][x][y].push_back(1);
            return false;
        }
        string max_vint;
        for (int i = x + 1; i <= M; ++i) {
            if (rec_helper(dp, k+1, i, y)) {
                auto &dp1 = dp[k+1][i][y];
                auto dp2 = string(1, char(numsx[i-1])+48) + dp1;
                if (max_vint.empty()) {
                    max_vint = dp2;
                } else {
                    if (max_vint < dp2) {
                        max_vint = dp2;
                    }
                }
            }
        }
        string max_vint1;
        for (int i = y + 1; i <= N; ++i) {
            if (rec_helper(dp, k+1, x, i)) {
                auto &dp1 = dp[k+1][x][i];
                auto dp2 = string(1, char(numsy[i-1])+48) + dp1;
                if (max_vint1.empty()) {
                    max_vint1 = dp2;
                } else {
                    if (max_vint1 < dp2) {
                        max_vint1 = dp2;
                    }
                }
            }
        }
        if (max_vint.empty() && max_vint1.empty()) {
            max_vint.push_back(1);
            dp[k][x][y] = max_vint;
            return false;
        } else {
            if (int(max_vint.empty()) + int (max_vint1.empty()) == 1) {
                dp[k][x][y] = max_vint1.empty() ? max_vint : max_vint1;
            } else {
                if (max_vint > max_vint1)
                    dp[k][x][y] = max_vint;
                else 
                    dp[k][x][y] = max_vint1;
            }
            return true;
        }
    }
};


int main() {
   vint numx = {6,4,7,8,6,5,5,3,1,7,4,9,9,5,9,6,1,7,1,3,6,3,0,8,2,1,8,0,0,7,3,9,3,1,3,7,5,9,4,3,5,8,1,9,5,6,5,7,8,6,6,2,0,9,7,1,2,1,7,0,6,8,5,8,1,6,1,5,8,4};
   vint numy = {3,0,0,1,4,3,4,0,8,5,9,1,5,9,4,4,4,8,0,5,5,8,4,9,8,3,1,3,4,8,9,4,9,9,6,6,2,8,9,0,8,0,0,0,1,4,8,9,7,6,2,1,8,7,0,6,4,1,8,1,3,2,4,5,7,7,0,4,8,4};
   PRINT1D(numx, " ");
   PRINT1D(numy, " ");
   Solution so;
   auto res = so.maxNumber(numx, numy, 70);
   PRINT1D(res, ",");
   return 0;
}
