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

class dijstra{
public:
        vint dij(vvint &dismat)
        {
                int n = dismat.size();
                vint dp_vist(n, 0);// -1: not visited
                vint path(n, 0);
                
                /* loop n-1 times. Why?
                 * This is the sample way to make sure
                 * that there will be no one in the
                 * min-priority to be updated */
                for (int outer = 1; outer < n; ++outer) {
                        /* min-priority queue */
                        int idx = 0, mmin = _MAX_S_32;
                        for (int i = 1; i < n; ++i) {
                                if (!dp_vist[i]) {
                                        if (mmin > dismat[0][i]) {
                                                mmin = dismat[0][i];
                                                idx = i;
                                        }
                                }
                        }

                        /* dp to be visited */
                        dp_vist[idx] = 1;

                        /* update */
                        for (int j = 0; j < n; ++j) {
                                if (isReacheable(dismat, idx, j)) {
                                        int dis_new = dismat[idx][j] + mmin;
                                        if (dis_new < dismat[0][j]) {
                                                dismat[0][j] = dis_new;
                                                path[j] = idx; /* record through which node, the distance is less overhead */
                                        }
                                }
                        }
                }
                return path;
        }
        bool isReacheable(vvint &dismat, int s, int t) {
                return dismat[s][t] != _MAX_S_32;
        }
        vint print_path(vint &path)
        {
                int n = path.size();
                int p = path.back();
                vint res;
                res.push_back(n-1);
                while (p != 0) {
                        res.push_back(p);
                        p = path[p];
                }
                for (int i = 0; i < res.size() / 2; ++i) {
                        int tmp = res[res.size() - 1 - i];
                        res[res.size() - 1 - i] = res[i];
                        res[i] = tmp;
                }
                PRINT1D(res, " --> ");
                return res;
        }
};

void solve_print(vvint &dismat)
{
        dijstra d;
        auto path = d.dij(dismat);
        d.print_path(path);
}

int main()
{
        int n = 6;
        vvint p(n, vint(n, _MAX_S_32));
        p[0][1]=10;
        p[0][3]=30;
        p[1][2]=50;
        p[1][4]=100;
        p[2][4]=5;
        p[3][2]=20;
        p[3][4]=60;
        p[4][5]=10;
        for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                {
                        if (p[j][i] != _MAX_S_32)
                                p[i][j] = p[j][i];
                }
        solve_print(p);
        return 0;
}

