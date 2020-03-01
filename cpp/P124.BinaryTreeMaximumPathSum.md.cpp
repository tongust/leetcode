# 124. Binary Tree Maximum Path Sum


```cpp

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


class Solution {
public:
    typedef TreeNode* tnp;
    static int mmax(int a, int b)
    {
        return MMAX(a, b);
    }
    int maxPathSum(tnp root)
    {
        if (!root)return 0;
        int res = -10000;
        recur(root, res);
        return res;
    }
    int recur(tnp root, int &res)
    {
    /* return the single direction (either left or right) max sum
     * res: recourd the max sum of path when do recuring.
     */
        if (!root) return 0;
        int val = root->val;
        /* left path max sum value */
        int leftv = recur(root->left, res);
        /* right path max sum value */
        int rightv = recur(root->right, res);
        /* single path value from current point */
        int sv = val + mmax(0, mmax(rightv, leftv));
        /* double directions value from current point */
        int dv = val + mmax(0, leftv) + mmax(0, rightv);
        res = mmax(dv, res);
        return sv;
    }
};
```
