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
template<typename T>
void exchange(T& a, T& b) {
    auto tmp = a;
    a = b;
    b = tmp;
    return;
}

template<class T>
void quickSort(typename vector<T>::iterator beg, typename vector<T>::iterator end) {
    if (beg == end || end - beg == 1) return;
    auto pre = beg;
    bool flg = false;
    auto lmd = end - 1;
    auto provit = *(lmd);
    for (auto it = beg; it != lmd; ++it)
    {
        if (*it <= provit) {
            if (flg)
                pre++;
            else
                flg = true;
            exchange(*it, *pre);
        }
    }
    if (flg) pre++;
    exchange(*lmd, *pre);
    quickSort<T>(beg, pre);
    quickSort<T>(pre+1, end);
}

void exg(int &lhs, int &rhs)
{
    auto tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}
int quickSelect(vint &nums, int a, int b, int n) {
    if (b - a - 1 == n)
        return nums[b - 1];
    int t = a - 1;
    int p = nums[b - 1];
    for (int i = a; i < b - 1; i++)
    {
        if (nums[i] <= p) {
            t++;
            exg(nums[t], nums[i]);
        }
    }
    t++;
    exg(nums[t], nums[b - 1]);
    if (a + n > t) {
        return quickSelect(nums, t + 1, b, a + n - t - 1);
    }
    else if (a + n == t)
    {
        return nums[t];
    }
    else
        return quickSelect(nums, a, t, n);
}


