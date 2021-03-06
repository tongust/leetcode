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
#define _MIN_S_32 0x80000001
#define _MIN_U_32 0x00000000
#define _MAX_S_32 0x7fffffff
#define _MAX_U_32 0xffffffff
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
        typedef vector<char> vchar;
        typedef vector<vchar> vvchar;
        bool isIn(int i, int n) {
                return i > -1 && i < n;
        }
        bool recur(vvchar &board, string &word, int k, int i0, int j0, vvchar &dp)
        {
                if (k == word.size())
                        return true;
                int len_w = word.size(),
                    m = board.size(),
                    n = board[0].size();
                char w = word[k];
                for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                                int i1 = i0 + i,
                                    j1 = j0 + j;
                                if ((i == 0 && j == 0) || (i*j != 0))
                                        continue;
                                if (!isIn(i1, m) || !isIn(j1, n)) { continue; }
                                if (board[i1][j1] != w || (dp[i1][j1]!=0))
                                                continue;
                                /* visited */
                                dp[i1][j1] = 1;
                                if (recur(board, word, k+1, i1, j1, dp))
                                {
                                        dp[i1][j1] = 0;
                                        return true;
                                }
                                dp[i1][j1] = 0;
                        }
                }
                return false;
        }
        bool exist(vector<vector<char>>& board, string word) {
                vvchar dp(board.size(), vchar(board[0].size(), 0));
                for (int i = 0; i < board.size(); ++i)
                {
                        for (int j = 0; j < board[i].size(); ++j)
                        {
                                if (word.front() == board[i][j]) {
                                        dp[i][j] = 1;
                                        if (recur(board, word, 1, i, j, dp)) {
                                                return true;
                                        }
                                        dp[i][j] = 0;
                                }
                        }
                }
                return false;
        }
};
int main()
{
        Solution::vvchar a = {
			{'A','B','C','E'},
			{'S','F','C','S'},
			{'A','D','E','E'} };
        string s;
        Solution so;
        while(cin >> s) {
                cout << so.exist(a, s) << endl;
        }
        return 0;
}

