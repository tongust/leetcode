#include <iostream>
#include <utility>

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
using std::pair;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;
typedef pair<int, int> pint;

int maxEarFence(vector<int> &fence) {
    if (fence.empty()) return 0;
    vector<pint> mstack;
    int res = fence[0];
    pint tmp;
    tmp.first = res; tmp.second = 0;
    mstack.push_back(tmp);
    for (int i = 1; i < fence.size(); ++i) {
        int cur = fence[i];
        pint tmp1, tmp2;
        tmp2.first = cur; tmp2.second = i;
        while (!mstack.empty() && mstack[mstack.size()-1].first >= cur) {
            tmp1 = mstack[mstack.size() - 1];
            int aera1 = tmp1.first * (i - tmp1.second);
            if (aera1 > res)
                res = aera1;
            tmp2.second = tmp1.second;
            mstack.pop_back();
        }
        mstack.push_back(tmp2);
    }
    int N = fence.size();
    for (auto it : mstack) {
        int aera1 = it.first * (N - it.second);
        if (aera1 > res)
            res = aera1;
    }
    return res;
}

int maximalRectangle_(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int N = matrix.size();
    int M = matrix[0].size();
    for (auto &i : matrix) 
        for (auto &j : i)
            if (j == '0')
                j = 0;
            else j = 1;
    vector<int> dp(M, 0);
    int res = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == 0) {
                if (matrix[i][j] == 1) {
                    dp[j] = 1;
                } else
                    dp[j] = 0;
            } else {
                if (matrix[i][j] == 1) {
                    dp[j]++;
                } else {
                    dp[j] = 0;
                }
            }
        }
        int tmp1 = maxEarFence(dp);
        if (tmp1 > res) 
            res = tmp1;
    }
    return res;
}

int main() {
    int N = 5;
    string s = "10100101111111110010";
    int mc = 0;
    vector<vector<char>> matrix(N, vector<char>(N));
    for (auto i : s) {
        matrix[mc / N][mc % N] = i;
        mc++;
    }
    for (auto i : matrix) 
    {
        for (auto j : i)
            cout << j;
        cout << endl;
    }
    cout << maximalRectangle_(matrix) << endl;
    return 0;
}
