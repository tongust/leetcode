#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include <math.h>       /* log2 */

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


#define MMIN(x, y) (x) > (y) ? (y) : (x)

#define MMAX(x, y) (x) < (y) ? (y) : (x)





typedef vector<int> vint;

typedef vector<vint> vvint;

class Solution {

public:

    int minCut1(string s) {

        if (s.size() <= 1) return 0;

        vvint dp(s.size(), vint(s.size(), -1));

        int N = s.size(), N0 = s.size() - 1;

        vvint dp2(N);

        for (int i = 0; i < N; ++i) 

            dp[i][i] = 1;

        for (int i = 0; i < N; ++i) {

            for (int j = N0; j > i; --j) {

                int recur = recurHelper(s, dp, i, j);

                if (recur == 1) {

                    dp2[i].push_back(j);

                }

            }

        }

        vint dp1(N, N);

        recurCut(dp1, dp, 0);

        return dp1[0];

    }

    int recurCut(vint &dp1, vvint &dp, int j0) {

        int N = dp1.size(), N0 = dp1.size() - 1;

        if (j0 >= N0)

        {

            if (j0 == N0) dp1[N0] = 0;

            return 0;

        }

        

        if (dp1[j0] < N) return dp1[j0];

        int res = N;

        for (int i = j0; i < N; ++i) {

            if (dp[i][j0] == 1) {

                int tmp;

                if (i == N0) 

                    tmp = 0;

                else 

                    tmp = 1 + recurCut(dp1, dp, i+1);

                if (res > tmp)

                    res = tmp;

            }

        }

        dp1[j0] = res;

        return res;

    }

    int recurHelper(string &s, vvint &dp, int i, int j) {

        if (dp[i][j] > -1)return dp[i][j];

        if (j <= i + 2)

        {

            dp[j][i] = dp[i][j] = (s[i] == s[j] ? 1 : 0);

            return dp[j][i];

        }

        if (s[i] == s[j]) {

            dp[j][i] = dp[i][j] = recurHelper(s, dp, i+1, j-1);

        } else {

            dp[i][j] = dp[j][i] = 0;

        }

        return dp[i][j];

    }

    int minCut(string s) {

        return minCut1(s);

    }

};
