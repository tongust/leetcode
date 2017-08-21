#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include <math.h>       /* log2 */

#ifndef PRINT1D
#define PRINT1D(v,d) do {for (auto it_print : v) cout << int(it_print) << d; cout << endl;}while(0)
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

#define FORWITHN(i,N) for (i = 0; i < N; ++N)


bool recurP(string &s, vector<char> &isP, int i, int j) {
    cout << i << "," << j << endl;
    if (i >= j) {
        int idx = i*s.size() + j;
        isP[idx] = 1;
        return true;
    }
    int idx = i*s.size() + j;
    if (isP[idx] != -1) return isP[idx];
    if (s[i] != s[j]) {
        isP[idx] = 0;
        return false;
    }
    if (recurP(s, isP, i+1, j-1)) {
        isP[idx] = 1;
        return true;
    } else {
        isP[idx] = 0;
        return false;
    }
}
int recurCal(vector<int> &dp2, int N, vector<vector<int>> &dp0, int i) {
    if (i >= N) return 0;
    if (dp2[i] > 0) return dp2[i];
    int res = N;
    for (auto i0 : dp0[i]) {
        int tmp = recurCal(dp2,N,dp0,i0+1) + 1;
        if (res > tmp)
            res = tmp;
    }
    dp2[i] = res;
    return res;
}

int minCut1(string s) {
    int N = s.size();
    vector<char> isP(s.size()*s.size(), -1/*untouched*/);
    int i_fwn= 0;
    PRINT1D(isP, ",")s
    FORWITHN(i_fwn,N) 
        isP[i_fwn*N+i_fwn] = 1/* true */;
    MDebugLog("hi");
    recurP(s, isP, 0, N-1);
    vector<vector<int>> dp0(N);
    int i = 0, j = 0;
    FORWITHN(i, N) {
        auto &vs = dp0[i];
        FORWITHN(j, N) {
            if (isP[i*N+j] == 1) {
                vs.push_back(j);
            }
        }
    }
    int res = N;
    vector<int> dp2(N, 0);
    return recurCal(dp2, N, dp0, 0);
}

