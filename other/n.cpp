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

void foo(vvint &mat, vint &nums) 
{
        int mx = nums[0];
        for (auto it : nums)
                if (it>mx)
                        mx = it;
        unordered_map<int, set<int>> dp;
        for (int i = 0; i < nums.size(); ++i) {
                int like = nums[i];
                auto itf = dp.find(like);
                if (itf != dp.end()) {
                        dp[like].insert(i);
                } else {
                        set<int> tmp;
                        tmp.insert(i);
                        dp[like] = tmp;
                }
        }
        for (auto& it : mat) {
                int l = it[0],
                    r = it[1],
                    k = it[2];
                set<int> &d = dp[k];
                //MDebugLog(k) << " l " << l << " r " << r << endl;
                //for (auto it : d)
                //        cout << it << " >\n";
                auto low = std::lower_bound(d.begin(), d.end(), l-1);
                auto up = std::upper_bound(d.begin(), d.end(), r-1);
                cout << std::distance(low, up) << endl;
        }
        return;

}

int main(){
        int n;
        cin >> n;
        vint nums(n);
        for (int i =0;i<n;++i){
                cin >> nums[i];
        }
        int q;
        cin >> q;
        vvint mat(q,vint(3));
        for (int i =0;i<q;++i){
                for (int j = 0; j < 3; ++j) {
                        cin >> mat[i][j];
                }
        }
        foo(mat, nums);
        return 0;
}
