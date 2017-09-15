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

/* using */

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
 */

typedef unsigned long long ull64;
void run1() {
        int n = 0;
        cin >> n;
        vint nums(n);
        for (auto &num : nums)
                cin >> num;
        vector<string> nstr(n);
        for (int i = 0; i < n; ++i) {
                nstr[i] = std::to_string(nums[i]);
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
                string ls = nstr[i]; 
                for (int j = i+1; j < n; j++) {
                        string rs = nstr[j];
                        ull64 lr = std::stoull(ls+rs);
                        if (lr % 7 == 0)
                                res++;
                        lr = std::stoull(rs+ls);
                        if (lr % 7 == 0)
                                res++;
                }
        }
        cout << res << endl;
}
int run0(vint &nums) {
        int n = nums.size();
        vector<string> nstr(n);
        for (int i = 0; i < n; ++i) {
                nstr[i] = std::to_string(nums[i]);
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
                string ls = nstr[i]; 
                for (int j = i+1; j < n; j++) {
                        string rs = nstr[j];
                        ull64 lr = std::stoull(ls+rs);
                        if (lr % 7 == 0)
                                res++;
                        lr = std::stoull(rs+ls);
                        if (lr % 7 == 0)
                                res++;
                }
        }
        return res;
}
int is7(int l, int r) {
        int res = 0;
        string ls = std::to_string(l),
               rs = std::to_string(r);
        if(std::stoull(ls+rs) % 7 == 0)
                res++;
        if(std::stoull(rs+ls) % 7 == 0)
                res++;
        return res;

}
void run2() {
        int n = 0;
        cin >> n;
        vint nums0, nums1;
        for (int i = 0; i < n; ++i)
        {
                int t = 0;
                cin >> t;
                if (t % 7 ==0)
                        nums0.push_back(t);
                else nums1.push_back(t);
        }
        int res = 0;
        if (nums0.size() > 1) {
                res = nums0.size();
                res = (res - 1)*res;
                res += run0(nums1);
        }
        else {
                vint nums2(n);
                std::copy(nums0.begin(), nums0.end(), nums2.begin());
                std::copy(nums1.begin(), nums1.end(), nums2.begin()+nums0.size());
                res = run0(nums2);
        }
        cout << res << endl;
}
int  main () {
        run2();
        return 0;
}


