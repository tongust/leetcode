#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
typedef std::pair<int,int> pairii;
inline
bool searchM_row(vector<vint> &mx, const int &t, int row)
{
    if (mx[row].empty()) return false;
    int N = mx[row].size();
    int a = 0;
    int b = N-1;
    int e = (a+b)/2;
    if (mx[row][a] == t || mx[row][b] == t || mx[row][e] == t)return true;
    if (mx[row][a] > t || mx[row][b] < t)return false;
    while (a < b)
    {
        if (a==b)
            return mx[row][a] == t;
        if (t < mx[row][e])
        {
            b = e;
            a++;
        }
        else
        {
            a = e;
            b--;
        }
        if (mx[row][a] == t || mx[row][b] == t)return true;
        e = (a+b)/2;
    }
    return false;
}
inline
bool searchM_col(vector<vint> &mx, const int &t, int row)
{
    if (mx.empty()) return false;
    int N = mx.size();
    int a = 0;
    int b = N-1;
    int e = (a+b)/2;
    if (mx[a][row] == t || mx[b][row] == t || mx[e][row] == t)return true;
    if (mx[a][row] > t || mx[b][row] < t)return false;
    while (a < b)
    {
        if (a==b)
            return mx[a][row] == t;
        if (t < mx[e][row])
        {
            b = e;
            a++;
        }
        else
        {
            a = e;
            b--;
        }
        if (mx[a][row] == t || mx[b][row] == t)return true;
        e = (a+b)/2;
    }
    return false;
}
bool searchMatrix(vector<vint> &mx, const int &t, pairii b, pairii e)
{
    if (e.first - b.first <=2 && e.second - b.second <= 2)
    {
        for (int i = b.first; i < e.first; ++i)
        {
            for (int j = b.second; j < e.second; ++j)
            {
                if (mx[i][j] == t) 
                    return true;
            }
        }
        return false;
    }
    pairii med((b.first+e.first)/2, (b.second+e.second)/2);
    if (mx[e.first-1][e.second-1] < t || mx[b.first][b.second] > t ) return false;
    if (
            searchM_row(mx,t, b.first) ||
            searchM_row(mx,t, med.first) ||
            searchM_row(mx,t, e.first-1) ||
            searchM_col(mx,t, b.second) ||
            searchM_col(mx,t, e.second-1) ||
            searchM_col(mx,t, med.second)
       )
        return true;
    return (
            searchMatrix(mx, t, pairii(med.first+1, b.second+1), pairii(e.first-1, med.second)) ||
            searchMatrix(mx, t, pairii(b.first+1, med.second+1), pairii(med.first, e.second-1)) ||
            searchMatrix(mx, t, pairii(med.first+1, med.second+1), pairii(e.first-1, e.second-1)) ||
            searchMatrix(mx, t, pairii(b.first+1, b.second+1), med)
           );
}
bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
    if (matrix.empty() || matrix[0].empty()) return false;
    return searchMatrix(matrix, target, pairii(0,0), pairii(matrix.size(), matrix[0].size()));
}

int main()
{
    vector<vint> mx = {
        {1,   3,  5, 7, 9},
        {2,   4,  6, 8, 19}, 
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}};
    for (auto &i: mx) for (auto &j : i)cout <<searchMatrix(mx, j) << endl;
    for (int i = -2; i < 45;++i)
        cout << i << "\t" << searchMatrix(mx, i) << endl;
    cout << searchM_row(mx, 8, 1) << endl;
    cout << searchM_col(mx, 8, 3) << endl;
    return 0;
}
