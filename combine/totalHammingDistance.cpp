#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;

int totalHammingDistance(int* nums, int numsSize) {
    int res = 0;
    int a = 0, b = 0, i = 0;
    for (int m = 0; m < numsSize; ++m)
    {
        for (int j = m+1; j < numsSize; ++j)
        {
            i = (nums[m]^nums[j]);
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            res += (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
        }
    }
    return res;
}
int td(vector<int> &nums)
{
        auto numsSize = nums.size();
        int res = 0;
        int i = 0;
        int p = 0, q = 0;
        vector<int> b1;
        b1 = nums;
        for (int i = 0; i < 32; ++i)
        {
            p  = q = 0;
            if (i!=0)
            {
                for (int j = 0; j != numsSize; ++j)
                    b1[j] = b1[j] >> 1;
            }
            for (auto &bt : b1)
                {
                    if (bt % 2 == 0)
                        p++;
                    else
                        q++;
                }
            cout << p << "," << q << ",," << b1[0] <<endl;
            res += p*q;
        }
        return res;
    }
int main()
{ 
    int a[3] ={4,14,2};
    int N = 3;
    cout << "pop\t" << __builtin_popcount((4^14)) << endl;
    vector<int> A = {4,14,2};
    cout << td(A) << endl;
    return 0;
}
