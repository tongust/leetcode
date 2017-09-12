#include <algorithm>
#include <cmath>
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

using std::cin;
using std::cout;
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

/* Typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;

template<typename T>
int countRange(multiset<T> &mset, const T& val_lower, const T& val_upper)
{
        //for (auto it : mset) cout << it << " ";
        // [)
        if (val_lower > val_upper)return -1;
        auto lower = std::lower_bound(mset.begin(), mset.end(), val_lower);
        auto upper = std::upper_bound(mset.begin(), mset.end(), val_upper);
        return std::distance(lower, upper);
        // return std::distance(upper, lower); // WRONG!
}

int main()
{
        multiset<int> mset = {2,4,1,7,3,9,3,1,11};
        for (auto it : mset)
                cout << it << " ";
        int l = 1,
            u = 5;
        cout << "lower" << endl;
        cin >> l;
        cout << "upper" << endl;
        cin >> u;
        cout << countRange(mset, l, u) << endl;
        return 0;
}
