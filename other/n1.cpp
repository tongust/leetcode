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

void pro1(vvint &in, vvint &co, const int c)
{
        co.clear();
        co.resize(c);
        for (int i = 0; i < in.size(); ++i) {
                for (int j = 0; j < in[i].size(); ++j) {
                        if (in[i][j] != 0) 
                                co[in[i][j] - 1].push_back(i);
                }
        }
        return;
}

int solution(vvint &co, int m)
{
        int c = co.size();
        int res = 0;
        for (int i = 0; i < c; ++i) {
                vint &nums = co[i];
                if (nums.size() <= 1)
                        continue;
                std::sort(nums.begin(), nums.end());
                int pre = nums[0];
                for (int j = 1; j < nums.size(); ++j) {
                        int t0 = nums[j] - pre;
                        pre = nums[j];
                        if (t0 < m){
                                res++;
                                break;
                        }
                }

        }
        return res;
}

int main() {
        int n, m, c;
        cin >> n >> m >> c;
        vvint colorIdx;
        vvint inputs(n);
        for (int i = 0; i < n; ++i) {
                int t0 = 0;
                cin >> t0;
                if(t0 == 0) {
                        inputs[i] = vint(1, 0);
                } else {
                        inputs[i].resize(t0);
                        for (int j = 0; j < t0; ++j) {
                                int tmp0;
                                cin >> tmp0;
                                inputs[i][j] = tmp0;
                        }
                }
        }
        for (int i = 0; i < m-1; i++) {
                inputs.push_back(inputs[i]);
        }
        // 
        cout << "\n------" << endl;
        pro1(inputs, colorIdx, c);
        PRINT2D(colorIdx, " ");
        cout << "------" << endl;
        cout << solution(colorIdx, m) << endl;
        return 0;
}
